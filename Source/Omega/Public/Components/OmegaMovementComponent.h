#pragma once

#include "CoreMinimal.h"
#include "OmegaTypes.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "OmegaMovementComponent.generated.h"

class AOmegaPlayerController;
class AOmegaCharacter;
struct FInputActionValue;


UENUM(BlueprintType)
enum class EOmegaCustomMovementMode : uint8
{
	NONE	UMETA(Hidden),
	Dash	UMETA(DisplayName = "Dash"),
	Mantle	UMETA(DisplayName = "Mantle"),
	Slide	UMETA(DisplayName = "Slide"),
	MAX		UMETA(Hidden)
};


DECLARE_MULTICAST_DELEGATE(FOnMovementEventSignature);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class OMEGA_API UOmegaMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	
	UOmegaMovementComponent();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:

	virtual void BeginPlay() override;

public:
	
	void BindDependencies(AController* OwningController);
	void UpdateCapsulePosition(float DeltaTime) const;

	UFUNCTION(BlueprintPure)
	FORCEINLINE EOmegaCustomMovementMode GetOmegaCustomMovementMode() const { return OmegaCustomMovementMode; } 

private:

	TObjectPtr<AOmegaCharacter> OmegaCharacterOwner;
	TObjectPtr<AOmegaPlayerController> OmegaController;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EOmegaCustomMovementMode OmegaCustomMovementMode = EOmegaCustomMovementMode::NONE;

protected:

	
	//  STORE INITIAL VALUES
	// =============================

public:
	
	float InitialWalkDeceleration;
	float InitialWalkSpeed;
	float InitialGroundFriction;


	//  COMMON FUNCTIONS
	// =============================

	void HandleHit();
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetOmegaCustomMovementMode(EOmegaCustomMovementMode NewCustomMode)					{ OmegaCustomMovementMode = NewCustomMode; }
	FORCEINLINE float GetBaseWalkSpeed() const															{ return InitialWalkSpeed; }
	FORCEINLINE bool IsCustomMovementMode(EOmegaCustomMovementMode InOmegaCustomMovementMode) const		{ return MovementMode == MOVE_Custom && OmegaCustomMovementMode == InOmegaCustomMovementMode; }
	
	// =============================
	//  UPDATE MOVEMENT
	// =============================

protected:
	
	/**
	 *	Automatically called at the end of every perform move.
	 * 
	 * @param DeltaSeconds 
	 * @param OldLocation 
	 * @param OldVelocity 
	 */
	virtual void OnMovementUpdated(float DeltaSeconds, const FVector& OldLocation, const FVector& OldVelocity) override;

	
	// =============================
	//  JUMP
	// =============================
	
public:
	
	UFUNCTION()
	void PerformJump(const FInputActionValue& InputActionValue) const;

private:
	
	bool IsValidJump() const;

public:

	UPROPERTY(EditAnywhere, Category = "Omega Movement|Jump", DisplayName = "Debug")
	bool bJumpDebug = false;

	
	// =============================
	//  CROUCH
	// =============================

public:

	UFUNCTION(BlueprintCallable)
	void HandleCrouch(const FInputActionValue& InputActionValue);

	UFUNCTION(BlueprintCallable)
	bool IsCrouchValid(const FInputActionValue& InputActionValue) const;
	
	UFUNCTION()
	void PerformCrouch(const FInputActionValue& InputActionValue);


	// =============================
	//  DASH
	// =============================

public:
	
	UFUNCTION(BlueprintCallable)
	void HandleDash(const FInputActionValue& InputActionValue);

private:
	
	void PerformDash();
	bool IsValidDash();
	
	float DashStarTime = 0.f;

	bool bFirstDash = true;
	bool bDashValid = true;

protected:

	UFUNCTION(BlueprintCallable, Category = "Omega Movement|Dash" )
	void ExitDash();
	
	UPROPERTY(EditAnywhere, Category = "Omega Movement|Dash")
	float DashImpulse = 1000.f;

	UPROPERTY(EditAnywhere, Category = "Omega Movement|Dash")
	float DashCooldown = 1.f;

	UPROPERTY(EditAnywhere, Category = "Omega Movement|Dash")
	float AdjustedGroundFriction = 4.f;

	
	//  CLIMB
	// =============================

	UFUNCTION()
	void HandleMantle(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	bool IsMantleValid(const FHitResult& InHitResult, FVector& OutMantleTargetPoint);
	
	void PerformMantle(const FVector& MantleTargetPoint);

	UFUNCTION(BlueprintCallable, Category = "Omega Movement|Mantle" )
	void OnMantleFinished();

	UFUNCTION(Exec, DisplayName = "ShowDebug Mantle")
	FORCEINLINE void ShowDebugMantle() { bMantleDebug = !bMantleDebug; }
	
	FTimerHandle MantleCheckResetTimer;
	FTimerDelegate OnMantleResetDelegate;

	UPROPERTY(EditAnywhere, Category = "Omega Movement|Mantle", DisplayName = "Check Interval")
	float MantleCheckInterval = 0.f;

	FVector MantleTargetLocation;
	
	UPROPERTY(EditAnywhere, Category = "Omega Movement|Mantle", DisplayName = "Grab Height")
	float GrabHeight = 25.f;

	UPROPERTY(EditAnywhere, Category = "Omega Movement|Mantle", DisplayName = "Animation Speed")
	float MantleAnimationSpeed = 2.f;

	UPROPERTY(EditAnywhere, Category = "Omega Movement|Mantle", DisplayName = "Debug")
	bool bMantleDebug = false;
	
	bool bValidateMantle = false;
};
