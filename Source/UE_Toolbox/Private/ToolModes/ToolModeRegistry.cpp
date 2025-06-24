#include "UE_Toolbox/Public/ToolModes/ToolModeRegistry.h"

#include "ToolModes/IToolMode.h"

TMap<FName, FToolModeRegistry::FToolModeFactory>& FToolModeRegistry::GetRegistry()
{
	static TMap<FName, FToolModeFactory> Registry;
	return Registry;
}

void FToolModeRegistry::Register(FName ModeName, FToolModeFactory Factory)
{
	GetRegistry().Add(ModeName, MoveTemp(Factory));
}

TArray<FName> FToolModeRegistry::GetAvailableModes()
{
	TArray<FName> Keys;
	GetRegistry().GetKeys(Keys);
	return Keys;
}

TSharedPtr<IToolMode> FToolModeRegistry::CreateMode(FName ModeName)
{
	if (FToolModeFactory* Factory = GetRegistry().Find(ModeName))
	{
		return (*Factory)();
	}
	return nullptr;
}
