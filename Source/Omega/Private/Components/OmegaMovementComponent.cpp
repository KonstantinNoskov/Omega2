#include "Components/OmegaMovementComponent.h"

#include "InputActionValue.h"
#include "KismetTraceUtils.h"
#include "OmegaCollisionChannels.h"
#include "PaperCharacter.h"
#include "BehaviorTree/Blackboard/BlackboardKeyEnums.h"
#include "Characters/OmegaCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/OmegaPlayerController.h"

UOmegaMovementComponent::UOmegaMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	NavAgentProps.bCanCrouch = true;

	InitialWalkSpeed = MaxWalkSpeed;
	InitialGroundFriction = GroundFriction;

	SetWalkableFloorAngle(50.f);

	// Constrain to Plane
	bConstrainToPlane = true;
	SetPlaneConstraintAxisSetting(EPlaneConstraintAxisSetting::Y);
	
}

void UOmegaMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	InitialWalkDeceleration = BrakingDecelerationWalking;
}
void UOmegaMovementComponent::BindDependencies(AController* OwningController)
{
	OmegaCharacterOwner = Cast<AOmegaCharacter>(GetOwner());
	OmegaController = Cast<AOmegaPlayerController>(OwningController);
	
	if (OmegaCharacterOwner)
	{
		OmegaCharacterOwner->GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &UOmegaMovementComponent::HandleMantle);
	}
	else { UE_LOG(LogTemp, Error, TEXT("[%hs]: OmegaOwner is null!"),__FUNCTION__);	}
	
}
void UOmegaMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateCapsulePosition(DeltaTime);
}


//  COMMON FUNCTIONS
// =============================

void UOmegaMovementComponent::HandleHit()
{
	// Dash behavior on Capsule Hit
	if (Velocity.Length() > 0 && OmegaCustomMovementMode == EOmegaCustomMovementMode::Dash)
	{
		ExitDash();	
	}
}


// JUMP
// =============================

void UOmegaMovementComponent::OnMovementUpdated(float DeltaSeconds, const FVector& OldLocation, const FVector& OldVelocity)
{
	Super::OnMovementUpdated(DeltaSeconds, OldLocation, OldVelocity);
}
void UOmegaMovementComponent::PerformJump(const FInputActionValue& InputActionValue) const
{
	const float InputBool = InputActionValue.Get<bool>();
	
	if (OmegaCharacterOwner)
	{	
		if (InputBool && IsValidJump())
		{
			OmegaCharacterOwner->Jump();
		}
	}
}
bool UOmegaMovementComponent::IsValidJump() const 
{
	const bool bNotValid = !OmegaCharacterOwner || IsCrouching();

	if(bNotValid) return false;
	
	FHitResult HitResult;
	const UWorld* World = GetWorld();
	const float CapsuleHalfHeight = OmegaCharacterOwner->GetCapsuleComponent()->GetScaledCapsuleHalfHeight() * .5f;
	const FVector TraceStart = OmegaCharacterOwner->GetCapsuleComponent()->GetComponentLocation() + FVector(0.f,0.,CapsuleHalfHeight) * 2;
	const FVector TraceEnd = TraceStart + FVector(0.f,0.f, 10.f);
	const float CapsuleRadius = OmegaCharacterOwner->GetCapsuleComponent()->GetScaledCapsuleRadius();
	
	UKismetSystemLibrary::CapsuleTraceSingle(
		World,
		TraceStart,
		TraceEnd,
		CapsuleRadius,
		CapsuleHalfHeight,
		ETraceTypeQuery::TraceTypeQuery1,
		false,
		TArray<AActor*>(),
		bJumpDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None,
		HitResult, true);

	const bool bJumpValid = !HitResult.bBlockingHit && OmegaCustomMovementMode != EOmegaCustomMovementMode::Dash; 

	return bJumpValid;
}


//  CROUCH
// =============================

