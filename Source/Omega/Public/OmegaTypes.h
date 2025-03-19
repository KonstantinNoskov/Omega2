#pragma once

#include "GameplayEffectTypes.h"
#include "OmegaTypes.generated.h"


class UInputAction;
class UPaperSprite;
class UOmegaUserWidget;
class UAttributeSet;
class UAbilitySystemComponent;

/*
 * Used to handle gameplay effect apply conditions
 */
UENUM(BlueprintType)
enum class EEffectApplicationPolicy : uint8
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};

/*
 * Used to handle gameplay effect removal conditions
 */
UENUM(BlueprintType)
enum class EEffectRemovalPolicy : uint8
{
	RemoveOnOverlap,
	RemoveOnEndOverlap,
	DoNotRemove
};

UENUM(BlueprintType)
enum class EOmegaCustomMovementMode : uint8
{
	None,
	Dash,
	Mantle
};

/*
 * Stores essentials params to setup widget controllers
 */
USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY()

	FWidgetControllerParams()
	{}
	
	FWidgetControllerParams(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS) :
	PlayerController(PC),
	PlayerState(PS),
	AbilitySystemComponent(ASC),
	AttributeSet(AS)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerController> PlayerController = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerState> PlayerState = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAttributeSet> AttributeSet = nullptr;
};

/*
 * 
 */
USTRUCT(BlueprintType)
struct FEffectProperties
{
	GENERATED_BODY()

	FEffectProperties(){}
	
	FGameplayEffectContextHandle EffectContextHandle;

	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;

	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;

	UPROPERTY()
	AController* SourceController = nullptr;

	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;
	
	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;

	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;

	UPROPERTY()
	AController* TargetController = nullptr;

	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;
	
};

/*
 * Stores icon info for gameplay effect message widget
 */
USTRUCT(BlueprintType)
struct FMessageIconData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperSprite* Sprite = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D Size = FVector2D(0.f,0.f);
};


/*
 *	Data to display on overlay widget on gameplay tag update 
 */
USTRUCT()
struct FUIWidgetRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag MessageTag = FGameplayTag();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Message = FText();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UOmegaUserWidget> MessageWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FMessageIconData MessageIconData;
	
};

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

	UPROPERTY(BlueprintReadOnly)
	float AttributeValue = 0.f;
};




