#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_MaxHealth.generated.h"

UCLASS(BlueprintType)
class OMEGA_API UMMC_MaxHealth : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
	
public:
	
	UMMC_MaxHealth();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health", DisplayName = "Initial Health", meta = (AllowPrivateAccess = "true", ClampMin = 0.f))
	float InitialHealth = 1.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health", DisplayName = "Player Level Multiplier", meta = (AllowPrivateAccess = "true", ClampMin = 0.f))
	float PlayerLevelScale = 1.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health", DisplayName = "Strength Multiplier", meta = (AllowPrivateAccess = "true", ClampMin = 0.f))
	float StrengthScale = 1.f;
	

	FGameplayEffectAttributeCaptureDefinition StrengthDef;
	
};
