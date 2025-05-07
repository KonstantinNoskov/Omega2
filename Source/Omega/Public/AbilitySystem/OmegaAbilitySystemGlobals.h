#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "OmegaAbilitySystemGlobals.generated.h"


UCLASS()
class OMEGA_API UOmegaAbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_BODY()

public:
	
	virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;
};
