#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CAsset.generated.h"

UCLASS()
class TOY_API UCAsset : public UObject
{
	GENERATED_BODY()
	
public:
	FName GetName() { return Name; }
	FORCEINLINE class UStaticMesh* GetShape() { return Shape; }
	FORCEINLINE float GetDropRate() { return DropRate; }

protected:
	UPROPERTY(EditAnywhere)
		FName Name;

	UPROPERTY(EditAnywhere)
		class UStaticMesh* Shape;

	UPROPERTY(EditAnywhere)
		float DropRate;
};
