#pragma once

#include "CoreMinimal.h"
#include "OmegaTypes.h"
#include "Engine/DataAsset.h"
#include "AttributeInfo.generated.h"

/**
 * Attribute data broadcasted to the widgets
 */
USTRUCT(BlueprintType)
struct FOmegaAttributeInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AttributeTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeName = FText();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeDescription = FText();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeAbbreviation = FText();

	UPROPERTY(BlueprintReadOnly)
	float AttributeValue = 0.f;
};


UCLASS()
class OMEGA_API UAttributeInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, DisplayName = "Primary")
	TMap<FName, FOmegaAttributeInfo> PrimaryAttributesInfo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, DisplayName = "Secondary")
	TMap<FName, FOmegaAttributeInfo> SecondaryAttributesInfo;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, DisplayName = "Tertiary")
	TMap<FName, FOmegaAttributeInfo> TertiaryAttributesInfo;
	
	FOmegaAttributeInfo FindAttributeInfoByTag(const FGameplayTag& AttributeTag, bool bLogNotFound = false);
};
