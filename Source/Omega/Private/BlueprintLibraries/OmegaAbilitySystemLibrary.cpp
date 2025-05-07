#include "BlueprintLibraries/OmegaAbilitySystemLibrary.h"

#include "OmegaAbilityTypes.h"

bool UOmegaAbilitySystemLibrary::IsImmuneToEffect(const FGameplayEffectContextHandle& ContextHandle)
{
	if (const FOmegaGameplayEffectContext* OmegaContext = static_cast<const FOmegaGameplayEffectContext*>(ContextHandle.Get()))
	{
		return OmegaContext->IsImmune();
	}
	
	return false;
}

void UOmegaAbilitySystemLibrary::SetIsImmuneToEffect(FGameplayEffectContextHandle& ContextHandle, bool bIsImmuneToEffect)
{
	if (FOmegaGameplayEffectContext* OmegaContext = static_cast<FOmegaGameplayEffectContext*>(ContextHandle.Get()))
	{
		OmegaContext->SetIsImmune(bIsImmuneToEffect);
	}
}

bool UOmegaAbilitySystemLibrary::IsBlockedEffect(const FGameplayEffectContextHandle& ContextHandle)
{
	if (const FOmegaGameplayEffectContext* OmegaContext = static_cast<const FOmegaGameplayEffectContext*>(ContextHandle.Get()))
	{
		return OmegaContext->IsBlocked();
	}
	
	return false;
}

bool UOmegaAbilitySystemLibrary::IsParryEffect(const FGameplayEffectContextHandle& ContextHandle)
{
	if (const FOmegaGameplayEffectContext* OmegaContext = static_cast<const FOmegaGameplayEffectContext*>(ContextHandle.Get()))
	{
		return OmegaContext->IsParried();
	}
	
	return false;
}
