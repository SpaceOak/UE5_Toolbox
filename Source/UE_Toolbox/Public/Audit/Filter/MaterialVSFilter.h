#pragma once

// MaterialVertexInstructionCountFilter.h
#pragma once

#include "MaterialAuditBaseFilter.h"
#include "MaterialVSFilter.generated.h"

UCLASS(EditInlineNew)
class UMaterialVertexInstructionCountFilter : public UMaterialAuditBaseFilter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "InstructionCount")
	int32 MinVertexInstructions = 0;

	UPROPERTY(EditAnywhere, Category = "InstructionCount")
	int32 MaxVertexInstructions = 300;

	virtual bool PassesFilter_Implementation(const FMaterialAuditInfo& Info) const override;
};