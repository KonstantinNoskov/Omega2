#include "AbilitySystem/MMC/MMC_Health.h"

UMMC_Health::UMMC_Health()
{
}

float UMMC_Health::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	return Super::CalculateBaseMagnitude_Implementation(Spec);
}
