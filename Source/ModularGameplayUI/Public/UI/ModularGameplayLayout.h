#pragma once
#include "CommonActivatableWidget.h"
#include "ModularInputActivatableWidget.h"
#include "ModularUserWidget.h"
#include "ModularGameplayLayout.generated.h"

/**
 * Gameplay Layouts are sub-layouts meant to slot into layers of a PrimaryGameLayout.
 *
 * These support a constant 'Escape' menu modal along with input loss detection and error screens.
 * Blueprint instances should not have a Blueprint EventGraph or any defined functions. Instead, Game Modes and Player
 * States should rely on CommonUIExtensions methods to place Widgets into these layouts.
 *
 * In order to propagate the tag, you will also need to add an Input Action for UI.Action.Escape.
 * One place to do this is in the Project Settings/Plugins - Common UI Input Settings.
 * If you do, you'll also want to change the Editor Keyboard shortcut for "Play World" to something else,
 * like Shift+Esc.
 *
 * Menus by default rely on CommonInput setup, which means your project should have configured a default
 * set of Input Data in the Common Input Settings.
 *
 * You can see an example of this with the GameFeatureAction_AddWidget class.
 * @see GameFeature/GameFeatureAction_AddWidget
 */
UCLASS(Abstract, BlueprintType, Blueprintable, Meta = (DisplayName = "Modular Gameplay Layout", Category = "HUD"))
class UModularGameplayLayout : public UModularUserWidget
{
	GENERATED_BODY()

public:
	UModularGameplayLayout(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(EditDefaultsOnly, Category = Gameplay)
	TSoftClassPtr<UCommonActivatableWidget> EscapeMenuClass;

	/**
	 * Function delegate to handle an Escape action being detected.
	 *
	 * Will bring up the widget defined by EscapeMenuClass.
	 * To use, create an action binding and register it with the delegate.
	 */
	void HandleEscapeAction();

	/**
	 * @ingroup UUserWidget
	 * @{
	 */
public:
	virtual void NativeOnInitialized() override;
	virtual void NativeDestruct() override;
	/**
	 * @}
	 */
};
