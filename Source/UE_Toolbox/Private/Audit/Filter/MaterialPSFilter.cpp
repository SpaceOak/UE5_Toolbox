#include "Audit/Filter/MaterialPSFilter.h"

bool UMaterialPixelInstructionCountFilter::PassesFilter_Implementation(const FMaterialAuditInfo& Info) const
{
	// Пропускаем, если статистика невалидна
	if (Info.Stats.NumPixelShaderInstructions < 0)
		return false;

	return Info.Stats.NumPixelShaderInstructions >= MinPixelInstructions &&
		   Info.Stats.NumPixelShaderInstructions <= MaxPixelInstructions;
}
