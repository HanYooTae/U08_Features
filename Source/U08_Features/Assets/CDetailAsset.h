#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CDetailAsset.generated.h"

UCLASS()
class U08_FEATURES_API UCDetailAsset : public UObject
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere)
		FVector Location;


};
