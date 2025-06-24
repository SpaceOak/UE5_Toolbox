#include "Audit/MaterialAuditManager.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Materials/Material.h"
#include "Materials/MaterialInstance.h"
#include "Materials/MaterialInterface.h"
#include "MaterialEditingLibrary.h"
#include "MaterialStatsCommon.h"
#include "MaterialEditor/PreviewMaterial.h"

UMaterialAuditManager::UMaterialAuditManager()
{
   // InitializeMaterials();
}




UMaterialAuditManager* UMaterialAuditManager::Instance = nullptr;

UMaterialAuditManager* UMaterialAuditManager::Get()
{
    if (!Instance)
    {
        Instance = NewObject<UMaterialAuditManager>();
        Instance->AddToRoot(); // защита от GC
    }
    return Instance;
}

void UMaterialAuditManager::Initialize()
{
    UE_LOG(LogTemp, Log, TEXT("[MaterialAuditManager] Initialized"));
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

        if (!AssetData.IsValid())
        {
            UE_LOG(LogTemp, Warning, TEXT("[MaterialAuditManager] Invalid AssetData encountered"));
            continue;
        }
        
        Info.Asset = AssetData.GetAsset();
        Info.Path = AssetData.GetObjectPathString();
        Info.Name = AssetData.AssetName.ToString();

        if (UMaterialInterface* Mat = Cast<UMaterialInterface>(Info.Asset))
        {
            Info.BlendMode = Mat->GetBlendMode();
            Info.bIsInstance = Mat->IsA<UMaterialInstance>();
            Info.Stats = UMaterialEditingLibrary::GetStatistics(Mat);

            // --- Домен и шейдинг модел ---
            if (UMaterial* BaseMat = Cast<UMaterial>(Mat))
            {
                Info.MaterialDomain = BaseMat->MaterialDomain;
                Info.ShadingModel = BaseMat->GetShadingModels().GetFirstShadingModel();
            }
            else if (UMaterialInstance* Inst = Cast<UMaterialInstance>(Mat))
            {
                // Для инстансов тянем из Parent
                if (UMaterial* ParentMat = Inst->GetMaterial())
                {
                    Info.MaterialDomain = ParentMat->MaterialDomain;
                    Info.ShadingModel = ParentMat->GetShadingModels().GetFirstShadingModel();
                }
            }
        }
        else
        {
            Info.Stats = FMaterialStatistics();
        }

        Materials.Add(Info);
    }

    bIsInitialized = true;
}

void UMaterialAuditManager::SetAnalyzeCurrentLevelOnly(bool bOnlyCurrentLevel)
{
    bAnalyzeCurrentLevelOnly = bOnlyCurrentLevel;
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
