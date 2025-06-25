#include "UE_Toolbox/Public/ToolModes/MaterialAuditToolMode.h"
#include "Audit/MaterialAuditManager.h"
#include "Audit/AuditSubsystem.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"

FMaterialAuditToolMode::FMaterialAuditToolMode()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClassFinder(TEXT("/FluffyGuacamole/UI/W_Audit_Materials"));
	if (WidgetClassFinder.Succeeded())
	{
		WidgetClass = WidgetClassFinder.Class;
	}
}

TSubclassOf<UUserWidget> FMaterialAuditToolMode::GetWidgetClass() const
{
	return WidgetClass;
}

void FMaterialAuditToolMode::Initialize()
{
	if (bInitialized)
		return;

	if (UMaterialAuditManager* Manager = UMaterialAuditManager::Get())
	{
		Manager->Initialize();
		Manager->InitializeMaterials();
	}
}

FName FMaterialAuditToolMode::GetModeName() const
{
	return "MaterialAudit";
}
