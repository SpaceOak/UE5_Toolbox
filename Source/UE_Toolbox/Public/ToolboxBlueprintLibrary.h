#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ToolboxBlueprintLibrary.generated.h"

class UUserWidget;

/**
 * Blueprint доступ к зарегистрированным режимам тулзы
 */
UCLASS()
class UE_TOOLBOX_API UToolboxBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/** Получить список доступных режимов (имена) */
	UFUNCTION(BlueprintCallable, Category = "Toolbox")
	static TArray<FName> GetAvailableToolModes();

	/** Создать виджет для режима по имени */
	UFUNCTION(BlueprintCallable, Category = "Toolbox")
	static UUserWidget* CreateToolModeWidget(UObject* WorldContext, FName ModeName);
};