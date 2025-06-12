// MaterialAuditInfoObject.h
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MaterialAuditInfo.h"
#include "MaterialAuditInfoObject.generated.h"

UCLASS(BlueprintType)
class UE_TOOLBOX_API UMaterialAuditInfoObject : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FMaterialAuditInfo Data;
};
