#pragma once
// MaterialPixelInstructionCountFilter.h
#pragma once

#include "MaterialAuditBaseFilter.h"
#include "MaterialPSFilter.generated.h"

UCLASS(EditInlineNew)
class UMaterialPixelInstructionCountFilter : public UMaterialAuditBaseFilter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "InstructionCount")
	int32 MinPixelInstructions = 0;

	UPROPERTY(EditAnywhere, Category = "InstructionCount")
	int32 MaxPixelInstructions = 500;

	virtual bool PassesFilter_Implementation(const FMaterialAuditInfo& Info) const override
	{
		// Пропускаем, если статистика невалидна
		if (Info.Stats.NumPixelShaderInstructions < 0)
			return false;

		return Info.Stats.NumPixelShaderInstructions >= MinPixelInstructions &&
			   Info.Stats.NumPixelShaderInstructions <= MaxPixelInstructions;
	}
	
};