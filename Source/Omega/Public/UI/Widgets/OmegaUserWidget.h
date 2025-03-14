#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OmegaUserWidget.generated.h"

struct FWidgetControllerParams;
class UOmegaWidgetController;

UCLASS()
class OMEGA_API UOmegaUserWidget : public UUserWidget
{
	GENERATED_BODY()

	
protected:
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnWidgetControllerSet();

public:

	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;

	
	
		
};
