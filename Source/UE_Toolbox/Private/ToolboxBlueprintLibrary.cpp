#include "ToolboxBlueprintLibrary.h"
#include "ToolModes/ToolModeRegistry.h"
#include "ToolModes/IToolMode.h"
#include "Blueprint/UserWidget.h"

TArray<FName> UToolboxBlueprintLibrary::GetAvailableToolModes()
{
	return FToolModeRegistry::GetAvailableModes();
}

UUserWidget* UToolboxBlueprintLibrary::CreateToolModeWidget(UObject* WorldContext, FName ModeName)
{
	if (!WorldContext)
	{
		UE_LOG(LogTemp, Error, TEXT("[ToolboxBPLibrary] Invalid context."));
		return nullptr;
	}

	TSharedPtr<IToolMode> Mode = FToolModeRegistry::CreateMode(ModeName);
	if (!Mode.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("[ToolboxBPLibrary] No ToolMode found for name: %s"), *ModeName.ToString());
		return nullptr;
	}

	Mode->Initialize();

	TSubclassOf<UUserWidget> WidgetClass = Mode->GetWidgetClass();
	if (!WidgetClass)
	{
		UE_LOG(LogTemp, Error, TEXT("[ToolboxBPLibrary] WidgetClass is null for mode: %s"), *ModeName.ToString());
		return nullptr;
	}

	UWorld* World = GEngine ? GEngine->GetWorldFromContextObjectChecked(WorldContext) : nullptr;
	if (!World)
	{
		UE_LOG(LogTemp, Error, TEXT("[ToolboxBPLibrary] Could not resolve UWorld from context."));
		return nullptr;
	}

	return CreateWidget<UUserWidget>(World, WidgetClass);
}
