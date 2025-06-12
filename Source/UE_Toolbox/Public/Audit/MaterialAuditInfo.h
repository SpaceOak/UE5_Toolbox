// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MaterialAuditInfo.generated.h"

USTRUCT(BlueprintType)
struct FMaterialAuditInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Path;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UObject* Asset = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TEnumAsByte<EBlendMode> BlendMode;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TEnumAsByte<EMaterialShadingModel> ShadingModel;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 BasePassShaderCount = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsInstance = false;
};