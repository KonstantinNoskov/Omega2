#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "CharacterDefaultInfo.generated.h"

class UGameplayAbility;
class UGameplayEffect;

UENUM(BlueprintType)
enum class ECharacterClass : uint8
{
	Melee  UMETA(DisplayName = "Melee"),
	Range  UMETA(DisplayName = "Range")
};

USTRUCT()
struct FCharacterTypeInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, Category = "Class Defaults")
	TSubclassOf<UGameplayEffect> AttributesModifyEffect;
};

UCLASS()
class OMEGA_API UCharacterDefaultInfo : public UDataAsset
{
	GENERATED_BODY()

public:

	const FCharacterTypeInfo& GetCharacterTypeInfo(const FGameplayTag& CharacterTypeClass);

	UPROPERTY(EditDefaultsOnly, Category = "Character Class Defaults", DisplayName = "ClassAbilities", meta=(ForceInlineRow))
	TMap<FGameplayTag, TSubclassOf<UGameplayAbility>> CharacterClassAbilities;
	
	UPROPERTY(EditDefaultsOnly, Category = "Character Class Defaults", DisplayName = "TypeInfo", meta=(ForceInlineRow))
	TMap<FGameplayTag, FCharacterTypeInfo> CharacterTypeInfo;
	
	UPROPERTY(EditDefaultsOnly, Category = "Common Abilities")
	TArray<TSubclassOf<UGameplayAbility>> CommonAbilities;
};
