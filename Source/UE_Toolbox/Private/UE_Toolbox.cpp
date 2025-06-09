// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE_Toolbox.h"
#include "UE_ToolboxStyle.h"
#include "UE_ToolboxCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"

static const FName UE_ToolboxTabName("UE_Toolbox");

#define LOCTEXT_NAMESPACE "FUE_ToolboxModule"

void FUE_ToolboxModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FUE_ToolboxStyle::Initialize();
	FUE_ToolboxStyle::ReloadTextures();

	FUE_ToolboxCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FUE_ToolboxCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FUE_ToolboxModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FUE_ToolboxModule::RegisterMenus));
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

void FUE_ToolboxModule::PluginButtonClicked()
{
	// Put your "OnButtonClicked" stuff here
	FText DialogText = FText::Format(
							LOCTEXT("PluginButtonDialogText", "Add code to {0} in {1} to override this button's actions"),
							FText::FromString(TEXT("FUE_ToolboxModule::PluginButtonClicked()")),
							FText::FromString(TEXT("UE_Toolbox.cpp"))
					   );
	FMessageDialog::Open(EAppMsgType::Ok, DialogText);
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