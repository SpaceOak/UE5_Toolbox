#pragma once

#include "UObject/Interface.h"
#include "Audit/MaterialAuditInfo.h"
#include "MaterialAuditFilterInterface.generated.h"

UINTERFACE(BlueprintType)
class UMaterialAuditFilterInterface : public UInterface
{
	GENERATED_BODY()
};

class IMaterialAuditFilterInterface
{
	GENERATED_BODY()

public:
	// Основная функция: проходит ли материал по фильтру
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Audit")
	bool PassesFilter(const FMaterialAuditInfo& Info) const;
};
