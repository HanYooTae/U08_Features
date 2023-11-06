#include "DebuggerCategory.h"
#include "CanvasItem.h"
#include "GameFramework/PlayerController.h"

FDebuggerCategory::FDebuggerCategory()
{
	bShowOnlyWithDebugActor = false;
}

FDebuggerCategory::~FDebuggerCategory()
{
}

TSharedRef<FGameplayDebuggerCategory> FDebuggerCategory::MakeInstance()
{
	return MakeShareable(new FDebuggerCategory());
}

void FDebuggerCategory::CollectData(APlayerController* OwnerPC, AActor* DebugActor)
{
	FGameplayDebuggerCategory::CollectData(OwnerPC, DebugActor);

	APawn* playerPawn = OwnerPC->GetPawn();

	// Player
	{
		PlayerPawnData.Name = playerPawn->GetName();
		PlayerPawnData.Location = playerPawn->GetActorLocation();
		PlayerPawnData.Forward = playerPawn->GetActorForwardVector();
	}

	// ForwardActor
	{
		FHitResult hitResult;
		FVector start = PlayerPawnData.Location;
		FVector end = start * 10000.f;

		FCollisionQueryParams queryParams;
		queryParams.AddIgnoredActor(playerPawn);

		playerPawn->GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECollisionChannel::ECC_Visibility, queryParams);

		if (hitResult.bBlockingHit)
		{
			ForwardActorData.Name = hitResult.GetActor()->GetName();
			ForwardActorData.Location = hitResult.GetActor()->GetActorLocation();
			ForwardActorData.Forward = hitResult.GetActor()->GetActorForwardVector();
		}

		else
		{
			ForwardActorData.Name = "No Trace Forward Actor";
			ForwardActorData.Location = FVector::ZeroVector;
			ForwardActorData.Forward = FVector::ZeroVector;
		}
	}

	// DebugActor
	{
		if (DebugActor != nullptr)
		{
			DebugActorData.Name = DebugActor->GetName();
			DebugActorData.Location = DebugActor->GetActorLocation();
			DebugActorData.Forward = DebugActor->GetActorForwardVector();
		}

		else
		{
			DebugActorData.Name = "No Debug Actor";
			DebugActorData.Location = FVector::ZeroVector;
			DebugActorData.Forward = FVector::ZeroVector;
		}
	}
}

void FDebuggerCategory::DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext)
{
	FGameplayDebuggerCategory::DrawData(OwnerPC, CanvasContext);

	FCanvasTileItem item(FVector2D(10, 10), FVector2D(300, 230), FLinearColor(0, 0, 0, 0.5f));
	item.BlendMode = ESimpleElementBlendMode::SE_BLEND_AlphaBlend;
	CanvasContext.DrawItem(item, CanvasContext.CursorX, CanvasContext.CursorY);

	CanvasContext.Printf(FColor::Green, L"-- Player Pawn --");
	CanvasContext.Printf(FColor::White, L"Name : %s", *PlayerPawnData.Name);
	CanvasContext.Printf(FColor::White, L"Location : %s", *PlayerPawnData.Location.ToString());
	CanvasContext.Printf(FColor::White, L"Forward : %s", *PlayerPawnData.Forward.ToString());

	CanvasContext.Printf(FColor::White, L"");
	CanvasContext.Printf(FColor::White, L"Name : %s", *ForwardActorData.Name);
	CanvasContext.Printf(FColor::White, L"Location : %s", *ForwardActorData.Location.ToString());
	CanvasContext.Printf(FColor::White, L"Forward : %s", *ForwardActorData.Forward.ToString());

	CanvasContext.Printf(FColor::White, L"");
	CanvasContext.Printf(FColor::White, L"Name : %s", *DebugActorData.Name);
	CanvasContext.Printf(FColor::White, L"Location : %s", *DebugActorData.Location.ToString());
	CanvasContext.Printf(FColor::White, L"Forward : %s", *DebugActorData.Forward.ToString());
}
