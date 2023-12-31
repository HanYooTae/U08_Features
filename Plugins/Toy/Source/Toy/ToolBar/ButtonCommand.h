#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"

class TOY_API FButtonCommand : public TCommands<FButtonCommand>
{
public:
	FButtonCommand();
	~FButtonCommand();

public:
	virtual void RegisterCommands() override;

private:
	void SpawnVertexButton_Pressed();
	void OPenViewerButton_Pressed();

public:
	TSharedPtr<FUICommandInfo> SpawnVertexButton;
	TSharedPtr<FUICommandInfo> OpenViewerButton;

	TSharedPtr<FUICommandList> SpawnVertexCommand;
};