void UOmegaMovementComponent::HandleCrouch(const FInputActionValue& InputActionValue)
{
	if (!IsCrouchValid(InputActionValue))
	{
		bWantsToCrouch = false;
		return;
	}
	
	PerformCrouch(InputActionValue);
}
bool UOmegaMovementComponent::IsCrouchValid(const FInputActionValue& InputActionValue) const
{	
	bool bValidCrouch =
		InputActionValue.Get<bool>() &&
		OmegaCharacterOwner &&
		//!IsFalling() &&
		//OmegaCustomMovementMode != EOmegaCustomMovementMode::Dash &&
			GetLastUpdateVelocity().Length() <= 0.f;

	return bValidCrouch;
}
void UOmegaMovementComponent::PerformCrouch(const FInputActionValue& InputActionValue)
{
	bWantsToCrouch = IsCrouchValid(InputActionValue) ? true : false;
	
}


//  DASH
// =============================

void UOmegaMovementComponent::HandleDash(const FInputActionValue& InputActionValue)
{
	if (IsValidDash() && OmegaCharacterOwner)
	{
		PerformDash();
	}
}
bool UOmegaMovementComponent::IsValidDash()
{
	const float CurrentTime = GetWorld()->GetTimeSeconds();

	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(
		HitResult,
		OmegaCharacterOwner->GetActorLocation(),
		OmegaCharacterOwner->GetActorLocation() + OmegaCharacterOwner->GetActorForwardVector() * 100.f,
		ECC_Visibility,
		FCollisionQueryParams()
		);
	
	bDashValid =
		!HitResult.bBlockingHit &&
		CurrentTime - DashStarTime >= DashCooldown ||
		bFirstDash;
		
	
	if (bDashValid)
	{	
		return IsWalking();
	}
	
	return false;
}
void UOmegaMovementComponent::PerformDash()
{
	
	bFirstDash = false;
	
	OmegaCustomMovementMode = EOmegaCustomMovementMode::Dash;
	BrakingDecelerationWalking = 1000.f;
	GroundFriction = AdjustedGroundFriction;
	
	DashStarTime = GetWorld()->GetTimeSeconds();
	
	const FVector DashDirection = (Acceleration.IsNearlyZero() ? OmegaCharacterOwner->GetActorForwardVector() : Acceleration).GetSafeNormal2D();
	
	Velocity = DashImpulse * DashDirection;
	
	const FQuat NewRotation = FRotationMatrix::MakeFromXZ(DashDirection, FVector::UpVector).ToQuat();
	
	FHitResult HitResult;
	SafeMoveUpdatedComponent(FVector::ZeroVector, NewRotation, false, HitResult);

	OmegaCharacterOwner->GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Enemy, ECR_Ignore);
	
}
void UOmegaMovementComponent::ExitDash()
{
	OmegaCustomMovementMode = EOmegaCustomMovementMode::NONE;
	
	OmegaCharacterOwner->GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Enemy, ECR_Overlap);
	BrakingDecelerationWalking = InitialWalkDeceleration;
	GroundFriction = InitialGroundFriction;
}


//  MANTLE
// =============================

