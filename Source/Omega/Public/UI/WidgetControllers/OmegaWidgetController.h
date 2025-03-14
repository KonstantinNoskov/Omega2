#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "OmegaWidgetController.generated.h"

struct FWidgetControllerParams;
class UAbilitySystemComponent;
class UAttributeSet;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeValueChangedSignature, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeInfoChangedSignature, const FOmegaAttributeInfo&, Info);

UCLASS(Blueprintable, BlueprintType)
class OMEGA_API UOmegaWidgetController : public UObject
{
	GENERATED_BODY()

public:

	void SetWidgetControllerParameters(const FWidgetControllerParams& InParams);
	virtual void BroadcastInitialValues();
	
	virtual void BindCallbacksToDependencies();

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Widget Controller")
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly, Category = "Widget Controller")
	TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly, Category = "Widget Controller")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category = "Widget Controller")
	TObjectPtr<UAttributeSet> AttributeSet;
	
};
