#pragma once

#include "CoreMinimal.h"
#include "UObject/WeakObjectPtrTemplates.h"

class UUserWidget;

/**
 * Интерфейс для описания режима тулзы (например, Material Audit).
 */
class IToolMode
{
public:
	virtual ~IToolMode() = default;

	/** UI виджет для отображения пользователю */
	virtual TSubclassOf<UUserWidget> GetWidgetClass() const = 0;

	/** Ленивая инициализация подсистем и логики */
	virtual void Initialize() = 0;

	/** Уникальное имя режима */
	virtual FName GetModeName() const = 0;
};
