#include "AbilitySystem/OmegaAbilitySystemComponent.h"

#include "OmegaGameplayTags.h"
#include "AbilitySystem/Abilities/OmegaGameplayAbility.h"
#include "Characters/OmegaCharacter.h"
#include "Components/OmegaMovementComponent.h"


UOmegaAbilitySystemComponent::UOmegaAbilitySystemComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UOmegaAbilitySystemComponent::OnAbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UOmegaAbilitySystemComponent::OnEffectApplied);
}

void UOmegaAbilitySystemComponent::AbilityInputTagPressed(const FGameplayTag& InputTag)
{

	if (!InputTag.IsValid()) return;

	if (GetOmegaMovementComponent()->GetOmegaCustomMovementMode() != EOmegaCustomMovementMode::NONE) return;
	
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (!AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag) || AbilitySpec.IsActive()) continue;
		
		
		AbilitySpecInputPressed(AbilitySpec);
		
		TryActivateAbility(AbilitySpec.Handle);
	}
}

void UOmegaAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	/*if (!InputTag.IsValid()) return;

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (!AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag) || AbilitySpec.IsActive()) return;

		AbilitySpecInputPressed(AbilitySpec);
		TryActivateAbility(AbilitySpec.Handle);
	}*/
}

void UOmegaAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (!AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag)) return;
		
		AbilitySpecInputReleased(AbilitySpec);
	}
}

void UOmegaAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& InStartupAbilities)
{
	for (const TSubclassOf<UGameplayAbility> AbilityClass : InStartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1.f);
		
		if (const UOmegaGameplayAbility* OmegaAbility = CastChecked<UOmegaGameplayAbility>(AbilitySpec.Ability))
		{
			AbilitySpec.DynamicAbilityTags.AddTag(OmegaAbility->StartupInputTag);
			GiveAbility(AbilitySpec);
		}
	}
}


// Broadcast gameplay effect tags. Mostly for widget controller
void UOmegaAbilitySystemComponent::OnEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& AppliedEffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	AppliedEffectSpec.GetAllAssetTags(TagContainer);
	
	OnEffectAssetTagsUpdatedDelegate.Broadcast(TagContainer, AppliedEffectSpec);
}

UOmegaMovementComponent* UOmegaAbilitySystemComponent::GetOmegaMovementComponent()
{
	if (!OmegaMovementComponent)
	{
		if (AOmegaCharacter* OmegaCharacter = Cast<AOmegaCharacter>(GetAvatarActor()))
		{
			OmegaMovementComponent = OmegaCharacter->GetOmegaMovementComponent();
		}
	}
	
	return OmegaMovementComponent;
}


                      