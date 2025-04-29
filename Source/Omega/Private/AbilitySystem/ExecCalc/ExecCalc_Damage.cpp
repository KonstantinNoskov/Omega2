#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"

#include "AbilitySystemComponent.h"
#include "OmegaGameplayTags.h"
#include "AbilitySystem/OmegaAttributeSet.h"

struct OmegaDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(FireResistance)
	
	OmegaDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UOmegaAttributeSet, FireResistance, Target, false)
	}
};

static const OmegaDamageStatics& DamageStatics()
{
	static OmegaDamageStatics DStatics;
	return DStatics;
};

 

UExecCalc_Damage::UExecCalc_Damage()
{
	RelevantAttributesToCapture.Add(DamageStatics().FireResistanceDef);
	
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();
	
	const AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	const AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;

	// GameplayEffect Spec
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	// Gameplay Tags
	FOmegaGameplayTags GameplayTags = FOmegaGameplayTags::Get();
	
	// Fill up Evaluated params
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedSourceTags.GetAggregatedTags();
	
	FAggregatorEvaluateParameters EvaluateParams;
	EvaluateParams.SourceTags = SourceTags;
	EvaluateParams.TargetTags = TargetTags;
	
	// Get Damage Set by Caller Magnitude
	float Damage = Spec.GetSetByCallerMagnitude(GameplayTags.Damage);
	
	// Calculate magic block chance
	float TargetMagicBlockChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().FireResistanceDef, EvaluateParams, TargetMagicBlockChance);
	TargetMagicBlockChance = FMath::Max<float>(TargetMagicBlockChance, 0.f);
	const bool bBlocked = FMath::RandRange(1, 100) < TargetMagicBlockChance;
	Damage = bBlocked ? 0.f : Damage;
	
	FGameplayModifierEvaluatedData EvaluatedData(UOmegaAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, Damage); 
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}
