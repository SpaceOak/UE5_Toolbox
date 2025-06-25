#pragma once

#include "CoreMinimal.h"
#include "ToolModes/IToolMode.h"

class UUserWidget;

/**
 * Реализация режима аудита материалов.
 */
class FMaterialAuditToolMode : public IToolMode
{
public:
	FMaterialAuditToolMode();

	virtual TSubclassOf<UUserWidget> GetWidgetClass() const override;
	virtual void Initialize() override;
	virtual FName GetModeName() const override;

private:
	TSubclassOf<UUserWidget> WidgetClass;
	bool bInitialized = false;
};
