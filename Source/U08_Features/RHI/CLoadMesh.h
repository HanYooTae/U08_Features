#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CLoadMesh.generated.h"

UCLASS()
class U08_FEATURES_API ACLoadMesh : public AActor
{
	GENERATED_BODY()
	
public:	
	ACLoadMesh();

	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	virtual void BeginPlay() override;

public:
	void SetPositions(const TArray<FVector>& InPositions);
	void SetNormals(const TArray<FVector>& InNormals);
	void SetColors(const TArray<FColor>& InColors);
	void SetUVs(const TArray<FVector2D>& InUVs);
	void SetIndices(const TArray<int32> InIndices);

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UProceduralMeshComponent* ProcMesh;

	UPROPERTY(VisibleDefaultsOnly)
		class UMaterialInstanceConstant* Material;

private:
	TArray<FVector> Positions;
	TArray<FVector> Normals;
	TArray<FColor> Colors;
	TArray<FVector2D> UVs;
	TArray<int32> Indices;
};
