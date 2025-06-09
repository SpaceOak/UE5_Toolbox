// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE_ToolboxStyle.h"
#include "UE_Toolbox.h"
#include "Framework/Application/SlateApplication.h"
#include "Styling/SlateStyleRegistry.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FUE_ToolboxStyle::StyleInstance = nullptr;

void FUE_ToolboxStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FUE_ToolboxStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FUE_ToolboxStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("UE_ToolboxStyle"));
	return StyleSetName;
}


const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);

TSharedRef< FSlateStyleSet > FUE_ToolboxStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("UE_ToolboxStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("UE_Toolbox")->GetBaseDir() / TEXT("Resources"));

	Style->Set("UE_Toolbox.PluginAction", new IMAGE_BRUSH_SVG(TEXT("PlaceholderButtonIcon"), Icon20x20));
	return Style;
}

void FUE_ToolboxStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FUE_ToolboxStyle::Get()
{
	return *StyleInstance;
}
