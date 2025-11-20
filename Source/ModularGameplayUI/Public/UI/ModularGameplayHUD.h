// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ModularLayoutInterface.h"
#include "GameFramework/HUD.h"
#include "ModularUserWidget.h"
#include "ModularWidgetController.h"
#include "ModularGameplayHUD.generated.h"


class UAttributeSet;
class UModularAbilitySystemComponent;
class AModularPlayerState;
class AModularPlayerController;
struct FWidgetControllerParams;

namespace EEndPlayReason { enum Type : int; }

class AActor;
class UObject;
class UModularUserWidget;
struct FTimerHandle;

/**
 * AModularGameplayHUD
 *
 * Decorator class that adds debug methods to the regular HUD class.
 *
 * @note You typically do not need to extend or modify this class, instead you would
 * use an "Add Widget" action in your experience to add a HUD layout and widgets to it.
 */
UCLASS(Config = Game)
class MODULARGAMEPLAYUI_API AModularGameplayHUD : public AHUD, public IModularLayoutInterface
{
	GENERATED_BODY()

public:
	explicit AModularGameplayHUD(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UPROPERTY()
	TObjectPtr<UModularUserWidget> OverlayWidget;
	
	UModularWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);

	void InitOverlay(AModularPlayerController* PC, AModularPlayerState* PS, UModularAbilitySystemComponent* ASC,const UAttributeSet* AS);

	UPROPERTY(EditAnywhere)
	TSubclassOf<UModularUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UModularWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UModularWidgetController> OverlayWidgetControllerClass;

	virtual UModularGameplayLayout* GetModularGameplayLayout() const override { return ModularGameplayLayout; }
	virtual void SetModularGameplayLayout(UModularGameplayLayout* InLayout) override;

protected:

	//~UObject interface
	virtual void PreInitializeComponents() override;
	//~End of UObject interface

	//~AActor interface
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	//~End of AActor interface

	//~AHUD interface
	virtual void GetDebugActorList(TArray<AActor*>& InOutList) override;
	//~End of AHUD interface

	UPROPERTY()
	UModularGameplayLayout* ModularGameplayLayout;

private:
	// Timer used to retry overlay initialization until ModularGameplayLayout becomes available
	FTimerHandle OverlayInitRetryTimerHandle;
	
};
