#pragma once

#include "GameplayEffectTypes.h"
#include "OmegaTypes.generated.h"


class UInputAction;
class UPaperSprite;
class UOmegaUserWidget;
class UAttributeSet;
class UAbilitySystemComponent;


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
 * 
 */
USTRUCT(BlueprintType, Blueprintable)
struct FDamageEffectContextData
{
	GENERATED_BODY()

	FDamageEffectContextData(){}

	UPROPERTY(BlueprintReadOnly)
	float Damage = 0.f;

	UPROPERTY(BlueprintReadOnly)
	bool bImmune = false;

	UPROPERTY(BlueprintReadOnly)
	bool bBlocked = false;

	UPROPERTY(BlueprintReadOnly)
	bool bParried = false;
	
};







