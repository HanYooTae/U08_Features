#pragma once

#include "CoreMinimal.h"
#include "EditorViewportClient.h"

class TOY_API FMeshViewer_Viewport_Client : public FEditorViewportClient, public TSharedFromThis<FMeshViewer_Viewport_Client>
{
public:
	FMeshViewer_Viewport_Client(class FPreviewScene* InScene, const TSharedRef<class SMeshViewer_Viewport>& InViewport);
};
