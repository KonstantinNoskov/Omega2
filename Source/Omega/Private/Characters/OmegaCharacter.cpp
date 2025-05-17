#include "Characters/OmegaCharacter.h"

#include "AbilitySystemComponent.h"
#include "OmegaGameplayTags.h"
#include "PaperFlipbook.h"
#include "PaperZDAnimationComponent.h"
#include "PaperZDAnimInstance.h"
#include "AbilitySystem/OmegaAbilitySystemComponent.h"
#include "BlueprintLibraries/OmegaFunctionLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Components/OmegaMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"

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
	if (CharacterTypeTags.IsEmpty()) return;
	
	UOmegaAbilitySystemComponent* OmegaASC = Cast<UOmegaAbilitySystemComponent>(AbilitySystemComponent);
	if (!OmegaASC) { UE_LOG(LogTemp, Error, TEXT("[%hs] OmegaAbilitySystem cast has failed! %s"), __FUNCTION__, *GetName()) }

	OmegaASC->AddLooseGameplayTags(CharacterTypeTags);
}

void AOmegaCharacter::ModifyAttributesByTag() const
{
	if (CharacterTypeTags.IsEmpty() || !IsValid(AbilitySystemComponent)) return;
	UOmegaFunctionLibrary::ModifyAttributesByTag(this, CharacterTypeTags, AbilitySystemComponent);	
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


void AOmegaCharacter::Attack_Implementation()
{	
	// Local Variables
	FOmegaGameplayTags GameplayTags = FOmegaGameplayTags::Get();

	// Get Attack Animation
	UPaperZDAnimSequence* AnimationToPlay = GetAttackAnimation_Implementation();

	// Start a combo if attack ability was activated during combo window
	if (AbilitySystemComponent->HasMatchingGameplayTag(GameplayTags.Combat_Attack_Combo_WindowOpened))
	{
		AbilitySystemComponent->SetLooseGameplayTagCount(GameplayTags.Combat_Attack_Combo_Activated, 1);
	}

	// Prevent attack animation from double launch
	if (!AbilitySystemComponent->HasMatchingGameplayTag(GameplayTags.Combat_Attack))
	{
		if (!IsValid(AnimationToPlay)) return;
		PaperAnimation->GetAnimInstance()->PlayAnimationOverride(AnimationToPlay);
	}
	
	// Add Attack Tag
	AbilitySystemComponent->SetLooseGameplayTagCount(GameplayTags.Combat_Attack, 1);
}

UPaperZDAnimSequence* AOmegaCharacter::GetAttackAnimation_Implementation()
{
	bool bAttackValid = PaperAnimation->GetAnimInstance() && AbilitySystemComponent && OmegaMovementComponent; 
	if (!bAttackValid) return nullptr;
	
	FOmegaGameplayTags GameplayTags = FOmegaGameplayTags::Get();
	
	// Defines what set of animations we choose from
	TArray<TObjectPtr<UPaperZDAnimSequence>> AnimationsArray = OmegaMovementComponent->MovementStateTags.HasTagExact(GameplayTags.Movement_State_Falling) ? AirAttackAnimations : AttackAnimations;
	
	// Animation Index depends on amount of combo stacks
	int AnimIndex = AbilitySystemComponent->GetTagCount(GameplayTags.Combat_Attack_Combo_Count);

	// Reset animation index if we out of combo animations 
	if (AnimIndex > AnimationsArray.Num() - 1) { AnimIndex = 0; }
	
	return AnimationsArray[AnimIndex];
}
void AOmegaCharacter::OnAttackFinished_Implementation()
{
	TArray<TObjectPtr<UPaperZDAnimSequence>> AnimationsToPlay = OmegaMovementComponent->MovementStateTags.HasTagExact(FOmegaGameplayTags::Get().Movement_State_Falling) ? AirAttackAnimations : AttackAnimations;
	if (!AbilitySystemComponent) return;
	FOmegaGameplayTags GameplayTags = FOmegaGameplayTags::Get();
	
	if (AbilitySystemComponent->HasMatchingGameplayTag(GameplayTags.Combat_Attack_Combo_Activated)) 
	{
		UPaperZDAnimInstance* AnimInstance = Execute_GetAnimationInstance(this);
		if (!AnimInstance) return;
		if (AnimationsToPlay.IsEmpty()) return;
		
		AbilitySystemComponent->AddLooseGameplayTag(GameplayTags.Combat_Attack_Combo_Count);
		int AnimIndex = AbilitySystemComponent->GetTagCount(GameplayTags.Combat_Attack_Combo_Count);
		if (AnimIndex > AnimationsToPlay.Num() - 1)
		{
			ResetAttack_Implementation();
			return;
		}
		
		AnimInstance->PlayAnimationOverride(AnimationsToPlay[AnimIndex]);
		AbilitySystemComponent->SetLooseGameplayTagCount(FOmegaGameplayTags::Get().Combat_Attack_Combo_Activated, 0);
	}
	else
	{
		ResetAttack_Implementation();
	}
}
void AOmegaCharacter::ResetAttack_Implementation()
{
	AbilitySystemComponent->SetLooseGameplayTagCount(FOmegaGameplayTags::Get().Combat_Attack_Combo_Activated, 0);
	AbilitySystemComponent->SetLooseGameplayTagCount(FOmegaGameplayTags::Get().Combat_Attack, 0);
	AbilitySystemComponent->SetLooseGameplayTagCount(FOmegaGameplayTags::Get().Combat_Attack_Combo_Count, 0);
}

FVector AOmegaCharacter::GetCombatSocketLocation_Implementation() const
{
	if (!GetSprite()) return FVector();
	return GetSprite()->GetSocketLocation("SKT_CombatSocket");
}
void AOmegaCharacter::SetIsAttackWindowOpened_Implementation(const FGameplayTag& ComboWindowOpenedTag)
{
	if (!AbilitySystemComponent) return;
	if (ComboWindowOpenedTag == FGameplayTag::EmptyTag)
	{
		AbilitySystemComponent->RemoveLooseGameplayTag(FOmegaGameplayTags::Get().Combat_Attack_Combo_WindowOpened);
		return;
	}
	
	AbilitySystemComponent->AddLooseGameplayTag(ComboWindowOpenedTag);
}
void AOmegaCharacter::Die_Implementation()
{
	
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	
	PaperAnimation->GetAnimInstance()->JumpToNode("Death");
	
	SetLifeSpan(PostDeathLifeSpan);
}

bool AOmegaCharacter::IsDead_Implementation() const
{
	return ICombatInterface::IsDead_Implementation();
}

bool AOmegaCharacter::ProcessConsoleExec(const TCHAR* Cmd, FOutputDevice& Ar, UObject* Executor)
{
	if (OmegaMovementComponent && OmegaMovementComponent->ProcessConsoleExec(Cmd, Ar, Executor))
	{
		return true;
	}
	
	return Super::ProcessConsoleExec(Cmd, Ar, Executor);
}
