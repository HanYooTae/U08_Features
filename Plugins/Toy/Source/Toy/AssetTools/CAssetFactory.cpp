#include "CAssetFactory.h"
#include "CAsset.h"

UCAssetFactory::UCAssetFactory()
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UCAsset::StaticClass();
}

UObject* UCAssetFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext)
{
	UE_LOG(LogTemp, Error, L"%s is created as uasset file", *InParent->GetName());
	return NewObject<UCAsset>(InParent, InClass, InName, Flags);
}