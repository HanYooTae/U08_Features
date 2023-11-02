#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CButtonActor.generated.h"

UENUM(BlueprintType)
enum class EMaterialType : uint8
{
	Gold, Wood, Concrete, Brick, Max
};

USTRUCT(BlueprintType)
struct FMaterialParameterData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		class UTexture* BaseMap;

	UPROPERTY(EditAnywhere)
		class UTexture* NormalMap;

	UPROPERTY(EditAnywhere)
		class UTexture* RoughnessMap;

	UPROPERTY(EditAnywhere)
		float Metalic;

	UPROPERTY(EditAnywhere)
		float Roughness_Min;

	UPROPERTY(EditAnywhere)
		float Roughness_Max;
};

UCLASS()
class U08_FEATURES_API ACButtonActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACButtonActor();

protected:
	virtual void BeginPlay() override;

public:
#if WITH_EDITOR
	void ShuffleMaterial();
#endif

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleDefaultsOnly)
		class UMaterialInstanceConstant* Material;

	UPROPERTY(EditDefaultsOnly)
		FMaterialParameterData MaterialParameters[(int32)EMaterialType::Max];
};
