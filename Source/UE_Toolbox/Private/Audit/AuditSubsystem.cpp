#include "Audit/AuditSubsystem.h"
#include "Audit/MaterialAuditManager.h"

void UAuditSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// Создаём менеджер как UObject
	if (!MaterialAuditManager)
	{
		MaterialAuditManager = NewObject<UMaterialAuditManager>(this, UMaterialAuditManager::StaticClass());
		// Теперь он будет жить столько, сколько живёт эта сабсистема
	}
}

void UAuditSubsystem::Deinitialize()
{
	// Очищаем ссылку (не обязательно, просто good practice)
	MaterialAuditManager = nullptr;
	Super::Deinitialize();
}
