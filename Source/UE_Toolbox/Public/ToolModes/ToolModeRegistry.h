#pragma once

#include "CoreMinimal.h"
#include "Templates/SharedPointer.h"
#include "Templates/Function.h"

class IToolMode;

/**
 * Централизованный реестр всех доступных режимов тулзы.
 */
class FToolModeRegistry
{
public:
	using FToolModeFactory = TFunction<TSharedPtr<IToolMode>()>;

	/** Регистрирует режим по имени и фабрике */
	static void Register(FName ModeName, FToolModeFactory Factory);

	/** Возвращает список всех зарегистрированных режимов */
	static TArray<FName> GetAvailableModes();

	/** Создаёт новый экземпляр режима */
	static TSharedPtr<IToolMode> CreateMode(FName ModeName);

private:
	static TMap<FName, FToolModeFactory>& GetRegistry();
};
