#include "DetailsButton.h"
#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"

TSharedRef<IDetailCustomization> FDetailsButton::MakeInstance()
{
	MakeShareable(new FDetailsButton());
}

void FDetailsButton::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	IDetailCategoryBuilder& category = DetailBuilder.EditCategory("AwesomeCategory");

	category.AddCustomRow(FText::FromString("Awesome"))
	.NameContent()
	[
		SNew(STextBlock)
		.Text(FText::FromString("Shuffle Material"))
	]
	.ValueContent()
	.VAlign(VAlign_Center)
	.MaxDesiredWidth(250)
	[
		SNew(SButton)
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Fill)
		[
			SNew(STextBlock)
			.Text(FText::FromString("Shuffle"))
		]
	];
}