#include "Audit/MaterialAuditManager.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Materials/Material.h"
#include "Materials/MaterialInstance.h"
#include "Materials/MaterialInterface.h"
#include "MaterialEditingLibrary.h"
#include "MaterialStatsCommon.h"
#include "MaterialStatsCommon.h"
#include "MaterialEditor/PreviewMaterial.h"

UMaterialAuditManager::UMaterialAuditManager()
{
    InitializeMaterials();
}

void UMaterialAuditManager::InitializeMaterials()
{
    if (bIsInitialized)
        return;

    Materials.Empty();

    FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");

    // Новый UE5 способ!
    TArray<FTopLevelAssetPath> ClassPaths = {
        UMaterial::StaticClass()->GetClassPathName(),
        UMaterialInstance::StaticClass()->GetClassPathName()
    };
    FARFilter Filter;
    Filter.ClassPaths = ClassPaths;
    Filter.bRecursiveClasses = true;

    TArray<FAssetData> AssetDataList;
    AssetRegistryModule.Get().GetAssets(Filter, AssetDataList);

    for (const FAssetData& AssetData : AssetDataList)
    {
        FMaterialAuditInfo Info;
        Info.Asset = AssetData.GetAsset();
        Info.Path = AssetData.GetObjectPathString();
        Info.Name = AssetData.AssetName.ToString();

        if (UMaterialInterface* Mat = Cast<UMaterialInterface>(Info.Asset))
        {
            Info.BlendMode = Mat->GetBlendMode();
            Info.bIsInstance = Mat->IsA<UMaterialInstance>();
            Info.Stats = UMaterialEditingLibrary::GetStatistics(Mat);
        }
        else
        {
            Info.Stats = FMaterialStatistics();
        }

        Materials.Add(Info);
    }

    bIsInitialized = true;
}

TArray<FMaterialAuditInfo> UMaterialAuditManager::GetFilteredMaterials()
{
    if (!bIsInitialized)
        InitializeMaterials();

    TArray<FMaterialAuditInfo> Result;
    for (const FMaterialAuditInfo& Info : Materials)
    {
        bool bPassesAll = true;
        for (const UMaterialAuditBaseFilter* Filter : Filters)
        {
            if (Filter && !IMaterialAuditFilterInterface::Execute_PassesFilter(Filter, Info))
            {
                bPassesAll = false;
                break;
            }
        }
        if (bPassesAll)
            Result.Add(Info);
    }
    return Result;
}
