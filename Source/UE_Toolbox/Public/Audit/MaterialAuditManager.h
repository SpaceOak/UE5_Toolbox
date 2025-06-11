// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MaterialAuditInfo.h"
#include "MaterialAuditManager.generated.h"

UCLASS(BlueprintType)
class UE_TOOLBOX_API UMaterialAuditManager : public UObject
{
	GENERATED_BODY()

public:

	// Массив информации по материалам, доступен в BP
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Material Audit")
	TArray<FMaterialAuditInfo> Materials;

	// Функция для добавления тестовых данных из BP
	UFUNCTION(BlueprintCallable, Category = "Material Audit")
	void AddTestEntry(const FString& Name, const FString& Path);
};
