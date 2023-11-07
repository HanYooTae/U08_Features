#include "DetailsButton.h"
#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"
#include "RHI/CButtonActor.h"
#include "Interfaces/IMainFrameModule.h"
#include "DesktopPlatformModule.h"
#include "IDesktopPlatform.h"
#include "Serialization/BufferArchive.h"
#include "Misc/FileHelper.h"

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
		SNew(STextBlock)	// TSharedRef<SWidget> <- SNew
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
	// -> Get SM Asset
	ACButtonActor* actor = Cast<ACButtonActor>(Objects[0]);
	UActorComponent* comp = actor->GetComponentByClass(UStaticMeshComponent::StaticClass());
	UStaticMeshComponent* meshComp = Cast<UStaticMeshComponent>(comp);
	if (meshComp == nullptr) return FReply::Unhandled();

	UStaticMesh* meshAsset = meshComp->GetStaticMesh();
	if (meshAsset == nullptr) return FReply::Unhandled();
	FStaticMeshRenderData* renderData = meshAsset->RenderData.Get();
	if(renderData->LODResources.Num() < 1) return FReply::Unhandled();
	
	// -> Get Vertex Data
	FStaticMeshLODResources& lod = renderData->LODResources[0];
	FPositionVertexBuffer& positionBuffer = lod.VertexBuffers.PositionVertexBuffer;
	FStaticMeshVertexBuffer& metaBuffer = lod.VertexBuffers.StaticMeshVertexBuffer;
	FColorVertexBuffer& colorBuffer = lod.VertexBuffers.ColorVertexBuffer;
	FRawStaticIndexBuffer& indexBuffer = lod.IndexBuffer;

	if (positionBuffer.GetNumVertices() < 1) return FReply::Unhandled();
	if (indexBuffer.GetNumIndices() < 1) return FReply::Unhandled();
	uint32 vertexCount = positionBuffer.GetNumVertices();
	int32 indexCount = indexBuffer.GetNumIndices();		// -1ÀÌ¸é ÀÎµ¦½ºnull

	GLog->Logf(L"Vertex Count : %d", vertexCount);
	GLog->Logf(L"Index Count : %d", indexCount);

	//------------------------------------------------------------------------------------------------------------
	// 	   @@ Save File Dialog
	//------------------------------------------------------------------------------------------------------------
	// -> On Save File Dialog(WinAPI)
	IMainFrameModule& mainFrame = FModuleManager::LoadModuleChecked<IMainFrameModule>("MainFrame");
	void* handle = mainFrame.GetParentWindow()->GetNativeWindow()->GetOSWindowHandle();

	FString path;
	TArray<FString> fileNames;

	IDesktopPlatform* platform = FDesktopPlatformModule::Get();
	platform->SaveFileDialog(handle, "Save", path, "", "Binary File(*.bin) | *.bin", EFileDialogFlags::None, fileNames);

	if (fileNames.Num() < 1) return FReply::Unhandled();

	// -> Save File Archive
	FVectexData data;

	TArray<FColor> colors;
	colorBuffer.GetVertexColors(colors);
	if (colors.Num() < 1)
	{
		for (uint32 i = 0; i < vertexCount; i++)
			colors.Add(FColor::White);
	}

	for (uint32 i = 0; i < vertexCount; i++)
	{
		data.Positions.Add(positionBuffer.VertexPosition(i));
		data.Normals.Add(metaBuffer.VertexTangentZ(i));		// Normal vector
		data.UVs.Add(metaBuffer.GetVertexUV(i, 0));
		data.Colors.Add(colors[i]);
	}

	TArray<uint32> indices;
	indexBuffer.GetCopy(indices);
	data.Indices.Insert((int32*)indices.GetData(), indexCount, 0);

	FBufferArchive buffer;

	buffer << data;

	// -> Save File(*.bin)
	FFileHelper::SaveArrayToFile(buffer, *fileNames[0]);
	buffer.FlushCache();
	buffer.Empty();

	FString str;
	str.Append(FPaths::GetCleanFilename(fileNames[0]));
	str.Append(" Binary File Saved");
	GLog->Log(str);

	// -> Save File(*.csv)
	FString planeText;
	for (uint32 i = 0; i < vertexCount; i++)
	{
		planeText.Append(data.Positions[i].ToString() + ",");
		planeText.Append(data.Normals[i].ToString() + ",");
		planeText.Append(data.UVs[i].ToString() + "\n");
	}

	FString planeTextPath = FPaths::GetBaseFilename(fileNames[0], false);
	planeTextPath.Append(".csv");
	FFileHelper::SaveStringToFile(planeText, *planeTextPath);

	return FReply::Handled();
}