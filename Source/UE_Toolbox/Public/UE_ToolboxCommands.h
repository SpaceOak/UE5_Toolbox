// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "UE_ToolboxStyle.h"

class FUE_ToolboxCommands : public TCommands<FUE_ToolboxCommands>
{
public:

	FUE_ToolboxCommands()
		: TCommands<FUE_ToolboxCommands>(TEXT("UE_Toolbox"), NSLOCTEXT("Contexts", "UE_Toolbox", "UE_Toolbox Plugin"), NAME_None, FUE_ToolboxStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
