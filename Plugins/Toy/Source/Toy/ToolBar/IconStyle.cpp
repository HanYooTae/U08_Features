#include "IconStyle.h"
#include "Styling/SlateStyle.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleRegistry.h"

TSharedPtr<FIconStyle> FIconStyle::Instance = nullptr;

TSharedPtr<FIconStyle> FIconStyle::Get()
{
	if (Instance == nullptr)
		Instance = MakeShareable(new FIconStyle());

	return Instance;
}

void FIconStyle::Shutdown()
{
	if (Instance.IsValid())
		Instance.Reset();
}

FIconStyle::FIconStyle()
{
	StyleSet = MakeShareable(new FSlateStyleSet(StyleSetName));

	FString path = IPluginManager::Get().FindPlugin("Toy")->GetBaseDir();
	path /= "Resources";
	StyleSet->SetContentRoot(path);

	RegisterIcon("SpawnVertex", path / "Icon.png", FVector2D(48), SpawnVertexButtonIcon);
	RegisterIcon("OpenViewer", path / "Icon2.png", FVector2D(48), OpenViewerButtonIcon);

	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet.Get());
}

FIconStyle::~FIconStyle()
{
	if (StyleSet.IsValid() == false) return;

	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet.Get());
	StyleSet.Reset();
}

void FIconStyle::RegisterIcon(const FString& InPostFix, const FString& InPath, const FVector2D& InSize, FSlateIcon& OutSlateIcon)
{
	FSlateImageBrush* brush = new FSlateImageBrush(InPath, InSize);

	FString styleName = StyleSetName.ToString() + "." + InPostFix;
	StyleSet->Set(FName(styleName), brush);

	OutSlateIcon = FSlateIcon(StyleSetName, FName(styleName));
}
