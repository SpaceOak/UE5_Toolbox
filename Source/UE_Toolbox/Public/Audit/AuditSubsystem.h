#pragma once

#include "CoreMinimal.h"
#include "EditorSubsystem.h" // или другая, если у тебя кастомная
#include "Audit/MaterialAuditManager.h"
#include "AuditSubsystem.generated.h"

/**
 * Центральная сабсистема для аудита материалов
 */
UCLASS()
class UE_TOOLBOX_API UAuditSubsystem : public UEditorSubsystem
{
	GENERATED_BODY()

public:
	// Получить менеджер аудита
	UFUNCTION(BlueprintCallable, Category = "Material Audit")
	UMaterialAuditManager* GetMaterialAuditManager() const { return MaterialAuditManager; }

	UFUNCTION()
	void Register();
	
protected:
	// Инициализация — тут создаём менеджер
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	// Опционально: деинициализация (очистка)
	virtual void Deinitialize() override;


private:
	// Храним менеджер как сабобъект
	UPROPERTY()
	UMaterialAuditManager* MaterialAuditManager = nullptr;
};
