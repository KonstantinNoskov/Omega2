#pragma once

#include "CoreMinimal.h"
#include "OmegaGameplayAbility.h"
#include "OmegaProjectileAbility.generated.h"

class AOmegaProjectile;

UCLASS()
class OMEGA_API UOmegaProjectileAbility : public UOmegaGameplayAbility
{
	GENERATED_BODY()

protected:

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AOmegaProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly )
	TSubclassOf<UGameplayEffect> DamageEffectClass;
};
