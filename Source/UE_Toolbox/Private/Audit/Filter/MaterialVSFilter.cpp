#include "Audit/Filter/MaterialVSFilter.h"



bool UMaterialVertexInstructionCountFilter::PassesFilter_Implementation(const FMaterialAuditInfo& Info) const
{
	if (Info.NumVertexShaderInstructions < 0)
		return false;

	return Info.NumVertexShaderInstructions >= MinVertexInstructions &&
		   Info.NumVertexShaderInstructions <= MaxVertexInstructions;
}