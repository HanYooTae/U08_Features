#pragma once

#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"

class TOY_API FMeshViewer : public FAssetEditorToolkit
{
public:
	static void OpenWindow(UObject* InAsset);
	static void Shutdown();

public:
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;

private:
	TSharedRef<SDockTab> SpawnViewportTab(const FSpawnTabArgs& InArgs);
	TSharedRef<SDockTab> SpawnPreviewSceneSettingsTab(const FSpawnTabArgs& InArgs);
	TSharedRef<SDockTab> SpawnDetailsViewTab(const FSpawnTabArgs& InArgs);

private:
	void OpenWindow_Internal(UObject* InAsset);

public:
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	virtual FLinearColor GetWorldCentricTabColorScale(void) const override;

private:
	static TSharedPtr<FMeshViewer> Instance;

private:
	TSharedPtr<class SMeshViewer_Viewport> ViewportWidget;
	TSharedPtr<class SWidget> PreviewSceneSettingsWidget;
	TSharedPtr<class IDetailsView> DetailsViewWidget;
};
