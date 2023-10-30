#include "IconStyle.h"
#include "Styling/SlateStyle.h"
#include "Interfaces/IPluginManager.h"

TSharedPtr<IconStyle> Instance = nullptr;

TSharedPtr<IconStyle> IconStyle::Get()
{
	if (Instance == nullptr)
		Instance = MakeShareable(new IconStyle());

	return Instance;
}

void IconStyle::Shutdown()
{
	if (Instance.IsValid())
		Instance.Reset();
}

IconStyle::IconStyle()
{
	StyleSet = MakeShareable(new FSlateStyleSet(StyleSetName));

	FString path = IPluginManager::Get().FindPlugin("Toy")->GetBaseDir();
	path /= "Resources";
	StyleSet->SetContentRoot(path);

	FSlateImageBrush* brush = new FSlateImageBrush(path / "Icon.png", FVector2D(48));

	FString name = StyleSetName.ToString() + ".SpawnVertex";
	StyleSet->Set(FName(name), brush);
}

IconStyle::~IconStyle()
{
}
