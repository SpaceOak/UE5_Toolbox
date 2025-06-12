#include "Audit/Filter/MaterialBasePassCountFilter.h"

bool UMaterialBasePassCountFilter::PassesFilter_Implementation(const FMaterialAuditInfo& Info) const
{
	// Родитель уже проверяет bEnabled, тут не надо дублировать!
	return (Info.BasePassShaderCount >= MinBasePassCount) && (Info.BasePassShaderCount <= MaxBasePassCount);
}
