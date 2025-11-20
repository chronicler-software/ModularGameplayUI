// Copyright Chronicler.


#include "UI/ModularUserWidget.h"

void UModularUserWidget::SetWidgetController(UObject* NewWidgetController)
{
	WidgetController = NewWidgetController;
	WidgetControllerSet();
}
