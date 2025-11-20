// Copyright Chronicler.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"

#include "ModularWidgetController.generated.h"

class AModularPlayerController;
class AModularPlayerState;
class UModularAbilitySystemComponent;
class UAttributeSet;


USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY()
	
	FWidgetControllerParams() {}
	FWidgetControllerParams(AModularPlayerController* PC,
		AModularPlayerState* PS,
		UModularAbilitySystemComponent* ASC,
		const UAttributeSet* AS)
	: PlayerController(PC), PlayerState(PS), AbilitySystemComponent(ASC), AttributeSet(AS) {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<AModularPlayerController> PlayerController = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<AModularPlayerState> PlayerState = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UModularAbilitySystemComponent> AbilitySystemComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<const UAttributeSet> AttributeSet = nullptr;
};
/**
 * Base class for WidgetControllers. Contains a struct for WidgetControllerParams to tie into the
 * ModularAbilitySystem. WidgetControllerParams returns a generic AttributeSet, in child classes,
 * cast to the relevant AttributeSet class to bind to Attributes.
 *
 * This allows you to assign a controller for any widget that is tied directly into the Ability System.
 * Works for both players and non-player characters.
 */
UCLASS()
class MODULARGAMEPLAYUI_API UModularWidgetController : public UObject
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable)
	virtual void SetWidgetControllerParams(const FWidgetControllerParams& WidgetControllerParams);
	
	virtual void BroadcastInitialValues();
	virtual void BindCallbacksToDependancies();

	protected:

	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<AModularPlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<AModularPlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<UModularAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<const UAttributeSet> AttributeSet;
};
