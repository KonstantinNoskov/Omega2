#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_MaxMana.generated.h"

UCLASS()
class OMEGA_API UMMC_MaxMana : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:
	
	UMMC_MaxMana();
	
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mana", DisplayName = "Initial Mana", meta = (AllowPrivateAccess = "true", ClampMin = 0.f))
	float InitialMana = 1.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mana", DisplayName = "Player Level Multiplier", meta = (AllowPrivateAccess = "true", ClampMin = 0.f))
	float PlayerLevelScale = 1.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mana", DisplayName = "Intelligence Multiplier", meta = (AllowPrivateAccess = "true", ClampMin = 0.f))
	float IntelligenceScale = 1.f;
	

	FGameplayEffectAttributeCaptureDefinition IntelligenceDef;
	
};
