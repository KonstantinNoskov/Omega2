#include "UI/WidgetControllers/OmegaWidgetController.h"

#include "OmegaTypes.h"

void UOmegaWidgetController::SetWidgetControllerParameters(const FWidgetControllerParams& InParams)
{
	PlayerController = InParams.PlayerController;
	PlayerState = InParams.PlayerState;
	AbilitySystemComponent = InParams.AbilitySystemComponent;
	AttributeSet = InParams.AttributeSet;
}

void UOmegaWidgetController::BroadcastInitialValues() {}

void UOmegaWidgetController::BindCallbacksToDependencies() {}
