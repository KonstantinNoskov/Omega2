#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "OmegaTypes.h"
#include "OmegaWidgetController.h"
#include "OverlayWidgetController.generated.h"

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
USTRUCT(BlueprintType)
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

	UPROPERTY(BlueprintReadOnly)
	float EffectMagnitude = 0.f;
	
};

class UAttributeInfo;
struct FGameplayTag;
struct FOnAttributeChangeData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageWidgetRowSignature, const FUIWidgetRow, Row);


UCLASS()
class OMEGA_API UOverlayWidgetController : public UOmegaWidgetController
{
	GENERATED_BODY()

public:
	
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;
	
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeInfoChangedSignature OnAttributeInfoChangedDelegate;
	
protected:

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAttributeInfo> AttributeData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widget Data", meta = (RequiredAssetDataTags = "RowStructure=/Script/Omega.UIWidgetRow"))
	TObjectPtr<UDataTable> WidgetMessageDataTable;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Messages")
	FMessageWidgetRowSignature MessageWidgetRowDelegate;
	
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeValueChangedSignature OnHealthChangedDelegate;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeValueChangedSignature OnMaxHealthChangedDelegate;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeValueChangedSignature OnManaChangedDelegate;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeValueChangedSignature OnMaxManaChangedDelegate;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeValueChangedSignature OnStrengthChangedDelegate;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeValueChangedSignature OnIntelligenceChangedDelegate;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeValueChangedSignature OnDexterityChangedDelegate;
};

