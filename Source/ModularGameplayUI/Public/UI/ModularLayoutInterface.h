// Copyright Chronicler.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ModularLayoutInterface.generated.h"

class UModularGameplayLayout;

UINTERFACE(MinimalAPI)
class UModularLayoutInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for returning a reference to a Widget Layout spawned by GameFeatureAction_AddWidget so the HUD widgets
 * can be initialized with information from the widget owner's Ability System.
 */
class MODULARGAMEPLAYUI_API IModularLayoutInterface
{
	GENERATED_BODY()

public:
	virtual UModularGameplayLayout* GetModularGameplayLayout() const = 0;
	virtual void SetModularGameplayLayout(UModularGameplayLayout* InLayout) = 0;



};