#include "AbilitySystem/OmegaAbilitySystemGlobals.h"

#include "OmegaAbilityTypes.h"

FGameplayEffectContext* UOmegaAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FOmegaGameplayEffectContext();
}
