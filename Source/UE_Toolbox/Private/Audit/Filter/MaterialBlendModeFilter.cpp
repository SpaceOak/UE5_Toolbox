#include "Audit/Filter/MaterialBlendModeFilter.h"

bool UMaterialBlendModeFilter::PassesFilter_Implementation(const FMaterialAuditInfo& Info) const
{
	return Info.BlendMode == BlendMode;
}
