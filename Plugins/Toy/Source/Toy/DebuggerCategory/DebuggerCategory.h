#pragma once

#include "CoreMinimal.h"
#include "GameplayDebuggerCategory.h"

class TOY_API FDebuggerCategory : public FGameplayDebuggerCategory
{
public:
	FDebuggerCategory();
	~FDebuggerCategory();

public:
	static TSharedRef<FGameplayDebuggerCategory> MakeInstance();
};
