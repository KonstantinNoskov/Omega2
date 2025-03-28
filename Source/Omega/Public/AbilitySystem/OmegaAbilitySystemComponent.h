#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "OmegaAbilitySystemComponent.generated.h"

class UOmegaMovementComponent;
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnEffectAssetTagsUpdatedSignature, const FGameplayTagContainer& /*AssetTags*/, const FGameplayEffectSpec& /*AppliedEffectSpec*/)

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class OMEGA_API UOmegaAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:

	UOmegaAbilitySystemComponent();

	
	//  Movement Component Association
	// ===============================================================================================================


private:
	
	TObjectPtr<UOmegaMovementComponent> OmegaMovementComponent;

protected:
	
	UFUNCTION(BlueprintPure)
	UOmegaMovementComponent* GetOmegaMovementComponent();

	
	void OnEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& AppliedEffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);
	
public:
	
	void OnAbilityActorInfoSet();

	void AbilityInputTagPressed(const FGameplayTag& InputTag);
	void AbilityInputTagHeld(const FGameplayTag& InputTag);
	void AbilityInputTagReleased(const FGameplayTag& InputTag);
	
	FOnEffectAssetTagsUpdatedSignature OnEffectAssetTagsUpdatedDelegate;


#pragma region ABILITIES

	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& InStartupAbilities);

#pragma endregion
		
	
};
