#pragma once

#include "CoreMinimal.h"
#include "OmegaDamageAbility.h"
#include "OmegaProjectileAbility.generated.h"

class AOmegaProjectile;

UCLASS()
class OMEGA_API UOmegaProjectileAbility : public UOmegaDamageAbility
{
	GENERATED_BODY()

protected:

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AOmegaProjectile> ProjectileClass;
};
