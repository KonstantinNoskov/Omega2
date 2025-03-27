#include "Player/OmegaPlayerCameraManager.h"

#include "Characters/PlayerCharacters/PlayerBaseCharacter.h"
#include "Components/OmegaMovementComponent.h"
#include "Player/OmegaPlayerController.h"

void AOmegaPlayerCameraManager::BeginPlay()
{
	Super::BeginPlay();
	
	OmegaController = Cast<AOmegaPlayerController>(GetOwningPlayerController());
	PlayerCharacter = Cast<APlayerBaseCharacter>(GetOwningPlayerController()->GetPawn());
	OmegaMovement = PlayerCharacter->GetOmegaMovementComponent();
}

AOmegaPlayerCameraManager::AOmegaPlayerCameraManager()
{
	InitialCameraOffset = 0.f; 
}


//  DEBUG
// =============================

bool AOmegaPlayerCameraManager::ProcessConsoleExec(const TCHAR* Cmd, FOutputDevice& Ar, UObject* Executor)
{
	bool bHandled = Super::ProcessConsoleExec(Cmd, Ar, Executor);
	if (!bHandled)
	{
		bHandled &= OmegaController->ProcessConsoleExec(Cmd, Ar, Executor);
	}
	return bHandled;
}


//  UPDATE VIEW TARGET
// =============================

void AOmegaPlayerCameraManager::UpdateViewTarget(FTViewTarget& OutVT, float DeltaTime)
{
	
	Super::UpdateViewTarget(OutVT, DeltaTime);

	// Apply zoom offset 
	HandleZoom(OutVT, DeltaTime);
	
}

void AOmegaPlayerCameraManager::HandleZoom(FTViewTarget& OutVT, float DeltaTime)
{
	if (!PlayerCharacter || !OmegaMovement) return;

	FVector TargetZoomOffset = FVector(
		0.f,
		ZoomOffset,
		0.f
	);


	// Is Character Moving?
	bool bIsMoving = FMath::Abs(PlayerCharacter->GetVelocity().Length()) > 0.f;

	// Optional: ZoomOut should be faster than the ZoomIn.  
	float ZoomBlendDuration = bIsMoving ? ZoomOutBlendDuration : ZoomInBlendDuration;

	// Calculate Current Offset
	FVector Offset = FMath::Lerp(FVector::ZeroVector, TargetZoomOffset, ZoomBlendTime * ZoomBlendDuration);
	
	// If character is moving
	if (bIsMoving)
	{
		ZoomBlendTime = FMath::Clamp(ZoomBlendTime + DeltaTime, 0.f, 1.f);
	}

	// If character is moving
	if (!bIsMoving)
	{
		ZoomBlendTime = FMath::Clamp(ZoomBlendTime - DeltaTime, 0.f, 1.f);
	}
	
	//Offset.Y = FMath::Clamp(Offset.Y, 0.f, ZoomOffset);
	OutVT.POV.Location += Offset;

	// Debug 
	if (bDebug)
	{
		GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Cyan, FString::Printf(TEXT("Velocity.Length: %f"), PlayerCharacter->GetVelocity().X));
		GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Magenta, FString::Printf(TEXT("Offset: %s"), *Offset.ToString()));
		GEngine->AddOnScreenDebugMessage(2, 1.f, FColor::Green, FString::Printf(TEXT("POV.Location: %s"), *Offset.ToString()));
		GEngine->AddOnScreenDebugMessage(3, 1.f, FColor::Yellow, FString::Printf(TEXT("ZoomBlendTime: %f"),ZoomBlendTime));
	}
	
}
