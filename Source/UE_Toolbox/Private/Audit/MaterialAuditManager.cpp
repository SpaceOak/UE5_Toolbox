// Fill out your copyright notice in the Description page of Project Settings.


#include "Audit/MaterialAuditManager.h"

void UMaterialAuditManager::AddTestEntry(const FString& Name, const FString& Path)
{
	FMaterialAuditInfo Info;
	Info.Name = Name;
	Info.Path = Path;
	Materials.Add(Info);
}
