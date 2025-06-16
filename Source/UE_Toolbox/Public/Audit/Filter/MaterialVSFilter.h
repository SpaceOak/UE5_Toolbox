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

	virtual bool PassesFilter_Implementation(const FMaterialAuditInfo& Info) const override
	{
		// Пропускаем, если статистика невалидна
		if (Info.Stats.NumVertexShaderInstructions < 0)
			return false;

		return Info.Stats.NumVertexShaderInstructions >= MinVertexInstructions &&
			   Info.Stats.NumVertexShaderInstructions <= MaxVertexInstructions;
	}
};