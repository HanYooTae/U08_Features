#include "Toy.h"
#include "ToolBar/ButtonCommand.h"
#include "ToolBar/IconStyle.h"
#include "LevelEditor.h"
#include "DebuggerCategory/DebuggerCategory.h"
#include "GameplayDebugger.h"
//#include "Brushes/SlateImageBrush.h"

#define LOCTEXT_NAMESPACE "FToyModule"

void FToyModule::StartupModule()
{
	UE_LOG(LogTemp, Error, TEXT("Startup Toy Module"));

	// ToolBar
	{
		FIconStyle::Get();
		FButtonCommand::Register();

		Extender = MakeShareable(new FExtender());

		FToolBarExtensionDelegate toolBarExtensionDelegate = FToolBarExtensionDelegate::CreateRaw(this, &FToyModule::AddToolBar_SpawnVertex);
		Extender->AddToolBarExtension("Compile", EExtensionHook::Before, FButtonCommand::Get().SpawnVertexCommand, toolBarExtensionDelegate);

		FToolBarExtensionDelegate toolBarExtensionDelegate2 = FToolBarExtensionDelegate::CreateRaw(this, &FToyModule::AddToolBar_OpenViewer);
		Extender->AddToolBarExtension("Compile", EExtensionHook::Before, FButtonCommand::Get().SpawnVertexCommand, toolBarExtensionDelegate2);

		FLevelEditorModule& levelEditor = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
		levelEditor.GetToolBarExtensibilityManager()->AddExtender(Extender);
	}

	// DebuggerCategory
	{
		IGameplayDebugger& gameplayDebugger = IGameplayDebugger::Get();
		IGameplayDebugger::FOnGetCategory categoryDelegate = IGameplayDebugger::FOnGetCategory::CreateStatic(&FDebuggerCategory::MakeInstance);
		gameplayDebugger.Get().RegisterCategory("AwesomData", categoryDelegate, EGameplayDebuggerCategoryState::EnabledInGameAndSimulate, 5);
		gameplayDebugger.NotifyCategoriesChanged();
	}
}

void FToyModule::ShutdownModule()
{
	UE_LOG(LogTemp, Error, TEXT("Shutdown Toy Module"));

	if (IGameplayDebugger::IsAvailable())
		IGameplayDebugger::Get().UnregisterCategory("AwesomData");

	FIconStyle::Shutdown();
}

void FToyModule::AddToolBar_SpawnVertex(FToolBarBuilder& InToolBarBuilder)
{
	InToolBarBuilder.AddSeparator();
	InToolBarBuilder.AddToolBarButton
	(
		FButtonCommand::Get().SpawnVertexButton,
		NAME_None,
		FText::FromString("Spawn Vertex"),
		FText::FromString("Spawn Vertex from Binary file"),
		FIconStyle::Get()->SpawnVertexButtonIcon
	);
}

void FToyModule::AddToolBar_OpenViewer(FToolBarBuilder& InToolBarBuilder)
{
	InToolBarBuilder.AddToolBarButton
	(
		FButtonCommand::Get().OpenViewerButton,
		NAME_None,
		FText::FromString("Open Viewer"),
		FText::FromString("OPen Customization Viewer"),
		FIconStyle::Get()->OpenViewerButtonIcon
	);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FToyModule, Toy)