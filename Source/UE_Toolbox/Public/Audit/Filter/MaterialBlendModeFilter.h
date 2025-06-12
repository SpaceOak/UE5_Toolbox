#pragma once

#include "Audit/Filter/MaterialAuditBaseFilter.h"
#include "MaterialBlendModeFilter.generated.h"

UCLASS(EditInlineNew, DefaultToInstanced, BlueprintType)
class UMaterialBlendModeFilter : public UMaterialAuditBaseFilter
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audit")
	TEnumAsByte<EBlendMode> BlendMode;

	virtual bool PassesFilter_Implementation(const FMaterialAuditInfo& Info) const override;
};
