#include "UI/ModularGameplayLayout.h"

#include "CommonUIExtensions.h"
#include "NativeGameplayTags.h"
#include "Input/CommonUIInputTypes.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ModularGameplayLayout)

UE_DEFINE_GAMEPLAY_TAG_STATIC(TAG_UI_LAYER_MENU, "UI.Layer.Menu");
UE_DEFINE_GAMEPLAY_TAG_STATIC(TAG_UI_ACTION_ESCAPE, "UI.Action.Escape");

UModularGameplayLayout::UModularGameplayLayout(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UModularGameplayLayout::HandleEscapeAction()
{
	if (ensure(!EscapeMenuClass.IsNull()))
	{
		UCommonUIExtensions::PushStreamedContentToLayer_ForPlayer(GetOwningLocalPlayer(), TAG_UI_LAYER_MENU, EscapeMenuClass);
	}
}

void UModularGameplayLayout::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	RegisterUIActionBinding(FBindUIActionArgs(
		FUIActionTag::ConvertChecked(TAG_UI_ACTION_ESCAPE),
		false,
		FSimpleDelegate::CreateUObject(this, &ThisClass::HandleEscapeAction))
	);
}

void UModularGameplayLayout::NativeDestruct()
{
	Super::NativeDestruct();
}
