// Copyright Chronicler.

#pragma once

#include "CoreMinimal.h"
#include "ModularInputActivatableWidget.h"
#include "ModularUserWidget.generated.h"

/**
 * UserWidget class that adds a WidgetController.
 * @see UI/ModularWidgetController.
 */
UCLASS()
class MODULARGAMEPLAYUI_API UModularUserWidget : public UModularInputActivatableWidget
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* NewWidgetController);
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;

protected:

	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
};
