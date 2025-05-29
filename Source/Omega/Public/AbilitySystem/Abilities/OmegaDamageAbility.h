
#pragma once

#include "CoreMinimal.h"
#include "OmegaGameplayAbility.h"
#include "OmegaDamageAbility.generated.h"

UCLASS()
class OMEGA_API UOmegaDamageAbility : public UOmegaGameplayAbility
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable)
	void CauseDamage(AActor* TargetActor);

protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly )
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	UPROPERTY(EditDefaultsOnly, Category = "Omega|Damage", meta=(ForceInlineRow))
	TMap<FGameplayTag, FScalableFloat> DamageTypes;
};
