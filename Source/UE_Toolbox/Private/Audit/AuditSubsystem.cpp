#include "Audit/AuditSubsystem.h"
#include "Audit/MaterialAuditInfoObject.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"

UMaterialAuditInfoObject* UAuditSubsystem::AddMaterialTestEntry(const FString& Name, const FString& Path)
{
	UMaterialAuditInfoObject* InfoObject = NewObject<UMaterialAuditInfoObject>(this);
	InfoObject->Data.Name = Name;
	InfoObject->Data.Path = Path;
	MaterialAuditObjects.Add(InfoObject);
	return InfoObject;
}

void UAuditSubsystem::ClearMaterialAudits()
{
	MaterialAuditObjects.Empty();
}
