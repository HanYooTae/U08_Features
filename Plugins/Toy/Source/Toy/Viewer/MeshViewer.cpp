#include "MeshViewer.h"
#include "MeshViewer_Viewport.h"
#include "AdvancedPreviewSceneModule.h"

TSharedPtr<FMeshViewer> FMeshViewer::Instance = nullptr;
const static FName ToolkitName = L"MeshViewer";
const static FName ViewportTabID = L"Viewport";
const static FName PreviewTabID = L"Preview";
const static FName DetailsTabID = L"Details";

void FMeshViewer::OpenWindow(UObject* InAsset)
{
	if (Instance.IsValid())
	{
		Instance->CloseWindow();
		Instance = nullptr;
	}

	Instance = MakeShareable(new FMeshViewer());
	Instance->OpenWindow_Internal(InAsset);
}

void FMeshViewer::Shutdown()
{
	if (Instance.IsValid())
		Instance->CloseWindow();
}

void FMeshViewer::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	FOnSpawnTab viewportSpawnEvent = FOnSpawnTab::CreateSP(this, &FMeshViewer::SpawnViewportTab);
	TabManager->RegisterTabSpawner(ViewportTabID, viewportSpawnEvent);

	FOnSpawnTab previewSpawnEvent = FOnSpawnTab::CreateSP(this, &FMeshViewer::SpawnPreviewSceneSettingsTab);
	TabManager->RegisterTabSpawner(PreviewTabID, previewSpawnEvent);

	FOnSpawnTab detailsSpawnEvent = FOnSpawnTab::CreateSP(this, &FMeshViewer::SpawnDetailsViewTab);
	TabManager->RegisterTabSpawner(DetailsTabID, detailsSpawnEvent);
}

TSharedRef<SDockTab> FMeshViewer::SpawnViewportTab(const FSpawnTabArgs& InArgs)
{
	// TSharedRef<SWidget> <- SNew
	return SNew(SDockTab)
		[
			ViewportWidget.ToSharedRef()
		];
}

TSharedRef<SDockTab> FMeshViewer::SpawnPreviewSceneSettingsTab(const FSpawnTabArgs& InArgs)
{
	return SNew(SDockTab)
		[
			PreviewSceneSettingsWidget.ToSharedRef()
		];
}

TSharedRef<SDockTab> FMeshViewer::SpawnDetailsViewTab(const FSpawnTabArgs& InArgs)
{
	return SNew(SDockTab)
		[
			DetailsViewWidget.ToSharedRef()
		];
}

void FMeshViewer::OpenWindow_Internal(UObject* InAsset)
{
	//Create SlateWidget
	ViewportWidget = SNew(SMeshViewer_Viewport);

	FAdvancedPreviewSceneModule& previewSceneSettings = FModuleManager::LoadModuleChecked<FAdvancedPreviewSceneModule>("AdvancedPreviewScene");
	PreviewSceneSettingsWidget = previewSceneSettings.CreateAdvancedPreviewSceneSettingsWidget(ViewportWidget->GetScene());

	FPropertyEditorModule& properyEditor = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	FDetailsViewArgs args(false, false, true, FDetailsViewArgs::ObjectsUseNameArea);
	DetailsViewWidget = properyEditor.CreateDetailView(args);
	DetailsViewWidget->SetObject(InAsset);

	// Create Layout
	TSharedRef<FTabManager::FLayout> layout = FTabManager::NewLayout("MeshViewer_Layout")
		->AddArea
		(
			FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
			// Toolbar
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.1f)
				->AddTab(GetToolbarTabId(), ETabState::OpenedTab)
			)
			// Panel(대)
			->Split
			(
				FTabManager::NewSplitter()->SetOrientation(Orient_Horizontal)
				
				// (중) Viewport
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.75f)
					->AddTab(ViewportTabID, ETabState::OpenedTab)
				)
				// END(중) Viewport

				// (중) RightPanel
				->Split
				(
					FTabManager::NewSplitter()->SetOrientation(Orient_Vertical)
					->SetSizeCoefficient(0.25f)
					// (소) Preview
					->Split
					(
						FTabManager::NewStack()
						->AddTab(PreviewTabID, ETabState::OpenedTab)
					)
					// (소) Details
					->Split
					(
						FTabManager::NewStack()
						->AddTab(DetailsTabID, ETabState::OpenedTab)
					)
				) // End(중) RightPanel
			)//END(대)
		);

	// Open Slate Window
	FAssetEditorToolkit::InitAssetEditor
	(
		EToolkitMode::Standalone/*별도의 창으로*/,
		TSharedPtr<IToolkitHost>(),
		ToolkitName,
		layout,
		true/*검색창*/,
		true/*툴바아이콘*/,
		InAsset
	);
}

FName FMeshViewer::GetToolkitFName() const
{
	return ToolkitName;
}

FText FMeshViewer::GetBaseToolkitName() const
{
	return FText::FromName(ToolkitName);
}

FString FMeshViewer::GetWorldCentricTabPrefix() const
{
	return ToolkitName.ToString();
}

FLinearColor FMeshViewer::GetWorldCentricTabColorScale(void) const
{
	return FLinearColor();
}
