#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MaterialAuditInfo.h"
#include "Filter/MaterialAuditBaseFilter.h"
#include "MaterialAuditManager.generated.h"

UCLASS(BlueprintType)
class UE_TOOLBOX_API UMaterialAuditManager : public UObject
{
	GENERATED_BODY()

public:
	UMaterialAuditManager();

	UFUNCTION(BlueprintCallable, Category = "Material Audit")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "Material Audit")
	void InitializeMaterials();

	UFUNCTION(BlueprintCallable, Category = "Material Audit")
	void SetAnalyzeCurrentLevelOnly(bool bOnlyCurrentLevel);

	UFUNCTION(BlueprintCallable, Category = "Material Audit")
	static UMaterialAuditManager* Get();

	UFUNCTION(BlueprintCallable, Category = "Material Audit")
	static void Destroy();

	UFUNCTION(BlueprintCallable, Category = "Material Audit")
	TArray<FMaterialAuditInfo> GetFilteredMaterials();
	
	UFUNCTION(BlueprintCallable, Category = "Material Audit")
	void ResetAndReinitialize();

private:
	void ScanProjectMaterials();
	void ScanLevelMaterials();

private:
	static UMaterialAuditManager* Instance;

	UPROPERTY()
	TArray<FMaterialAuditInfo> Materials;

	UPROPERTY(EditAnywhere, Instanced, Category = "Material Audit")
	TArray<UMaterialAuditBaseFilter*> Filters;

	bool bAnalyzeCurrentLevelOnly = false;
	bool bIsInitialized = false;
};
