#pragma once

#include "CoreMinimal.h"
#include "OmegaTypes.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "OmegaMovementComponent.generated.h"

class AOmegaPlayerController;
class AOmegaCharacter;
enum class EOmegaCustomMovementMode : uint8;
struct FInputActionValue;

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

	TObjectPtr<AOmegaCharacter> OmegaOwner;
	TObjectPtr<AOmegaPlayerController> OmegaController;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EOmegaCustomMovementMode OmegaCustomMovementMode = EOmegaCustomMovementMode::None;

	
	// -------------------------------------
	//  COMMON
	// -------------------------------------
	
	float InitialWalkDeceleration;

	float BaseWalkSpeed;
	
public:

	FORCEINLINE float GetBaseWalkSpeed() const { return BaseWalkSpeed; } 

	
#pragma region JUMP

public:
	
	UFUNCTION()
	void PerformJump(const FInputActionValue& InputActionValue) const;

private:
	
	bool IsValidJump() const;

public:

	UPROPERTY(EditAnywhere, Category = "Omega Movement|Jump", DisplayName = "Debug")
	bool bJumpDebug = false;

#pragma endregion

#pragma region CROUCH

public:
	
	UFUNCTION()
	void PerformCrouch(const FInputActionValue& InputActionValue);

	

	
#pragma endregion

#pragma region DASH


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
	void OnDashFinished();
	
	UPROPERTY(EditAnywhere, Category = "Omega Movement|Dash")
	float DashImpulse = 1000.f;

	UPROPERTY(EditAnywhere, Category = "Omega Movement|Dash")
	float DashCooldown = 1.f;


#pragma endregion

#pragma region MANTLE

public:

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

#pragma endregion
	
};
