#pragma once

#include "MaterialAuditBaseFilter.h"
#include "Materials/Material.h"
#include "MaterialDomainFilter.generated.h"

UCLASS(EditInlineNew)
class UMaterialDomainFilter : public UMaterialAuditBaseFilter
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Material Audit")
	TEnumAsByte<EMaterialDomain> Domain = MD_Surface;

	virtual bool PassesFilter_Implementation(const FMaterialAuditInfo& Info) const override
	{
		return Info.MaterialDomain == Domain;
	}
};
