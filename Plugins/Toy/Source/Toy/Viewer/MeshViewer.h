#pragma once

#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"

class TOY_API FMeshViewer : public FAssetEditorToolkit
{
public:
	static void OpenWindow(UObject* InAsset);
	static void Shutdown(UObject* InAsset);

private:
	void OpenWindow_Internal(UObject* InAsset);

public:
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	virtual FLinearColor GetWorldCentricTabColorScale(void) const override;

private:
	static TSharedPtr<FMeshViewer> Instance;
};
