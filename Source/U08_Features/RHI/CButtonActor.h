#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CButtonActor.generated.h"

UCLASS()
class U08_FEATURES_API ACButtonActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACButtonActor();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleDefaultsOnly)
		class UMaterialInstanceConstant* Material;
};