void UOmegaMovementComponent::HandleMantle(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	FVector MantleTargetPoint;
	if (IsMantleValid(Hit, MantleTargetPoint))
	{
		PerformMantle(MantleTargetPoint);
	}
}
bool UOmegaMovementComponent::IsMantleValid(const FHitResult& InHitResult, FVector& OutMantleTargetPoint)
{
	/*
	 * CHECK №1: FLOOR/CEILING CHECK
	 *	HandleMantle function is called when Character Capsule OnHit event is triggered.
	 *	We should distinguish either we hit a floor/ceiling in which case stop function immediately or we hit a vertical wall and continue.
	 */


	// CHECK №1
	const bool bHorizontalHit = FVector::DotProduct(InHitResult.ImpactNormal, FVector::UpVector) == FMath::Abs(0.f) ? true : false;
	
	if (/*IsFalling() && */ bHorizontalHit && !bValidateMantle && OmegaCustomMovementMode != EOmegaCustomMovementMode::Dash)
	{
		// Set Mantle Check Timer to avoid every frame check
		OnMantleResetDelegate.BindLambda([this]()
		{
			bValidateMantle = false;
		});
		GetWorld()->GetTimerManager().SetTimer(MantleCheckResetTimer, OnMantleResetDelegate, MantleCheckInterval,false);
		
		bValidateMantle = true;

		// Local variables needed for calculation
		FHitResult HitResult = InHitResult; 
		const FVector ForwardVector = OmegaCharacterOwner->GetActorForwardVector();
		const float OwnerCapsuleHeight = OmegaCharacterOwner->GetCapsuleComponent()->GetScaledCapsuleHalfHeight() * 2.f;
		const float OwnerCapsuleRadius = OmegaCharacterOwner->GetCapsuleComponent()->GetScaledCapsuleRadius();
		const FVector HitPoint = HitResult.ImpactPoint;
		const FVector MantleHeightDistance = HitPoint + FVector(0.f,0.f,GrabHeight);
		const FVector Adjust_X = MantleHeightDistance + ForwardVector * FVector(OwnerCapsuleRadius, 0.f,0.f);
		const FVector ClimbTargetPoint = Adjust_X + FVector(0.f,0.f,-OwnerCapsuleHeight - 1.f) ;
		
		// Trace from HitPoint to Up-direction as far as GrabHeight property allows.
		UKismetSystemLibrary::LineTraceSingle(GetWorld(), HitPoint, MantleHeightDistance, TraceTypeQuery1, false, TArray<AActor*>(), bMantleDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None, HitResult, true);

		// Move forward just a little bit towards actor direction to be sure that next "Down-Trace" can hit the surface.
		// If on this stage the trace hits something it means there is solid wall in front of the character.
		UKismetSystemLibrary::LineTraceSingle(GetWorld(), MantleHeightDistance, Adjust_X, TraceTypeQuery1, false, TArray<AActor*>(), bMantleDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None, HitResult, true);
		if (HitResult.bBlockingHit) return false;	
		
		//  All the way down to check if there's a ground to mantle to
		UKismetSystemLibrary::LineTraceSingle(GetWorld(), Adjust_X, ClimbTargetPoint, TraceTypeQuery1, false, TArray<AActor*>(), bMantleDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None, HitResult, true);
		if (!HitResult.bBlockingHit) return false;

		const float ObstacleHeight = (HitPoint - HitResult.ImpactPoint).Z;
		if (ObstacleHeight > GrabHeight) return false;


		
		MantleTargetLocation = HitResult.ImpactPoint + FVector(0.f,0.f, OmegaCharacterOwner->GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
		UKismetSystemLibrary::CapsuleTraceSingle(
			GetWorld(),
			MantleTargetLocation,
			MantleTargetLocation,
			OmegaCharacterOwner->GetCapsuleComponent()->GetScaledCapsuleRadius(),
			OmegaCharacterOwner->GetCapsuleComponent()->GetScaledCapsuleHalfHeight() - 1.f,
			TraceTypeQuery1,
			false,
			TArray<AActor*>(),
			bMantleDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None,
			HitResult,
			true,
			FColor::Red,
			FColor::Green,
			2.f
			);

		if (HitResult.bBlockingHit) return false;
		
		OutMantleTargetPoint = MantleTargetLocation;
		
		return true;
	}
	return false;
}
void UOmegaMovementComponent::PerformMantle(const FVector& MantleTargetPoint)
{
	OmegaCustomMovementMode = EOmegaCustomMovementMode::Mantle;
	Velocity = FVector::ZeroVector;
	
	SetMovementMode(MOVE_Flying);
	OmegaCharacterOwner->GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Ignore);

	
	// Move Climb start location to be sure that animation is smooth
	FVector AdjustedLocation = FVector(
		OmegaCharacterOwner->GetCapsuleComponent()->GetScaledCapsuleRadius() * OmegaCharacterOwner->GetActorForwardVector().X * 1.5f, 
		0.f,
		OmegaCharacterOwner->GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
	
	OmegaCharacterOwner->SetActorLocation(MantleTargetPoint - AdjustedLocation);
}
void UOmegaMovementComponent::OnMantleFinished()
{
	OmegaCustomMovementMode = EOmegaCustomMovementMode::NONE;
	SetMovementMode(MOVE_Walking);
	OmegaCharacterOwner->GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	//OmegaController->EnableInput(OmegaController);
}
void UOmegaMovementComponent::UpdateCapsulePosition(float DeltaTime) const
{
	if (OmegaCustomMovementMode == EOmegaCustomMovementMode::Mantle)
	{
		OmegaCharacterOwner->GetCapsuleComponent()->SetWorldLocation(FMath::VInterpTo(OmegaCharacterOwner->GetCapsuleComponent()->GetComponentLocation(), MantleTargetLocation, DeltaTime, MantleAnimationSpeed));
	}
}





