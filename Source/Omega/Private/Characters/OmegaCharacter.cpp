#include "Characters/OmegaCharacter.h"

#include "AbilitySystemComponent.h"
#include "PaperZDAnimationComponent.h"
#include "PaperZDAnimInstance.h"
#include "AbilitySystem/OmegaAbilitySystemComponent.h"
#include "BlueprintLibraries/OmegaFunctionLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Components/OmegaMovementComponent.h"

AOmegaCharacter::AOmegaCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UOmegaMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

	PaperAnimation = CreateDefaultSubobject<UPaperZDAnimationComponent>("PaperZD Animation");

	OmegaMovementComponent = Cast<UOmegaMovementComponent>(GetCharacterMovement());

	OmegaMovementComponent->bConstrainToPlane = true;
	OmegaMovementComponent->SetPlaneConstraintAxisSetting(EPlaneConstraintAxisSetting::Y);
}

void AOmegaCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AOmegaCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (AbilitySystemComponent)
	{
		UOmegaFunctionLibrary::GiveStartupAbilities(this, AbilitySystemComponent);
		AddCharacterTags();
	}
}

// -------------------------------------
//  MOVEMENT
// -------------------------------------

UPawnMovementComponent* AOmegaCharacter::GetMovementComponent() const
{	
	return OmegaMovementComponent;
}
UOmegaMovementComponent* AOmegaCharacter::GetOmegaMovementComponent()
{
	if (!OmegaMovementComponent)
	{
		OmegaMovementComponent = Cast<UOmegaMovementComponent>(GetMovementComponent());
	}

	return OmegaMovementComponent;
}


// -------------------------------------
//  ABILITIES
// -------------------------------------

void AOmegaCharacter::InitAbilityActorInfo()
{
	// Modify initialized attributes depending on which tags character has.
	ModifyAttributesByTag();
}


//  Apply Attributes as Gameplay Effect
// ===============================================================================================================

void AOmegaCharacter::InitializeDefaultAttributes(const TSubclassOf<UGameplayEffect>& DefaultAttributesEffect, float Level) const
{
	if (!AbilitySystemComponent)
	{ UE_LOG(LogTemp, Error, TEXT("[%hs]: AbilitySystemComponent is null! Can't initialize initial attributes without it."),__FUNCTION__)	return;	}
	
	if (!DefaultAttributesEffect)
	{ UE_LOG(LogTemp, Error, TEXT("[%hs]: Can't initialize initial attributes cause it's empty! Check for player character default attributes properties."),__FUNCTION__)	return;	}
	
	FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	
	const FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributesEffect, Level, ContextHandle);
	AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data, AbilitySystemComponent);

	
}

void AOmegaCharacter::AddCharacterAbilities()
{
	UOmegaAbilitySystemComponent* OmegaASC = Cast<UOmegaAbilitySystemComponent>(AbilitySystemComponent);
	if (!OmegaASC) { UE_LOG(LogTemp, Error, TEXT("[%hs] OmegaAbilitySystem cast has failed! %s"), __FUNCTION__, *GetName()) }

	OmegaASC->AddCharacterAbilities(StartupAbilities);
}

void AOmegaCharacter::AddCharacterTags()
{
	if (CharacterTags.IsEmpty()) return;
	
	UOmegaAbilitySystemComponent* OmegaASC = Cast<UOmegaAbilitySystemComponent>(AbilitySystemComponent);
	if (!OmegaASC) { UE_LOG(LogTemp, Error, TEXT("[%hs] OmegaAbilitySystem cast has failed! %s"), __FUNCTION__, *GetName()) }

	OmegaASC->AddLooseGameplayTags(CharacterTags);
}

void AOmegaCharacter::ModifyAttributesByTag() const
{
	if (CharacterTags.IsEmpty() || !IsValid(AbilitySystemComponent)) return;
	UOmegaFunctionLibrary::ModifyAttributesByTag(this, CharacterTags, AbilitySystemComponent);	
}


//  COMBAT
// -------------------------------------


FVector AOmegaCharacter::GetProjectileSpawnSocket(bool& bSocketExist)
{
	if (!GetSprite()->DoesSocketExist(ProjectileSpawnSocket))
	{
		bSocketExist = false;
		return FVector();
	}
		
	bSocketExist = true;
	return GetSprite()->GetSocketTransform(ProjectileSpawnSocket).GetLocation();	
}

void AOmegaCharacter::Die_Implementation()
{
	
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	
	PaperAnimation->GetAnimInstance()->JumpToNode("Death");
	
	SetLifeSpan(PostDeathLifeSpan);
}

bool AOmegaCharacter::ProcessConsoleExec(const TCHAR* Cmd, FOutputDevice& Ar, UObject* Executor)
{
	if (OmegaMovementComponent && OmegaMovementComponent->ProcessConsoleExec(Cmd, Ar, Executor))
	{
		return true;
	}
	
	return Super::ProcessConsoleExec(Cmd, Ar, Executor);
}
