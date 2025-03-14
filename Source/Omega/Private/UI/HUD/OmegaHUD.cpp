#include "UI/HUD/OmegaHUD.h"

#include "OmegaTypes.h"
#include "UI/Widgets/OmegaUserWidget.h"
#include "Blueprint/UserWidget.h"
#include "UI/WidgetControllers/OverlayWidgetController.h"

void AOmegaHUD::BeginPlay()
{
	Super::BeginPlay();
}

void AOmegaHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass,				TEXT("[%hs]: HUD OverlayWidgetClass property is null!"), __FUNCTION__)
	checkf(OverlayWidgetControllerClass,	TEXT("[%hs]: HUD OverlayWidgetControllerClass property is null!"), __FUNCTION__)

	// Creating overlay widget
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UOmegaUserWidget>(Widget);
	
	// Get essential params for overlay widget controller
	const FWidgetControllerParams WCParams(PC, PS, ASC, AS);

	// Creating overlay widget controller 
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WCParams);

	// Assign widget controller params to overlay widget controller
	OverlayWidget->SetWidgetController(WidgetController);

	// Set Initial values for overlay widget
	WidgetController->BroadcastInitialValues();
	
	// Add widget with assigned widget controller to the viewport
	OverlayWidget->AddToViewport();
}

UOverlayWidgetController* AOmegaHUD::GetOverlayWidgetController(const FWidgetControllerParams& InParams)
{
	if (!OverlayWidgetController )
	{
		// Create a widget controller if we don't have one yet
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);

		// Pass-in params
		OverlayWidgetController->SetWidgetControllerParameters(InParams);

		// Bind dependencies
		OverlayWidgetController->BindCallbacksToDependencies();
	}

	return OverlayWidgetController;
}



