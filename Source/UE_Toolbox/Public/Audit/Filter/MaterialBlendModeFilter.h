#pragma once

#include "Audit/Filter/MaterialAuditBaseFilter.h"
#include "MaterialBlendModeFilter.generated.h"

UCLASS(BlueprintType, EditInlineNew, DefaultToInstanced)
class UMaterialBlendModeFilter : public UMaterialAuditBaseFilter
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EBlendMode> BlendMode;

	virtual bool PassesFilter_Implementation(const FMaterialAuditInfo& Info) const override
	{
		if (!bEnabled) return true;
		return Info.BlendMode == BlendMode;
	}
};
