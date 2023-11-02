#include "DetailsButton.h"
#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"
#include "RHI/CButtonActor.h"
#include "Interfaces/IMainFrameModule.h"
#include "DesktopPlatformModule.h"
#include "IDesktopPlatform.h"

TSharedRef<IDetailCustomization> FDetailsButton::MakeInstance()
{
	return MakeShareable(new FDetailsButton());
}

void FDetailsButton::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	IDetailCategoryBuilder& category = DetailBuilder.EditCategory("AwesomeCategory");

	// Shuffle Material Button Layout
	category.AddCustomRow(FText::FromString("Shuffle Material"))
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
		.OnClicked(this, &FDetailsButton::OnClicked_ShuffleMaterial)
		.Content()
		[
			SNew(STextBlock)
			.Text(FText::FromString("Shuffle"))
		]
	];

	// Save Vertex Button Layout
	category.AddCustomRow(FText::FromString("SaveVertex"))
	.NameContent()
	[
		SNew(STextBlock)
		.Text(FText::FromString("SaveVertex"))
	]
	.ValueContent()
	.VAlign(VAlign_Center)
	.MaxDesiredWidth(250)
	[
		SNew(SButton)
		.VAlign(VAlign_Center)
	.HAlign(HAlign_Fill)
	.OnClicked(this, &FDetailsButton::OnClicked_SaveVertexData)
	.Content()
	[
		SNew(STextBlock)
		.Text(FText::FromString("Save to Binary File"))
	]
	];

	DetailBuilder.GetObjectsBeingCustomized(Objects);
}

FReply FDetailsButton::OnClicked_ShuffleMaterial()
{
	ACButtonActor* actor = Cast<ACButtonActor>(Objects[0]);
	if (actor == nullptr) return FReply::Unhandled();
	
	actor->ShuffleMaterial();

	return FReply::Handled();
}

FReply FDetailsButton::OnClicked_SaveVertexData()
{
	//------------------------------------------------------------------------------------------------------------
	// 	   @@ Load Vertex Data from SM_Asset
	//------------------------------------------------------------------------------------------------------------
	ACButtonActor* actor = Cast<ACButtonActor>(Objects[0]);
	UActorComponent* comp = actor->GetComponentByClass(UStaticMeshComponent::StaticClass());
	UStaticMeshComponent* meshComp = Cast<UStaticMeshComponent>(comp);
	if (meshComp == nullptr) return FReply::Unhandled();

	//------------------------------------------------------------------------------------------------------------
	// 	   @@ Save File Dialog
	//------------------------------------------------------------------------------------------------------------
	IMainFrameModule& mainFrame = FModuleManager::LoadModuleChecked<IMainFrameModule>("MainFrame");
	void* handle = mainFrame.GetParentWindow()->GetNativeWindow()->GetOSWindowHandle();

	FString path;
	TArray<FString> fileNames;

	IDesktopPlatform* platform = FDesktopPlatformModule::Get();
	platform->SaveFileDialog(handle, "Save", path, "", "Binary File(*.bin) | *.bin", EFileDialogFlags::None, fileNames);

	if (fileNames.Num() < 1) return FReply::Unhandled();

	GLog->Log(*fileNames[0]);

	return FReply::Handled();
}