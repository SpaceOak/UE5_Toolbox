#include "Audit/Filter/MaterialPSFilter.h"


bool UMaterialPixelInstructionCountFilter::PassesFilter_Implementation(const FMaterialAuditInfo& Info) const
{
	// -1 = unknown, пропускаем если невалидно
	if (Info.NumPixelShaderInstructions < 0)
		return false;

	return Info.NumPixelShaderInstructions >= MinPixelInstructions &&
		   Info.NumPixelShaderInstructions <= MaxPixelInstructions;
}