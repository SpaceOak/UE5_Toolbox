#pragma once

#include "MaterialAuditBaseFilter.h"
#include "Materials/Material.h"
#include "MaterialBlendModeFilter.generated.h"

UCLASS(EditInlineNew)
class UMaterialBlendModeFilter : public UMaterialAuditBaseFilter
{
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, Category = "Material Audit")
    TEnumAsByte<EBlendMode> BlendMode = BLEND_Opaque;

    virtual bool PassesFilter_Implementation(const FMaterialAuditInfo& Info) const override
    {
        return Info.BlendMode == BlendMode;
    }
};