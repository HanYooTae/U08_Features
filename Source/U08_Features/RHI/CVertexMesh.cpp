#include "CVertexMesh.h"
#include "Global.h"
#include "ProceduralMeshComponent.h"

ACVertexMesh::ACVertexMesh()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateSceneComponent(this, &ProcMesh, "ProcMesh");

	float p = 0.5f;

	Positions.Add(FVector(-p, -p, -p));
	Positions.Add(FVector(-p, -p, +p));
	Positions.Add(FVector(-p, +p, -p));
	Positions.Add(FVector(-p, +p, +p));

	for (int32 i = 0; i < 4; i++)
	{
		Normals.Add(FVector(-1, 0, 0));
	}

	Colors.Add(FColor::Red);
	Colors.Add(FColor::Green);
	Colors.Add(FColor::Blue);
	Colors.Add(FColor::Orange);

	UVs.Add(FVector2D(0, 1));
	UVs.Add(FVector2D(0, 0));
	UVs.Add(FVector2D(1, 1));
	UVs.Add(FVector2D(1, 0));

	Indices.Add(2);
	Indices.Add(1);
	Indices.Add(0);

	Indices.Add(3);
	Indices.Add(1);
	Indices.Add(2);
	
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
}

void ACVertexMesh::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACVertexMesh::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

