#pragma once

#include "MaterialAuditBaseFilter.h"
#include "Materials/Material.h"
#include "MaterialShadingModelFilter.generated.h"

UCLASS(EditInlineNew)
class UMaterialShadingModelFilter : public UMaterialAuditBaseFilter
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Material Audit")
	TEnumAsByte<EMaterialShadingModel> ShadingModel = MSM_DefaultLit;

	virtual bool PassesFilter_Implementation(const FMaterialAuditInfo& Info) const override
	{
		return Info.ShadingModel == ShadingModel;
	}
};
