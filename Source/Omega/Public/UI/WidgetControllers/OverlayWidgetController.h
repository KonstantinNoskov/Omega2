#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "OmegaTypes.h"
#include "OmegaWidgetController.h"
#include "OverlayWidgetController.generated.h"


class UAttributeInfo;
struct FGameplayTag;
struct FOnAttributeChangeData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageWidgetRowSignature, FUIWidgetRow, Row);

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
	
	template<typename T>
	T* GetDataTableRowByTag(UDataTable* InDataTable, const FGameplayTag& InTag);

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


