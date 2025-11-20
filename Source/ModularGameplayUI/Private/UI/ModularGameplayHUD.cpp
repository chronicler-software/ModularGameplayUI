// Copyright Epic Games, Inc. All Rights Reserved.

#include "UI/ModularGameplayHUD.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "ModularAbilityPlayerState.h"
#include "ActorComponent/ModularAbilitySystemComponent.h"

#include "Async/TaskGraphInterfaces.h"

#include "Components/GameFrameworkComponentManager.h"
#include "UI/ModularGameplayLayout.h"
#include "UObject/UObjectIterator.h"
#include "TimerManager.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ModularGameplayHUD)


class AModularAbilityPlayerState;
class UAbilitySystemComponent;
class UKulaPlayerAttributeSet;
class AKulaPlayerState;
class APlayerCharacter;
class AActor;
class UWorld;

AModularGameplayHUD::AModularGameplayHUD(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, ModularGameplayLayout(nullptr)
{
	PrimaryActorTick.bStartWithTickEnabled = false;
}

UModularWidgetController* AModularGameplayHUD::GetOverlayWidgetController(
	const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UModularWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		OverlayWidgetController->BindCallbacksToDependancies();
		return OverlayWidgetController;
	}
	return OverlayWidgetController;
}

void AModularGameplayHUD::InitOverlay(AModularPlayerController* PC, AModularPlayerState* PS,
	UModularAbilitySystemComponent* ASC, const UAttributeSet* AS)
{
	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UModularWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);

	ModularGameplayLayout = GetModularGameplayLayout();
	if (ModularGameplayLayout == nullptr)
	{
		if (UWorld* World = GetWorld())
		{
			FTimerManager& TM = World->GetTimerManager();
			if (!TM.IsTimerActive(OverlayInitRetryTimerHandle))
			{
				FTimerDelegate RetryDelegate;
				RetryDelegate.BindUObject(this, &AModularGameplayHUD::InitOverlay, PC, PS, ASC, AS);
				TM.SetTimer(OverlayInitRetryTimerHandle, RetryDelegate, 0.05f, true);
			}
		}
		return;
	}

	// Layout is available, stop any pending retry timer
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(OverlayInitRetryTimerHandle);
	}

	ModularGameplayLayout->SetWidgetController(WidgetController);
	WidgetController->BroadcastInitialValues();
}

void AModularGameplayHUD::SetModularGameplayLayout(UModularGameplayLayout* InLayout)
{
	ModularGameplayLayout = InLayout;
}

void AModularGameplayHUD::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	UGameFrameworkComponentManager::AddGameFrameworkComponentReceiver(this);
}

void AModularGameplayHUD::BeginPlay()
{
	UGameFrameworkComponentManager::SendGameFrameworkComponentExtensionEvent(this, UGameFrameworkComponentManager::NAME_GameActorReady);

	Super::BeginPlay();
}

void AModularGameplayHUD::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UGameFrameworkComponentManager::RemoveGameFrameworkComponentReceiver(this);

	// Ensure any pending retry timer is cleared on end play
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(OverlayInitRetryTimerHandle);
	}

	Super::EndPlay(EndPlayReason);
}

void AModularGameplayHUD::GetDebugActorList(TArray<AActor*>& InOutList)
{
	UWorld* World = GetWorld();

	Super::GetDebugActorList(InOutList);

	// Add all actors with an ability system component.
	for (TObjectIterator<UAbilitySystemComponent> It; It; ++It)
	{
		if (const UAbilitySystemComponent* ASC = *It)
		{
			if (!ASC->HasAnyFlags(RF_ClassDefaultObject | RF_ArchetypeObject))
			{
				AActor* AvatarActor = ASC->GetAvatarActor();
				AActor* OwnerActor = ASC->GetOwnerActor();

				if (AvatarActor && UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(AvatarActor))
				{
					AddActorToDebugList(AvatarActor, InOutList, World);
				}
				else if (OwnerActor && UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(OwnerActor))
				{
					AddActorToDebugList(OwnerActor, InOutList, World);
				}
			}
		}
	}
}
