#include "Characters/PlayerCharacters/PlayerBaseCharacter.h"

#include "OmegaCollisionChannels.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/OmegaAbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/OmegaMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/OmegaPlayerController.h"
#include "Player/OmegaPlayerState.h"
#include "UI/HUD/OmegaHUD.h"


void APlayerBaseCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
}

APlayerBaseCharacter::APlayerBaseCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	// -------------------------------------
	//  CAMERA
	// -------------------------------------
	
	CharacterSpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	CharacterSpringArm->SetupAttachment(GetRootComponent());
	CharacterSpringArm->SetWorldRotation(FRotator(0.f,-90.f,0.f));
	CharacterSpringArm->TargetArmLength = 600.f;
	CharacterSpringArm->bInheritPitch = false;
	CharacterSpringArm->bInheritYaw = false;
	CharacterSpringArm->bInheritRoll = false;
	
	CharacterSpringArm->bEnableCameraLag = true;

	CharacterCamera = CreateDefaultSubobject<UCameraComponent>("Camera");
	CharacterCamera->SetupAttachment(CharacterSpringArm);


	// -------------------------------------
	//  COLLISION CHANNELS
	// -------------------------------------

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetCapsuleComponent()->SetCollisionObjectType(ECC_Player);
	
}

void APlayerBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	InitialCameraDistance = CharacterSpringArm->TargetArmLength;
}

void APlayerBaseCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	HandleCameraBehavior(DeltaSeconds);
}

void APlayerBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	InitAbilityActorInfo();

	AddCharacterAbilities();
	
	if (OmegaMovementComponent)
	{
		OmegaMovementComponent->BindDependencies(NewController);
	}
}

int32 APlayerBaseCharacter::GetPlayerLevel() const
{
	const AOmegaPlayerState* OmegaPlayerState = GetPlayerState<AOmegaPlayerState>();
	if (!OmegaPlayerState)
		{ UE_LOG(LogTemp, Error, TEXT("[%hs]: Can't get player level. PlayerState is null!"),__FUNCTION__)	return 0;	}

	return OmegaPlayerState->GetPlayerLevel();
}

void APlayerBaseCharacter::InitAbilityActorInfo()
{
	// Init ability actor info with player state valid check
	AOmegaPlayerState* OmegaPlayerState = GetPlayerState<AOmegaPlayerState>();
	if (!OmegaPlayerState)	{ UE_LOG(LogTemp, Error, TEXT("[%hs]: OmegaPlayerState for PlayerBaseCharacter is null!"),__FUNCTION__)		return;	}
	
	OmegaPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(OmegaPlayerState, this);

	// Inform Ability system that all essential data is set and it's time to bind callbacks to ability system delegates (OnGameplayEffectApplied, etc.)
	UOmegaAbilitySystemComponent* OmegaASC = Cast<UOmegaAbilitySystemComponent>(OmegaPlayerState->GetAbilitySystemComponent());
	if (!OmegaASC)	{ UE_LOG(LogTemp, Error, TEXT("[%hs]: Cast from UAbiilitySystem to UOmegaAbilitySystem is failed!"),__FUNCTION__)	return;	}
	
	OmegaASC->OnAbilityActorInfoSet();
	
	// Assign Player's Ability system & Attribute Set
	AbilitySystemComponent = OmegaPlayerState->GetAbilitySystemComponent();
	AttributeSet = OmegaPlayerState->GetAttributeSet();

	// Set player's default primary attributes 
	InitializeDefaultAttributes(DefaultPrimaryAttributes, 1.f);
	InitializeDefaultAttributes(DefaultSecondaryAttributes, 1.f);
	InitializeDefaultAttributes(DefaultTertiaryAttributes, 1.f);

	if (AOmegaPlayerController* OmegaPlayerController = Cast<AOmegaPlayerController>(GetController()))
	{
		if (AOmegaHUD* OmegaHUD = Cast<AOmegaHUD>(OmegaPlayerController->GetHUD()))
		{
			OmegaHUD->InitOverlay(OmegaPlayerController, OmegaPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
}

void APlayerBaseCharacter::HandleCameraBehavior(const float DeltaTime) const
{
	const float CurrentCameraDistance = CharacterSpringArm->TargetArmLength;
	const float CurrentVelocity = GetCharacterMovement()->GetLastUpdateVelocity().Length();
	const float TargetCameraDistance = CurrentCameraDistance * (CurrentVelocity / 100);

	const float InterpCameraDistance = FMath::FInterpTo(CurrentCameraDistance, TargetCameraDistance, DeltaTime, CameraDistanceUpdateSpeed);
	const float ClampCameraDistance = FMath::Clamp(InterpCameraDistance, InitialCameraDistance, MaxCameraDistance);
	
	CharacterSpringArm->TargetArmLength = ClampCameraDistance;
}



