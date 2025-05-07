#include "BlueprintLibraries/OmegaFunctionLibrary.h"

#include "GameplayAbilitySpec.h"
#include "PaperSprite.h"
#include "AbilitySystem/Data/CharacterDefaultInfo.h"
#include "Game/GameModes/OmegaGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/OmegaAttributeSet.h"

FVector2D UOmegaFunctionLibrary::GetSourceSize(UPaperSprite* Sprite)
{
	return Sprite->GetSourceSize();
}

void UOmegaFunctionLibrary::GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC)
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
	
	for (const TSubclassOf<UGameplayAbility> AbilityClass : CharacterClassInfo->CommonAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		ASC->GiveAbility(AbilitySpec);
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
		if (CharacterClassInfo->AttributeByTagMap.Contains(ModifyTag))
		{
			FGameplayEffectContextHandle EffectContextHandle = ASC->MakeEffectContext();
			FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->AttributeByTagMap[ModifyTag], 1.f, EffectContextHandle); 
			ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data);
		}
	}
}
