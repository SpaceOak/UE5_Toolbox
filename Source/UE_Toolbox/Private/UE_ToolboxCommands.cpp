// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE_ToolboxCommands.h"

#define LOCTEXT_NAMESPACE "FUE_ToolboxModule"

void FUE_ToolboxCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "UE_Toolbox", "Execute UE_Toolbox action", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
