#include "Audit/MaterialAuditManager.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Materials/Material.h"
#include "Materials/MaterialInstance.h"
#include "Materials/MaterialInterface.h"
#include "MaterialEditingLibrary.h"
#include "MaterialStatsCommon.h"
#include "MaterialEditor/PreviewMaterial.h"
#include "Misc/ScopedSlowTask.h"

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
    UE_LOG(LogTemp, Log, TEXT("MaterialAuditManager initialized."));
    bIsInitialized = true;
}

void UMaterialAuditManager::InitializeMaterials()
{
    if (bIsInitialized)
        return;

    Materials.Empty();

    FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");

    TArray<FTopLevelAssetPath> ClassPaths = {
        UMaterial::StaticClass()->GetClassPathName(),
        UMaterialInstance::StaticClass()->GetClassPathName()
    };
    FARFilter Filter;
    Filter.ClassPaths = ClassPaths;
    Filter.bRecursiveClasses = true;

    TArray<FAssetData> AssetDataList;
    AssetRegistryModule.Get().GetAssets(Filter, AssetDataList);

#if WITH_EDITOR
    FScopedSlowTask SlowTask(AssetDataList.Num(), FText::FromString(TEXT("Scanning materials...")));
    SlowTask.MakeDialog(true);
#endif

    for (int32 Index = 0; Index < AssetDataList.Num(); ++Index)
    {
#if WITH_EDITOR
        SlowTask.EnterProgressFrame(1.f, FText::Format(
            FText::FromString("Processing {0} of {1}"),
            FText::AsNumber(Index + 1),
            FText::AsNumber(AssetDataList.Num())
        ));
#endif

        const FAssetData& AssetData = AssetDataList[Index];
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

            if (UMaterial* BaseMat = Cast<UMaterial>(Mat))
            {
                Info.MaterialDomain = BaseMat->MaterialDomain;
                Info.ShadingModel = BaseMat->GetShadingModels().GetFirstShadingModel();
            }
            else if (UMaterialInstance* Inst = Cast<UMaterialInstance>(Mat))
            {
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

void UMaterialAuditManager::Destroy()
{
    if (Instance)
    {
        Instance->RemoveFromRoot();
        Instance = nullptr;
    }
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