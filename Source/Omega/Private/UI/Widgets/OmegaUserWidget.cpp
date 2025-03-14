#include "UI/Widgets/OmegaUserWidget.h"


void UOmegaUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	
	OnWidgetControllerSet();
}

