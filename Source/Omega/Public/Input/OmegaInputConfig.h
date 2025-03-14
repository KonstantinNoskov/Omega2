#pragma once

#include "CoreMinimal.h"
#include "OmegaTypes.h"
#include "Engine/DataAsset.h"
#include "OmegaInputConfig.generated.h"


UCLASS()
class OMEGA_API UOmegaInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:

	const UInputAction* FindAbilityInputActionByTag(const FGameplayTag& InputTag, bool bLogNotFound = false) const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FOmegaInputAction> AbilityInputAction;
};
