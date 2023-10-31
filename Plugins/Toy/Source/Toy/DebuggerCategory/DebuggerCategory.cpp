#include "DebuggerCategory.h"

FDebuggerCategory::FDebuggerCategory()
{
}

FDebuggerCategory::~FDebuggerCategory()
{
}

TSharedRef<FGameplayDebuggerCategory> FDebuggerCategory::MakeInstance()
{
	return MakeShareable(new FDebuggerCategory());
}
