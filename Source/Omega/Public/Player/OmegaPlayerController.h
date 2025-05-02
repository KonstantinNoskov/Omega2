#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "OmegaTypes.h"
#include "GameFramework/PlayerController.h"
#include "OmegaPlayerController.generated.h"

class UDamageTextComponent;
class UOmegaMovementComponent;
class UOmegaAbilitySystemComponent;
class UOmegaInputConfig;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnInputRecievedSignature, const FInputActionValue& Input)

UCLASS()
class OMEGA_API AOmegaPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	AOmegaPlayerController();
	
protected:
	
	virtual void BeginPlay() override;


	// -------------------------------------
	//  SETUP
	// -------------------------------------

protected:
	
	virtual void SetupInputComponent() override;
	void AssignMappingContext() const;

private:
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UOmegaInputConfig> InputConfig;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> InputMappingContext;

	
	// -------------------------------------
	//  DELEGATES
	// -------------------------------------

public:
	
	FOnInputRecievedSignature OnJumpInputDelegate;
	FOnInputRecievedSignature OnCrouchInputDelegate;
	FOnInputRecievedSignature OnMoveInputDelegate;

	// -------------------------------------
	//  INPUT
	// -------------------------------------

private:

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);

	float ShortPressThreshold = .3f;
	float ElapsedPressTime = 0.f; 
	bool bShortPressed = true;
	
	// -------------------------------------
	//  COMMON
	// -------------------------------------

public:

	UOmegaAbilitySystemComponent* GetOmegaAbilitySystemComponent();
	UOmegaMovementComponent* GetOmegaMovementComponent();

private:
	
	UPROPERTY()
	TObjectPtr<UOmegaAbilitySystemComponent> OmegaAbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UOmegaMovementComponent> OmegaMovementComponent;
	
private:

	void RotateController();
	
	void Move(const FInputActionValue& InputActionValue);
	void Jump(const FInputActionValue& InputActionValue);
	void Crouch(const FInputActionValue& InputActionValue);
	
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> CrouchAction;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> PrimaryAttackAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> SecondaryAttackAction;

	
	// -------------------------------------
	//  DASH ACTION
	// -------------------------------------

private:

	void Dash(const FInputActionValue& InputActionValue);

public:
	
	FOnInputRecievedSignature OnDashInputDelegate;

private:
	
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> DashAction;


	// -------------------------------------
	//  DAMAGE WIDGET
	// -------------------------------------
	
public:
	
	UFUNCTION()
	void ShowFloatingText(const FDamageEffectContextData& DamageHandle, ACharacter* TargetCharacter);
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageTextComponent> DamageTextComponentClass;
};
