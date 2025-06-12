#pragma once

#include "Audit/Filter/MaterialAuditBaseFilter.h"
#include "MaterialBasePassCountFilter.generated.h"

UCLASS(EditInlineNew, DefaultToInstanced, BlueprintType)
class UMaterialBasePassCountFilter : public UMaterialAuditBaseFilter
{
	GENERATED_BODY()
public:
	// Нижний порог BasePass (включительно)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audit")
	int32 MinBasePassCount = 0;

	// Верхний порог BasePass (включительно)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audit")
	int32 MaxBasePassCount = 500;

	// Реализация фильтрации (override!)
	virtual bool PassesFilter_Implementation(const FMaterialAuditInfo& Info) const override;
};
