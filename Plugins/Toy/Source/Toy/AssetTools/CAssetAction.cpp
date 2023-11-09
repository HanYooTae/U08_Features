#include "CAssetAction.h"
#include "CAsset.h"

CAssetAction::CAssetAction(EAssetTypeCategories::Type InCategory)
	: Category(InCategory)
{
}

CAssetAction::~CAssetAction()
{
}

FText CAssetAction::GetName() const
{
	return FText::FromString(TEXT("Awesome Asset"));
}

FColor CAssetAction::GetTypeColor() const
{
	return FColor::Yellow;
}

UClass* CAssetAction::GetSupportedClass() const
{
	return UCAsset::StaticClass();
}

uint32 CAssetAction::GetCategories()
{
	return Category;
}
