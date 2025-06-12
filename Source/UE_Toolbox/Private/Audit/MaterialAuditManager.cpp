#include "Audit/MaterialAuditManager.h"

void UMaterialAuditManager::AddTestEntry(const FString& Name, const FString& Path)
{
	FMaterialAuditInfo Info;
	Info.Name = Name;
	Info.Path = Path;
	Materials.Add(Info);
}

TArray<FMaterialAuditInfo> UMaterialAuditManager::GetFilteredMaterials() const
{
	TArray<FMaterialAuditInfo> Result;
	for (const FMaterialAuditInfo& Info : Materials)
	{
		bool bPassesAll = true;
		for (const UMaterialAuditBaseFilter* Filter : Filters)
		{
			if (Filter && !Filter->PassesFilter(Info))
			{
				bPassesAll = false;
				break;
			}
		}
		if (bPassesAll)
		{
			Result.Add(Info);
		}
	}
	return Result;
}
