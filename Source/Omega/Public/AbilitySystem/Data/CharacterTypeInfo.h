#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "CharacterTypeInfo.generated.h"

class UGameplayAbility;
class UGameplayEffect;

USTRUCT()
struct FCharacterTypeDefaultInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Class Defaults")
	TSubclassOf<UGameplayEffect> PrimaryAttributes;
	
};


UCLASS()
class OMEGA_API UCharacterTypeInfo : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category = "Class Defaults")
	TMap<FGameplayTag, FCharacterTypeDefaultInfo> CharacterClassInformation;
	
	const FCharacterTypeDefaultInfo& GetClassDefaultInfo(const FGameplayTag& CharacterClass);

	UPROPERTY(EditDefaultsOnly, Category = "Class Defaults")
	TSubclassOf<UGameplayEffect> SecondaryAttributes;

	UPROPERTY(EditDefaultsOnly, Category = "Common Abilities")
	TArray<TSubclassOf<UGameplayAbility>> CommonAbilities;
};
