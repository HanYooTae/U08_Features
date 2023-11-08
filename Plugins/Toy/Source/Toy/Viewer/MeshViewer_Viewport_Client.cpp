#include "MeshViewer_Viewport_Client.h"
#include "MeshViewer_Viewport.h"

FMeshViewer_Viewport_Client::FMeshViewer_Viewport_Client(FPreviewScene* InScene, const TSharedRef<SMeshViewer_Viewport>& InViewport)
	: FEditorViewportClient(nullptr, InScene, StaticCastSharedRef<SMeshViewer_Viewport>(InViewport))
{
	// 카메라 세팅, 조명 세팅 등
	SetViewMode(VMI_Lit);

	SetViewRotation(FRotator(-20, -90, 0));
	SetViewLocationForOrbiting(FVector(0, 0, 100), 1000);
}
