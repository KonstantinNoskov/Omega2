#include "BlueprintLibraries/OmegaFunctionLibrary.h"

#include "GameplayAbilitySpec.h"
#include "PaperSprite.h"
#include "AbilitySystem/Data/CharacterDefaultInfo.h"
#include "Game/GameModes/OmegaGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "AbilitySystemComponent.h"
#include "OmegaAbilityTypes.h"
#include "Interfaces/CombatInterface.h"

FVector2D UOmegaFunctionLibrary::GetSourceSize(UPaperSprite* Sprite)
{
	return Sprite->GetSourceSize();
}

void UOmegaFunctionLibrary::GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC, const FGameplayTag& CharacterAttackType)
{
	// Check for GameMode
	AOmegaGameMode* OmegaGameMode = Cast<AOmegaGameMode>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (!OmegaGameMode) return;

	// Check for Character Class Info 
	if (!OmegaGameMode->CharacterClassInfo)
	{
		UE_LOG(LogTemp, Error, TEXT("[%hs] Character Class Info is null. Check for game mode defaults."), __FUNCTION__);
		return;
	}
	
	UCharacterDefaultInfo* CharacterClassInfo = OmegaGameMode->CharacterClassInfo;
	
	// Assign common abilities
	for (const TSubclassOf<UGameplayAbility> AbilityClass : CharacterClassInfo->CommonAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		ASC->GiveAbility(AbilitySpec);
	}

	// Assign Character class abilities
	for (auto AbilityClass : CharacterClassInfo->CharacterClassAbilities)
	{
		ICombatInterface* CombatInterface = Cast<ICombatInterface>(ASC->GetAvatarActor());
		if (CombatInterface)
		{
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass.Value, CombatInterface->GetPlayerLevel());
			ASC->GiveAbility(AbilitySpec);
		}
	}
}
void UOmegaFunctionLibrary::ModifyAttributesByTag(const UObject* WorldContextObject, const FGameplayTagContainer& InTagContainer, UAbilitySystemComponent* ASC)
{
	// Check for GameMode
	AOmegaGameMode* OmegaGameMode = Cast<AOmegaGameMode>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (!OmegaGameMode) return;

	// Check for Character Class Info 
	if (!OmegaGameMode->CharacterClassInfo)
	{
		UE_LOG(LogTemp, Error, TEXT("[%hs] Character Class Info is null. Check for game mode defaults."), __FUNCTION__);
		return;
	}
	
	// Modify ASC attributes if character
	UCharacterDefaultInfo* CharacterClassInfo = OmegaGameMode->CharacterClassInfo;

	
	for (const FGameplayTag& ModifyTag : InTagContainer)
	{
		if (CharacterClassInfo->CharacterTypeInfo.Contains(ModifyTag))
		{
			checkf(CharacterClassInfo->CharacterTypeInfo.Contains(ModifyTag), TEXT("%hs: Attribute modifier tag in CharacterClassInfo is empty!"), __FUNCTION__)

			// Apply attributes modify effect by Character tag 
			const TSubclassOf<UGameplayEffect>& AttributeModifyEffect = CharacterClassInfo->GetCharacterTypeInfo(ModifyTag).AttributesModifyEffect;
			FGameplayEffectContextHandle EffectContextHandle = ASC->MakeEffectContext();
			FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(AttributeModifyEffect, 1.f, EffectContextHandle); 
			ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data);
		}
	}
}

bool UOmegaFunctionLibrary::IsImmuneToEffect(const FGameplayEffectContextHandle& ContextHandle)
{
	if (const FOmegaGameplayEffectContext* OmegaContext = static_cast<const FOmegaGameplayEffectContext*>(ContextHandle.Get()))
	{
		return OmegaContext->IsImmune();
	}
	
	return false;
}
void UOmegaFunctionLibrary::SetIsImmuneToEffect(FGameplayEffectContextHandle& ContextHandle, bool bIsImmuneToEffect)
{
	if (FOmegaGameplayEffectContext* OmegaContext = static_cast<FOmegaGameplayEffectContext*>(ContextHandle.Get()))
	{
		OmegaContext->SetIsImmune(bIsImmuneToEffect);
	}
}

bool UOmegaFunctionLibrary::IsBlockedEffect(const FGameplayEffectContextHandle& ContextHandle)
{
	if (const FOmegaGameplayEffectContext* OmegaContext = static_cast<const FOmegaGameplayEffectContext*>(ContextHandle.Get()))
	{
		return OmegaContext->IsBlocked();
	}
	
	return false;
}
bool UOmegaFunctionLibrary::IsParryEffect(const FGameplayEffectContextHandle& ContextHandle)
{
	if (const FOmegaGameplayEffectContext* OmegaContext = static_cast<const FOmegaGameplayEffectContext*>(ContextHandle.Get()))
	{
		return OmegaContext->IsParried();
	}
	
	return false;
}
