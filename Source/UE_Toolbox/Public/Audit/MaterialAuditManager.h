#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Audit/MaterialAuditInfo.h"
#include "Audit/Filter/MaterialAuditBaseFilter.h"
#include "MaterialAuditManager.generated.h"

/**
 * Менеджер аудита материалов:
 * - Хранит массив информации по материалам (Materials)
 * - Хранит массив активных фильтров (Filters)
 * - Позволяет добавлять тестовые материалы
 * - Позволяет фильтровать материалы по всем активным фильтрам
 */
UCLASS(BlueprintType)
class UE_TOOLBOX_API UMaterialAuditManager : public UObject
{
	GENERATED_BODY()

public:

	// Массив информации о материалах
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Material Audit")
	TArray<FMaterialAuditInfo> Materials;

	// Массив активных фильтров (любые наследники базового фильтра!)
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, Category = "Material Audit|Filters")
	TArray<UMaterialAuditBaseFilter*> Filters;

	// Добавить тестовую запись (например, из BP)
	UFUNCTION(BlueprintCallable, Category = "Material Audit")
	void AddTestEntry(const FString& Name, const FString& Path);

	// Отфильтровать все материалы через текущий набор фильтров
	UFUNCTION(BlueprintCallable, Category = "Material Audit|Filters")
	TArray<FMaterialAuditInfo> GetFilteredMaterials() const;
};
