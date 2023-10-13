#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CVertexMesh.generated.h"

UCLASS()
class U08_FEATURES_API ACVertexMesh : public AActor
{
	GENERATED_BODY()
	
public:	
	ACVertexMesh();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UProceduralMeshComponent* ProcMesh;

private:
	TArray<FVector> Positions;
	TArray<int32> Indices;
	TArray<FVector> Normals;
	TArray<FVector2D> UVs;
	TArray<FColor> Colors;
};
