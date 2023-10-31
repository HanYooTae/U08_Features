#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FToyModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	void AddToolBar_SpawnVertex(class FToolBarBuilder& InToolBarBuilder);
	void AddToolBar_OpenViewer(class FToolBarBuilder& InToolBarBuilder);

private:
	TSharedPtr<FExtender> Extender;
};
