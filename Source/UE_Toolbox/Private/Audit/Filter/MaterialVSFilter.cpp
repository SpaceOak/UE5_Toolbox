#include "Audit/Filter/MaterialVSFilter.h"



bool UMaterialVertexInstructionCountFilter::PassesFilter_Implementation(const FMaterialAuditInfo& Info) const
{
	// Пропускаем, если статистика невалидна
	if (Info.Stats.NumVertexShaderInstructions < 0)
		return false;

	return Info.Stats.NumVertexShaderInstructions >= MinVertexInstructions &&
		   Info.Stats.NumVertexShaderInstructions <= MaxVertexInstructions;
}
