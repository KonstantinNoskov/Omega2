
#pragma once

#include "CoreMinimal.h"
#include "OmegaGameplayAbility.h"
#include "OmegaDamageAbility.generated.h"

UCLASS()
class OMEGA_API UOmegaDamageAbility : public UOmegaGameplayAbility
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly )
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	UPROPERTY(EditDefaultsOnly, Category = "Omega|Damage")
	TMap<FGameplayTag, FScalableFloat> DamageTypes;
};
