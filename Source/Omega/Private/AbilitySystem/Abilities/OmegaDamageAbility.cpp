#include "AbilitySystem/Abilities/OmegaDamageAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "OmegaAbilityTypes.h"

void UOmegaDamageAbility::CauseDamage(AActor* TargetActor)
{
	// Set Effect Context
	const UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
	if (!SourceASC) return;

	
	FGameplayEffectContextHandle EffectContextHandle = SourceASC->MakeEffectContext();
	FOmegaGameplayEffectContext* OmegaEffectContext = static_cast<FOmegaGameplayEffectContext*>(EffectContextHandle.Get());
	
	OmegaEffectContext->SetAbility(this);
	OmegaEffectContext->AddSourceObject(GetAvatarActorFromActorInfo());
	
	for (auto DamageType : DamageTypes)
	{
		OmegaEffectContext->AddDamageType(DamageType.Key);
	}
	
	FGameplayEffectSpecHandle DamageSpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, 1, EffectContextHandle);
	for (TTuple<FGameplayTag, FScalableFloat> Pair : DamageTypes)
	{
		OmegaEffectContext->AddDamageType(Pair.Key);
		const FGameplayTag DamageTypeTag = Pair.Key;
		const float ScaledDamage = Pair.Value.GetValueAtLevel(GetAbilityLevel());
		
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(DamageSpecHandle, DamageTypeTag, ScaledDamage);
	}

	GetAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(*DamageSpecHandle.Data, UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor));
}
