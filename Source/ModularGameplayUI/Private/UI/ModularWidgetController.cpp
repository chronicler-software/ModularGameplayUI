// Copyright Chronicler.


#include "UI/ModularWidgetController.h"

void UModularWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WidgetControllerParams)
{
		PlayerController = WidgetControllerParams.PlayerController;
		PlayerState = WidgetControllerParams.PlayerState;
		AbilitySystemComponent = WidgetControllerParams.AbilitySystemComponent;
		AttributeSet = WidgetControllerParams.AttributeSet;
}

void UModularWidgetController::BroadcastInitialValues()
{
	// Fill this out in child classes.
}

void UModularWidgetController::BindCallbacksToDependancies()
{
	// Fill this out in child classes.
}
