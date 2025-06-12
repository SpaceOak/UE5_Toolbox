#pragma once

#include "UObject/Object.h"
#include "MaterialAuditFilterInterface.h"
#include "MaterialAuditBaseFilter.generated.h"

UCLASS(Abstract, BlueprintType, EditInlineNew, DefaultToInstanced)
class UMaterialAuditBaseFilter : public UObject, public IMaterialAuditFilterInterface
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEnabled = false;

	virtual bool PassesFilter_Implementation(const FMaterialAuditInfo& Info) const override
	{
		if (!bEnabled) return true;
		return true; // Базовая реализация всегда true, потомки переопределяют.
	}
};

