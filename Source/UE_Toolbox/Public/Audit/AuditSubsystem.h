#pragma once

#include "CoreMinimal.h"
#include "EditorSubsystem.h"
#include "MaterialAuditInfoObject.h"
#include "AuditSubsystem.generated.h"

UCLASS()
class UE_TOOLBOX_API UAuditSubsystem : public UEditorSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category = "Audit|Materials")
	TArray<UMaterialAuditInfoObject*> MaterialAuditObjects;

	// Новый метод для добавления тестового объекта
	UFUNCTION(BlueprintCallable, Category = "Audit|Materials")
	UMaterialAuditInfoObject* AddMaterialTestEntry(const FString& Name, const FString& Path);

	UFUNCTION(BlueprintCallable, Category = "Audit|Materials")
	void ClearMaterialAudits();
};
