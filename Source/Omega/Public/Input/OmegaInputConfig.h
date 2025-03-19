#pragma once

#include "CoreMinimal.h"
#include "OmegaTypes.h"
#include "Engine/DataAsset.h"
#include "OmegaInputConfig.generated.h"

USTRUCT(BlueprintType)
struct FOmegaInputAction
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	const UInputAction* InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag();
};

UCLASS()
class OMEGA_API UOmegaInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:

	const UInputAction* FindAbilityInputActionByTag(const FGameplayTag& InputTag, bool bLogNotFound = false) const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FOmegaInputAction> AbilityInputAction;
};
