#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "OmegaPlayerCameraManager.generated.h"


class AOmegaPlayerController;
class APlayerBaseCharacter;
class UOmegaMovementComponent;

UCLASS()
class OMEGA_API AOmegaPlayerCameraManager : public APlayerCameraManager
{
protected:
	
	virtual void BeginPlay() override;

private:
	GENERATED_BODY()

	AOmegaPlayerCameraManager();

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<APlayerBaseCharacter> PlayerCharacter;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UOmegaMovementComponent> OmegaMovement;
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<AOmegaPlayerController> OmegaController;
	
	float BlendTime;

	//  DEBUG
	// =============================

public:
	
	virtual bool ProcessConsoleExec(const TCHAR* Cmd, FOutputDevice& Ar, UObject* Executor) override;
	
protected:

	UPROPERTY(EditDefaultsOnly, Category = "Omega")
	bool bDebug = false;

public:
	
	UFUNCTION(Exec, DisplayName = "Debug Camera")
	FORCEINLINE void DebugCamera() { bDebug = !bDebug; }

protected:

	float InitialCameraOffset;
	
	float MaxHorizontalOffset = 300.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Omega|Direction Offset")
	float BlendDuration = .2f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Omega|Direction Offset")
	float WalkTargetOffset = 200.f;
	
	float ForwardOffset = 100.f;

	UPROPERTY(EditDefaultsOnly, Category = "Omega|Direction Offset", meta = (ClampMin = 0.f, ClampMax = 1.f))
	float ZoomOutScale = .1f;

	UPROPERTY(EditDefaultsOnly, Category = "Omega|Direction Offset", meta = (ClampMin = 0.f, ClampMax = 1.f))
	float ZoomInScale = .1f;
	
	virtual void UpdateViewTarget(FTViewTarget& OutVT, float DeltaTime) override;


	//  ZOOM 
	// =============================

private:

	float ZoomBlendTime;
	
protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "Omega|Zoom")
	float ZoomOutBlendDuration = .2f;

	UPROPERTY(EditDefaultsOnly, Category = "Omega|Zoom")
	float ZoomInBlendDuration = .5f;

	UPROPERTY(EditDefaultsOnly, Category = "Omega|Zoom")
	float ZoomOffset = 200.f;
	
	void HandleZoom(FTViewTarget& OutVT, float DeltaTime);
};
