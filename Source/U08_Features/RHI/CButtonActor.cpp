#include "CButtonActor.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceConstant.h"

ACButtonActor::ACButtonActor()
{
	CHelpers::CreateSceneComponent(this, &Mesh, "Mesh");

	UStaticMesh* meshAsset;
	CHelpers::GetAsset<UStaticMesh>(&meshAsset, "StaticMesh'/Game/StaticMeshes/SM_Merged.SM_Merged'");

	
	CHelpers::GetAsset<UMaterialInstanceConstant>(&Material, "MaterialInstanceConstant'/Game/Materials/Surface/MAT_Shuffle.MAT_Shuffle'");

	Mesh->SetStaticMesh(meshAsset);
	Mesh->SetMaterial(0, Material);
}

#if WITH_EDITOR
void ACButtonActor::ShuffleMaterial()
{
	int32 random = UKismetMathLibrary::RandomIntegerInRange(0, (int32)EMaterialType::Max - 1);

	for (const auto& value : Material->TextureParameterValues)
	{
		if (value.ParameterInfo.Name.Compare("BaseMap") == 0)
			Material->SetTextureParameterValueEditorOnly(value.ParameterInfo, MaterialParameters[random].BaseMap);

		if (value.ParameterInfo.Name.Compare("NormalMap") == 0)
			Material->SetTextureParameterValueEditorOnly(value.ParameterInfo, MaterialParameters[random].NormalMap);

		if (value.ParameterInfo.Name.Compare("RoughnessMap") == 0)
			Material->SetTextureParameterValueEditorOnly(value.ParameterInfo, MaterialParameters[random].RoughnessMap);
	}

	for (const auto& value : Material->ScalarParameterValues)
	{
		if (value.ParameterInfo.Name.Compare("Metalic") == 0)
			Material->SetScalarParameterValueEditorOnly(value.ParameterInfo, MaterialParameters[random].Metalic);

		if (value.ParameterInfo.Name.Compare("Roughness_Min") == 0)
			Material->SetScalarParameterValueEditorOnly(value.ParameterInfo, MaterialParameters[random].Roughness_Min);

		if (value.ParameterInfo.Name.Compare("Roughness_Max") == 0)
			Material->SetScalarParameterValueEditorOnly(value.ParameterInfo, MaterialParameters[random].Roughness_Max);
	}

}
#endif

void ACButtonActor::BeginPlay()
{
	Super::BeginPlay();
	
}