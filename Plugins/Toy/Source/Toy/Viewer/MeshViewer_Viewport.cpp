#include "MeshViewer_Viewport.h"
#include "MeshViewer_Viewport_Client.h"
#include "AdvancedPreviewScene.h"
#include "Components/StaticMeshComponent.h"
#include "InputCoreTypes.h"

SMeshViewer_Viewport::SMeshViewer_Viewport()
{
    Scene = MakeShareable(new FAdvancedPreviewScene(FPreviewScene::ConstructionValues()));
}

void SMeshViewer_Viewport::Construct(const FArguments& InArgs)
{
    SEditorViewport::Construct(InArgs);

    //Floor
    UStaticMesh* floorMeshAsset = LoadObject<UStaticMesh>(nullptr, TEXT("StaticMesh'/Engine/MapTemplates/SM_Template_Map_Floor.SM_Template_Map_Floor'"));
    FloorMesh = NewObject<UStaticMeshComponent>(GetTransientPackage(), NAME_None, EObjectFlags::RF_Transient);
    FloorMesh->SetStaticMesh(floorMeshAsset);

    FTransform tranform;
    Scene->AddComponent(FloorMesh, tranform);

    //Robot
    UStaticMesh* robotMeshAsset = LoadObject<UStaticMesh>(nullptr, TEXT("StaticMesh'/Game/Robot/SM_Robot.SM_Robot'"));
    RobotMesh = NewObject<UStaticMeshComponent>(GetTransientPackage(), NAME_None, EObjectFlags::RF_Transient);
    RobotMesh->SetStaticMesh(robotMeshAsset);

    tranform.SetLocation(FVector(0, 0, 150));
    Scene->AddComponent(RobotMesh, tranform);
}

void SMeshViewer_Viewport::AddReferencedObjects(FReferenceCollector& Collector)
{
    Collector.AddReferencedObject(RobotMesh);
    Collector.AddReferencedObject(FloorMesh);
}

TSharedRef<class FAdvancedPreviewScene> SMeshViewer_Viewport::GetScene()
{
    return Scene.ToSharedRef();
}

TSharedRef<FEditorViewportClient> SMeshViewer_Viewport::MakeEditorViewportClient()
{
    ViewportClient = MakeShareable(new FMeshViewer_Viewport_Client(Scene.Get(), SharedThis(this)));

    return ViewportClient.ToSharedRef();
}
