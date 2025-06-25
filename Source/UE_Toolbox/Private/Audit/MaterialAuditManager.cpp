#include "Audit/MaterialAuditManager.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Materials/Material.h"
#include "Materials/MaterialInstance.h"
#include "Materials/MaterialInterface.h"
#include "MaterialEditingLibrary.h"
#include "MaterialStatsCommon.h"
#include "MaterialEditor/PreviewMaterial.h"
#include "Misc/ScopedSlowTask.h"
#include "Engine/World.h"
#include "Editor.h"
#include "GameFramework/Actor.h"
#include "Components/MeshComponent.h"

UMaterialAuditManager::UMaterialAuditManager()
{
   // InitializeMaterials();
}

UMaterialAuditManager* UMaterialAuditManager::Instance = nullptr;

UMaterialAuditManager* UMaterialAuditManager::Get()
{
    if (!Instance)
    {
        UE_LOG(LogTemp, Log, TEXT("[MaterialAudit] Creating new instance"));
        Instance = NewObject<UMaterialAuditManager>();
        Instance->AddToRoot();
    }
    return Instance;
}

void UMaterialAuditManager::Initialize()
{
    UE_LOG(LogTemp, Log, TEXT("[MaterialAudit] Initialize called"));
    bIsInitialized = true;
}

void UMaterialAuditManager::InitializeMaterials()
{
    if (bIsInitialized)
    {
        UE_LOG(LogTemp, Log, TEXT("[MaterialAudit] Already initialized. Skipping"));
        return;
    }

    Materials.Empty();
    UE_LOG(LogTemp, Log, TEXT("[MaterialAudit] Begin InitializeMaterials (bAnalyzeCurrentLevelOnly=%s)"), bAnalyzeCurrentLevelOnly ? TEXT("true") : TEXT("false"));

    if (bAnalyzeCurrentLevelOnly)
    {
        ScanLevelMaterials();
    }
    else
    {
        ScanProjectMaterials();
    }

    bIsInitialized = true;
    UE_LOG(LogTemp, Log, TEXT("[MaterialAudit] InitializeMaterials completed. Total materials: %d"), Materials.Num());
}

void UMaterialAuditManager::ScanProjectMaterials()
{
    UE_LOG(LogTemp, Log, TEXT("[MaterialAudit] Scanning project materials..."));

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
    UE_LOG(LogTemp, Log, TEXT("[MaterialAudit] Found %d material assets in project"), AssetDataList.Num());

    FScopedSlowTask SlowTask(AssetDataList.Num(), FText::FromString(TEXT("Scanning project materials...")));
    SlowTask.MakeDialog(true);

    for (int32 i = 0; i < AssetDataList.Num(); ++i)
    {
        SlowTask.EnterProgressFrame(1.f);

        const FAssetData& AssetData = AssetDataList[i];
        if (!AssetData.IsValid())
            continue;

        UObject* AssetObj = AssetData.GetAsset();
        if (!IsValid(AssetObj))
            continue;

        if (UMaterialInterface* Mat = Cast<UMaterialInterface>(AssetObj))
        {
            FMaterialAuditInfo Info;
            Info.Asset = AssetObj;
            Info.Path = AssetData.GetObjectPathString();
            Info.Name = AssetData.AssetName.ToString();
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
                if (UMaterial* Parent = Inst->GetMaterial())
                {
                    Info.MaterialDomain = Parent->MaterialDomain;
                    Info.ShadingModel = Parent->GetShadingModels().GetFirstShadingModel();
                }
            }

            Materials.Add(Info);
        }
    }
}

void UMaterialAuditManager::ScanLevelMaterials()
{
    UE_LOG(LogTemp, Log, TEXT("[MaterialAudit] Scanning current level materials..."));

    UWorld* World = GEditor ? GEditor->GetEditorWorldContext().World() : nullptr;
    if (!World) return;

    ULevel* Level = World->GetCurrentLevel();
    if (!Level) return;

    TSet<UMaterialInterface*> UniqueMaterials;

    for (AActor* Actor : Level->Actors)
    {
        if (!IsValid(Actor)) continue;

        TArray<UMeshComponent*> MeshComponents;
        Actor->GetComponents<UMeshComponent>(MeshComponents);

        for (UMeshComponent* Mesh : MeshComponents)
        {
            if (!IsValid(Mesh)) continue;

            const int32 Num = Mesh->GetNumMaterials();
            for (int32 i = 0; i < Num; ++i)
            {
                if (UMaterialInterface* Mat = Mesh->GetMaterial(i))
                {
                    UniqueMaterials.Add(Mat);
                }
            }
        }
    }

    TArray<UMaterialInterface*> MaterialsToScan = UniqueMaterials.Array();
    UE_LOG(LogTemp, Log, TEXT("[MaterialAudit] Found %d unique materials in level"), MaterialsToScan.Num());

    FScopedSlowTask SlowTask(MaterialsToScan.Num(), FText::FromString(TEXT("Scanning level materials...")));
    SlowTask.MakeDialog(true);

    for (int32 i = 0; i < MaterialsToScan.Num(); ++i)
    {
        SlowTask.EnterProgressFrame(1.f);

        UMaterialInterface* Mat = MaterialsToScan[i];
        if (!IsValid(Mat)) continue;

        FMaterialAuditInfo Info;
        Info.Asset = Mat;
        Info.Path = Mat->GetPathName();
        Info.Name = Mat->GetName();
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
            if (UMaterial* Parent = Inst->GetMaterial())
            {
                Info.MaterialDomain = Parent->MaterialDomain;
                Info.ShadingModel = Parent->GetShadingModels().GetFirstShadingModel();
            }
        }

        Materials.Add(Info);
    }
}

void UMaterialAuditManager::SetAnalyzeCurrentLevelOnly(bool bOnlyCurrentLevel)
{
    bAnalyzeCurrentLevelOnly = bOnlyCurrentLevel;
    UE_LOG(LogTemp, Log, TEXT("[MaterialAudit] AnalyzeCurrentLevelOnly set to %s"), bAnalyzeCurrentLevelOnly ? TEXT("true") : TEXT("false"));
}

void UMaterialAuditManager::Destroy()
{
    UE_LOG(LogTemp, Log, TEXT("[MaterialAudit] Destroy called"));
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

    UE_LOG(LogTemp, Log, TEXT("[MaterialAudit] GetFilteredMaterials: %d out of %d passed filters"), Result.Num(), Materials.Num());
    return Result;
}

void UMaterialAuditManager::ResetAndReinitialize()
{
    bIsInitialized = false;
    InitializeMaterials();
}
