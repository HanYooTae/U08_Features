#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"

struct FVectexData
{
	TArray<FVector> Positions;
	TArray<FVector> Normals;
	TArray<FColor> Colors;
	TArray<FVector2D> UVs;
	TArray<int32> Indices;

	friend FArchive& operator<<(FArchive& InArchive, FVectexData& InData)
	{
		return InArchive
			<< InData.Positions
			<< InData.Normals
			<< InData.Colors
			<< InData.UVs
			<< InData.Indices;
	}
};

class TOY_API FDetailsButton : public IDetailCustomization
{
public:
	static TSharedRef<IDetailCustomization> MakeInstance();

	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

private:
	FReply OnClicked_ShuffleMaterial();
	FReply OnClicked_SaveVertexData();

private:
	TArray<TWeakObjectPtr<UObject>> Objects;
};
