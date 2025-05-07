#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"

#include <ThirdParty/ShaderConductor/ShaderConductor/External/DirectXShaderCompiler/include/dxc/DXIL/DxilConstants.h>

#include "AbilitySystemComponent.h"
#include "OmegaAbilityTypes.h"
#include "OmegaGameplayTags.h"
#include "AbilitySystem/OmegaAttributeSet.h"
#include "BlueprintLibraries/OmegaAbilitySystemLibrary.h"

struct OmegaDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(PhysicalResistance)
	DECLARE_ATTRIBUTE_CAPTUREDEF(FireResistance)
	DECLARE_ATTRIBUTE_CAPTUREDEF(ColdResistance)
	DECLARE_ATTRIBUTE_CAPTUREDEF(PoisonResistance)
	DECLARE_ATTRIBUTE_CAPTUREDEF(LightningResistance)


	TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition> TagsToCaptureDefs;
	
	OmegaDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UOmegaAttributeSet, PhysicalResistance, Target, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UOmegaAttributeSet, FireResistance, Target, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UOmegaAttributeSet, ColdResistance, Target, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UOmegaAttributeSet, PoisonResistance, Target, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UOmegaAttributeSet, LightningResistance, Target, false)

		const FOmegaGameplayTags& GameplayTags = FOmegaGameplayTags::Get();
		TagsToCaptureDefs.Add(GameplayTags.Attributes_Secondary_Resistance_Physical,	PhysicalResistanceDef);
		TagsToCaptureDefs.Add(GameplayTags.Attributes_Secondary_Resistance_Fire,		FireResistanceDef);
		TagsToCaptureDefs.Add(GameplayTags.Attributes_Secondary_Resistance_Cold,		ColdResistanceDef);
		TagsToCaptureDefs.Add(GameplayTags.Attributes_Secondary_Resistance_Poison,		PoisonResistanceDef);
		TagsToCaptureDefs.Add(GameplayTags.Attributes_Secondary_Resistance_Lightning,	LightningResistanceDef);
	}
};

static const OmegaDamageStatics& DamageStatics()
{
	static OmegaDamageStatics DStatics;
	return DStatics;
};

UExecCalc_Damage::UExecCalc_Damage()
{
	RelevantAttributesToCapture.Add(DamageStatics().PhysicalResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().FireResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().ColdResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().PoisonResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().LightningResistanceDef);
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	
//  LOCAL VARIABLES
// ===============================================================================================================
	
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
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	
	FAggregatorEvaluateParameters EvaluateParams;
	EvaluateParams.SourceTags = SourceTags;
	EvaluateParams.TargetTags = TargetTags;
	
// ===============================================================================================================

	// Get Damage Set by Caller Magnitude
	
	
	// Damage Types adjustment
	for (const auto& DamagePair : GameplayTags.DamageTypesToResistances)
	{
		float Damage = 0.f;
		
		const FGameplayTag& DamageTypeTag = DamagePair.Key;
		const FGameplayTag& DamageResistanceTag = DamagePair.Value;
		
		checkf(OmegaDamageStatics().TagsToCaptureDefs.Contains(DamageResistanceTag), TEXT("%hs: TagsToCaptureDefs doesn't contain Tag: [%s] in ExecCalc_Damage"), __FUNCTION__, *DamageResistanceTag.ToString())
		const FGameplayEffectAttributeCaptureDefinition CaptureDef = OmegaDamageStatics().TagsToCaptureDefs[DamageResistanceTag];

		float DamageTypeValue = Spec.GetSetByCallerMagnitude(DamageTypeTag, false, 0.f);

		if (DamageTypeValue > 0)
		{
			// Evaluate Damage Resistance Magnitude
			float ResistanceMagnitude = 0.f;
			ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(CaptureDef, EvaluateParams, ResistanceMagnitude);
			ResistanceMagnitude = FMath::Clamp(ResistanceMagnitude, 0.f, 100.f);
		
			DamageTypeValue *= (100 - ResistanceMagnitude) / 100;
			Damage += DamageTypeValue;
		
			const FGameplayModifierEvaluatedData EvaluatedData(UOmegaAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Override, Damage);
			OutExecutionOutput.AddOutputModifier(EvaluatedData);	
		}
		
	}
}
