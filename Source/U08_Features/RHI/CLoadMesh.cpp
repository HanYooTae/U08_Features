#include "CLoadMesh.h"
#include "CLoadMesh.h"
#include "ProceduralMeshComponent.h"
#include "Global.h"
#include "Materials/MaterialInstanceConstant.h"

ACLoadMesh::ACLoadMesh()
{
	bRunConstructionScriptOnDrag = false;

	CHelpers::CreateSceneComponent(this, &ProcMesh, "ProcMesh");
}

void ACLoadMesh::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	ProcMesh->CreateMeshSection
	(
		0,
		Positions,
		Indices,
		Normals,
		UVs,
		Colors,
		TArray<FProcMeshTangent>(),
		true
	);

	CHelpers::GetAssetDynamic(&Material, "MaterialInstanceConstant'/Game/Materials/Surface/MAT_Gold.MAT_Gold'");

	ProcMesh->SetMaterial(0, Material);
}

void ACLoadMesh::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACLoadMesh::SetPositions(const TArray<FVector>& InPositions)
{
	Positions = InPositions;
}

void ACLoadMesh::SetNormals(const TArray<FVector>& InNormals)
{
	Normals = InNormals;
}

void ACLoadMesh::SetColors(const TArray<FColor>& InColors)
{
	Colors = InColors;
}

void ACLoadMesh::SetUVs(const TArray<FVector2D>& InUVs)
{
	UVs = InUVs;
}

void ACLoadMesh::SetIndices(const TArray<int32> InIndices)
{
	Indices = InIndices;
}