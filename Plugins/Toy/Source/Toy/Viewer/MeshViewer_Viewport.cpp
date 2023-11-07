#include "MeshViewer_Viewport.h"

SMeshViewer_Viewport::SMeshViewer_Viewport()
{
}

TSharedRef<FEditorViewportClient> SMeshViewer_Viewport::MakeEditorViewportClient()
{
    return TSharedRef<FEditorViewportClient>();
}

void SMeshViewer_Viewport::AddReferencedObjects(FReferenceCollector& Collector)
{
    Collector.AddReferencedObject(RobotMesh);
    Collector.AddReferencedObject(FloorMesh);
}
