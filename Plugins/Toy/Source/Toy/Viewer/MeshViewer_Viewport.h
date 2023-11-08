#pragma once

#include "CoreMinimal.h"
#include "SEditorViewport.h"

class TOY_API SMeshViewer_Viewport : public SEditorViewport, public FGCObject
{
public:
	SMeshViewer_Viewport();

	void Construct(const FArguments& InArgs);

public:
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;

	TSharedRef<class FAdvancedPreviewScene> GetScene();

protected:
	virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;

private:
	// Scene
	TSharedPtr<class FAdvancedPreviewScene> Scene;

	// Client
	TSharedPtr<class FMeshViewer_Viewport_Client> ViewportClient;

private:
	class UStaticMeshComponent* RobotMesh;
	class UStaticMeshComponent* FloorMesh;
};
