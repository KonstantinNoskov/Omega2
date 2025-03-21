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

	BaseWalkSpeed = MaxWalkSpeed;
	BaseGroundFriction = GroundFriction;
}

void UOmegaMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	InitialWalkDeceleration = BrakingDecelerationWalking;
}

void UOmegaMovementComponent::BindDependencies(AController* OwningController)
{
	OmegaOwner = Cast<AOmegaCharacter>(GetOwner());
	OmegaController = Cast<AOmegaPlayerController>(OwningController);
	
	if (OmegaOwner)
	{
		OmegaOwner->GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &UOmegaMovementComponent::HandleMantle);
	}
	else { UE_LOG(LogTemp, Error, TEXT("[%hs]: OmegaOwner is null!"),__FUNCTION__);	}
	
}

void UOmegaMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateCapsulePosition(DeltaTime);
}

void UOmegaMovementComponent::UpdateCapsulePosition(float DeltaTime) const
{
	if (OmegaCustomMovementMode == EOmegaCustomMovementMode::Mantle)
	{
		OmegaOwner->GetCapsuleComponent()->SetWorldLocation(FMath::VInterpTo(OmegaOwner->GetCapsuleComponent()->GetComponentLocation(), MantleTargetLocation, DeltaTime, MantleAnimationSpeed));
	}
}

#pragma region JUMP

void UOmegaMovementComponent::PerformJump(const FInputActionValue& InputActionValue) const
{
	const float InputBool = InputActionValue.Get<bool>();
	
	if (OmegaOwner)
	{	
		if (InputBool && IsValidJump())
		{
			OmegaOwner->Jump();
		}
	}
}

bool UOmegaMovementComponent::IsValidJump() const 
{
	const bool bNotValid = !OmegaOwner || IsCrouching();

	if(bNotValid) return false;
	
	FHitResult HitResult;
	const UWorld* World = GetWorld();
	const float CapsuleHalfHeight = OmegaOwner->GetCapsuleComponent()->GetScaledCapsuleHalfHeight() * .5f;
	const FVector TraceStart = OmegaOwner->GetCapsuleComponent()->GetComponentLocation() + FVector(0.f,0.,CapsuleHalfHeight) * 2;
	const FVector TraceEnd = TraceStart + FVector(0.f,0.f, 10.f);
	const float CapsuleRadius = OmegaOwner->GetCapsuleComponent()->GetScaledCapsuleRadius();
	
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

#pragma endregion

#pragma region CROUCH

void UOmegaMovementComponent::PerformCrouch(const FInputActionValue& InputActionValue)
{
	const bool InputBool = InputActionValue.Get<bool>();
	
	if (OmegaOwner)
	{
		if (InputBool && !IsFalling() && OmegaCustomMovementMode != EOmegaCustomMovementMode::Dash)
		{	
			OmegaOwner->Crouch();
		}
		else
		{
			OmegaOwner->UnCrouch();
		}
	}
}

#pragma endregion

#pragma region DASH

void UOmegaMovementComponent::HandleDash(const FInputActionValue& InputActionValue)
{
	if (IsValidDash() && OmegaOwner)
	{
		PerformDash();
	}
}

bool UOmegaMovementComponent::IsValidDash()
{
	const float CurrentTime = GetWorld()->GetTimeSeconds();
	
	bDashValid = CurrentTime - DashStarTime >= DashCooldown || bFirstDash; 
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
	
	const FVector DashDirection = (Acceleration.IsNearlyZero() ? OmegaOwner->GetActorForwardVector() : Acceleration).GetSafeNormal2D();
	
	Velocity = DashImpulse * DashDirection;
	
	const FQuat NewRotation = FRotationMatrix::MakeFromXZ(DashDirection, FVector::UpVector).ToQuat();
	
	FHitResult HitResult;
	SafeMoveUpdatedComponent(FVector::ZeroVector, NewRotation, false, HitResult);

	OmegaOwner->GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Enemy, ECR_Ignore);
	
}
void UOmegaMovementComponent::OnDashFinished()
{
	OmegaCustomMovementMode = EOmegaCustomMovementMode::None;
	
	OmegaOwner->GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Enemy, ECR_Overlap);
	BrakingDecelerationWalking = InitialWalkDeceleration;
	GroundFriction = BaseGroundFriction;
}



#pragma endregion

#pragma region MANTLE

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
		
		FHitResult HitResult = InHitResult; 
		const FVector ForwardVector = OmegaOwner->GetActorForwardVector();
		const float OwnerCapsuleHeight = OmegaOwner->GetCapsuleComponent()->GetScaledCapsuleHalfHeight() * 2.f;
		const float OwnerCapsuleRadius = OmegaOwner->GetCapsuleComponent()->GetScaledCapsuleRadius();
		const FVector HitPoint = HitResult.ImpactPoint;
		const FVector MantleHeightDistance = HitPoint + FVector(0.f,0.f,GrabHeight);
		const FVector Adjust_X = MantleHeightDistance + ForwardVector * FVector(OwnerCapsuleRadius, 0.f,0.f);
		const FVector ClimbTargetPoint = Adjust_X + FVector(0.f,0.f,-OwnerCapsuleHeight - 1.f) ;
		
		// HitPoint --> Up 
		UKismetSystemLibrary::LineTraceSingle(GetWorld(), HitPoint, MantleHeightDistance, TraceTypeQuery1, false, TArray<AActor*>(), bMantleDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None, HitResult, true);

		// Up --> Just a bit towards to actor direction
		UKismetSystemLibrary::LineTraceSingle(GetWorld(), MantleHeightDistance, Adjust_X, TraceTypeQuery1, false, TArray<AActor*>(), bMantleDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None, HitResult, true);
		if (HitResult.bBlockingHit)
		{
			return false;	
		} 
		
		//  All the way down to check if there's a ground to mantle to
		UKismetSystemLibrary::LineTraceSingle(GetWorld(), Adjust_X, ClimbTargetPoint, TraceTypeQuery1, false, TArray<AActor*>(), bMantleDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None, HitResult, true);
		if (!HitResult.bBlockingHit) return false;

		const float ObstacleHeight = (HitPoint - HitResult.ImpactPoint).Z;
		if (ObstacleHeight > GrabHeight) return false;
		
		MantleTargetLocation = HitResult.ImpactPoint + FVector(0.f,0.f, OmegaOwner->GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
		UKismetSystemLibrary::CapsuleTraceSingle(
			GetWorld(),
			MantleTargetLocation,
			MantleTargetLocation,
			OmegaOwner->GetCapsuleComponent()->GetScaledCapsuleRadius(),
			OmegaOwner->GetCapsuleComponent()->GetScaledCapsuleHalfHeight() - 1.f,
			TraceTypeQuery1,
			false,
			TArray<AActor*>(),
			bMantleDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None,
			HitResult,
			true
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
	OmegaOwner->GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Ignore);

	OmegaOwner->SetActorLocation(MantleTargetPoint - FVector(OmegaOwner->GetCapsuleComponent()->GetScaledCapsuleRadius() * OmegaOwner->GetActorForwardVector().X,0.f,OmegaOwner->GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));
}

void UOmegaMovementComponent::OnMantleFinished()
{
	OmegaCustomMovementMode = EOmegaCustomMovementMode::None;
	SetMovementMode(MOVE_Walking);
	OmegaOwner->GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	OmegaController->EnableInput(OmegaController);
}



#pragma endregion





