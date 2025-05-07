#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "CharacterDefaultInfo.generated.h"

class UGameplayAbility;
class UGameplayEffect;

/*USTRUCT()
struct FCharacterTypeDefaultInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Class Defaults")
	TSubclassOf<UGameplayEffect> PrimaryAttributes;

	UPROPERTY(EditDefaultsOnly, Category = "Class Defaults")
	TSubclassOf<UGameplayEffect> SecondaryAttributes;
};*/

USTRUCT()
struct FCharacterTypeDefaultInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Class Defaults")
	TSubclassOf<UGameplayEffect> PrimaryAttributes;

	UPROPERTY(EditDefaultsOnly, Category = "Class Defaults")
	TSubclassOf<UGameplayEffect> SecondaryAttributes;
	
};

UCLASS()
class OMEGA_API UCharacterDefaultInfo : public UDataAsset
{
	GENERATED_BODY()

public:
 
	UPROPERTY(EditDefaultsOnly, Category = "Modify Attributes by Tag", meta=(ForceInlineRow))
	TMap<FGameplayTag, TSubclassOf<UGameplayEffect>> AttributeByTagMap;
	
	UPROPERTY(EditDefaultsOnly, Category = "Class Defaults")
	TMap<FGameplayTag, FCharacterTypeDefaultInfo> CharacterClassInformation;
	
	const FCharacterTypeDefaultInfo& GetClassDefaultInfo(const FGameplayTag& CharacterClass);
	
	UPROPERTY(EditDefaultsOnly, Category = "Class Defaults")
	TSubclassOf<UGameplayEffect> SecondaryAttributes;

	UPROPERTY(EditDefaultsOnly, Category = "Common Abilities")
	TArray<TSubclassOf<UGameplayAbility>> CommonAbilities;
};
