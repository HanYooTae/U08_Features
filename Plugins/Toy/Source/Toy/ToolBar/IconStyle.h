#pragma once

#include "CoreMinimal.h"

class TOY_API FIconStyle
{
public:
	static TSharedPtr<FIconStyle> Get();
	static void Shutdown();

public:
	FIconStyle();
	~FIconStyle();

private:
	void RegisterIcon(const FString& InPostFix, const FString& InPath, const FVector2D& InSize, FSlateIcon& OutSlateIcon);

private:
	static TSharedPtr<FIconStyle> Instance;

private:
	const FName StyleSetName = "ToyStyle";
	TSharedPtr<class FSlateStyleSet> StyleSet;

public:
	FSlateIcon SpawnVertexButtonIcon;
	FSlateIcon OpenViewerButtonIcon;
};
