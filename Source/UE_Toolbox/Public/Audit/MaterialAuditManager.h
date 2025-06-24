#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Audit/MaterialAuditInfo.h"
#include "Audit/Filter/MaterialAuditBaseFilter.h"
#include "MaterialAuditManager.generated.h"

/**
 * Менеджер аудита материалов.
 * Собирает все материалы и их инстансы, фильтрует по заданным фильтрам.
 */
UCLASS(BlueprintType)
class UE_TOOLBOX_API UMaterialAuditManager : public UObject
{
	GENERATED_BODY()

public:
	UMaterialAuditManager();

	// Массив информации о материалах (автоматически собирается)
	UPROPERTY(BlueprintReadOnly, Category = "Material Audit")
	TArray<FMaterialAuditInfo> Materials;

	// Активные фильтры (редактируются через UI)
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, Category = "Material Audit|Filters")
	TArray<UMaterialAuditBaseFilter*> Filters;

	// Получить только материалы, проходящие все фильтры
	UFUNCTION(BlueprintCallable, Category = "Material Audit")
	TArray<FMaterialAuditInfo> GetFilteredMaterials();

	static UMaterialAuditManager* Get();

	void Initialize();

	void InitializeMaterials();
	

	void SetAnalyzeCurrentLevelOnly(bool bOnlyCurrentLevel);
	

protected:
	bool bAnalyzeCurrentLevelOnly = false;
	bool bIsInitialized = false;
	static UMaterialAuditManager* Instance;
	
};
