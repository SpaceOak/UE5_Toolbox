#pragma once

#include "UObject/Object.h"
#include "MaterialAuditFilterInterface.h"
#include "MaterialAuditBaseFilter.generated.h"

/**
 * Abstract base class for all material audit filters.
 */
UCLASS(Abstract, BlueprintType, EditInlineNew, DefaultToInstanced)
class UMaterialAuditBaseFilter : public UObject, public IMaterialAuditFilterInterface
{
	GENERATED_BODY()
public:
	/** Whether this filter is enabled and should be applied */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audit")
	bool bEnabled = true;

	/** Main filter implementation. Override in children */
	virtual bool PassesFilter_Implementation(const FMaterialAuditInfo& Info) const override
	{
		if (!bEnabled) return true;
		return true;
	}
};