#pragma once

#include "CoreMinimal.h"
#include "GameplayDebuggerCategory.h"

struct FCollectionData
{
	FString Name;
	FVector Location;
	FVector Forward;
};

class TOY_API FDebuggerCategory : public FGameplayDebuggerCategory
{
public:
	FDebuggerCategory();
	~FDebuggerCategory();

public:
	static TSharedRef<FGameplayDebuggerCategory> MakeInstance();

public:
	/** [AUTH] gather data for replication */
	virtual void CollectData(APlayerController* OwnerPC, AActor* DebugActor) override;

	/** [LOCAL] draw collected data */
	virtual void DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext) override;

private:
	FCollectionData PlayerPawnData;
	FCollectionData ForwardActorData;
	FCollectionData DebugActorData;
};
