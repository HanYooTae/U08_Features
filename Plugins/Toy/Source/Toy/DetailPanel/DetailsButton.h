#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"

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
