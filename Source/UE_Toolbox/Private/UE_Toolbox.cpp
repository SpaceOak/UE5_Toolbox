// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE_Toolbox.h"

#include "EditorUtilitySubsystem.h"
#include "EditorUtilityWidgetBlueprint.h"
#include "UE_ToolboxStyle.h"
#include "UE_ToolboxCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"

#include "Interfaces/IPluginManager.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "IPythonScriptPlugin.h"
static const FName UE_ToolboxTabName("UE_Toolbox");

#define LOCTEXT_NAMESPACE "FUE_ToolboxModule"

void FUE_ToolboxModule::StartupModule()
{
	// Инициализация стиля и команд
	FUE_ToolboxStyle::Initialize();
	FUE_ToolboxStyle::ReloadTextures();

	FUE_ToolboxCommands::Register();

	PluginCommands = MakeShareable(new FUICommandList);
	PluginCommands->MapAction(
		FUE_ToolboxCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FUE_ToolboxModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(
		FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FUE_ToolboxModule::RegisterMenus)
	);

	// --- Python автоинициализация ---
	TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(TEXT("UE_Toolbox"));
	if (!Plugin.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("[UE_Toolbox] Plugin not found."));
		return;
	}

	const FString PluginDir = Plugin->GetBaseDir();
	const FString PythonDir = FPaths::Combine(PluginDir, TEXT("UE5_Python"));

	const TArray<FString> StartupScripts = {
		TEXT("__init__.py"),
		TEXT("startup.py")
	};

	for (const FString& ScriptName : StartupScripts)
	{
		const FString ScriptPath = FPaths::Combine(PythonDir, ScriptName);

		if (!FPaths::FileExists(ScriptPath))
		{
			UE_LOG(LogTemp, Warning, TEXT("[UE_Toolbox] %s not found: %s"), *ScriptName, *ScriptPath);
			continue;
		}

		FString ScriptContent;
		if (!FFileHelper::LoadFileToString(ScriptContent, *ScriptPath))
		{
			UE_LOG(LogTemp, Error, TEXT("[UE_Toolbox] Failed to read: %s"), *ScriptPath);
			continue;
		}

		if (IPythonScriptPlugin::Get())
		{
			IPythonScriptPlugin::Get()->ExecPythonCommand(*ScriptContent);
			UE_LOG(LogTemp, Log, TEXT("[UE_Toolbox] Executed %s from: %s"), *ScriptName, *ScriptPath);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("[UE_Toolbox] Python plugin not available."));
			break;
		}
	}
}


void FUE_ToolboxModule::PluginButtonClicked()
{
	FString WidgetAssetPath = TEXT("/UE_Toolbox/UI/WBP_ToolboxMain.WBP_ToolboxMain");
	UEditorUtilityWidgetBlueprint* WidgetBP = Cast<UEditorUtilityWidgetBlueprint>(
		StaticLoadObject(UEditorUtilityWidgetBlueprint::StaticClass(), nullptr, *WidgetAssetPath));

	if (WidgetBP)
	{
		UEditorUtilitySubsystem* EditorUtilitySubsystem = GEditor->GetEditorSubsystem<UEditorUtilitySubsystem>();
		if (EditorUtilitySubsystem)
		{
			EditorUtilitySubsystem->SpawnAndRegisterTab(WidgetBP);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Could not find Editor Utility Widget at path: %s"), *WidgetAssetPath);
	}
}







void FUE_ToolboxModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FUE_ToolboxStyle::Shutdown();

	FUE_ToolboxCommands::Unregister();
}



void FUE_ToolboxModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FUE_ToolboxCommands::Get().PluginAction, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("PluginTools");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FUE_ToolboxCommands::Get().PluginAction));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FUE_ToolboxModule, UE_Toolbox)