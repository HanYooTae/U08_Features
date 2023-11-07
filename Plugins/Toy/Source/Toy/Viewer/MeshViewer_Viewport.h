#pragma once

#include "CoreMinimal.h"
#include "SEditorViewport.h"

class TOY_API SMeshViewer_Viewport : public SEditorViewport, public FGCObject
{
public:
	SMeshViewer_Viewport();

protected:
	virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;

public:
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;

private:
	class UStaticMeshComponent* RobotMesh;
	class UStaticMeshComponent* FloorMesh;
};
