#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MaterialAuditInfo.generated.h"

USTRUCT(BlueprintType)
struct FMaterialAuditInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	UObject* Asset = nullptr;

	UPROPERTY(BlueprintReadOnly)
	FString Name;

	UPROPERTY(BlueprintReadOnly)
	FString Path;

	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<EBlendMode> BlendMode;

	UPROPERTY(BlueprintReadOnly)
	bool bIsInstance = false;

	UPROPERTY(BlueprintReadOnly)
	int32 NumPixelShaderInstructions = -1;

	UPROPERTY(BlueprintReadOnly)
	int32 NumVertexShaderInstructions = -1;
};

