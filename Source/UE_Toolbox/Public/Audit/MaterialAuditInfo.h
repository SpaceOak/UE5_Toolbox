#pragma once

#include "CoreMinimal.h"
#include "MaterialDomain.h"
#include "UObject/NoExportTypes.h"
#include "Materials/Material.h"
#include "Materials/MaterialInstance.h"
#include "Materials/MaterialInterface.h"
#include "MaterialEditingLibrary.h"
#include "MaterialStatsCommon.h"
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

	// --- Основные типовые свойства ---
	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<EMaterialDomain> MaterialDomain = MD_Surface;

	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<EBlendMode> BlendMode = BLEND_Opaque;

	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<EMaterialShadingModel> ShadingModel = MSM_DefaultLit;

	UPROPERTY(BlueprintReadOnly)
	bool bIsInstance = false;

	// --- Вся статистика для продвинутых фильтров ---
	UPROPERTY(BlueprintReadOnly)
	FMaterialStatistics Stats;
};
