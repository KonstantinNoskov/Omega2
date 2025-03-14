#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "OmegaGameplayAbility.generated.h"

UCLASS()
class OMEGA_API UOmegaGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category = "OmegaAbility|Input")
	FGameplayTag StartupInputTag;

	UPROPERTY(EditDefaultsOnly, Category = "OmegaAbility|Damage")
	FScalableFloat AbilityDamageMagnitude;
	
};
