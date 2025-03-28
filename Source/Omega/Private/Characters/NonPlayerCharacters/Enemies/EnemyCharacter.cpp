#include "Characters/NonPlayerCharacters/Enemies/EnemyCharacter.h"

#include "OmegaCollisionChannels.h"
#include "OmegaGameplayTags.h"
#include "AbilitySystem/OmegaAbilitySystemComponent.h"
#include "AbilitySystem/OmegaAttributeSet.h"
#include "AI/OmegaAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/OmegaMovementComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UI/Widgets/OmegaUserWidget.h"


// -------------------------------------
//  CONSTRUCTOR
// -------------------------------------

AEnemyCharacter::AEnemyCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
	PrimaryActorTick.bCanEverTick = false;

	// GAS
	AbilitySystemComponent = CreateDefaultSubobject<UOmegaAbilitySystemComponent>("Omega Ability System");
	AttributeSet = CreateDefaultSubobject<UOmegaAttributeSet>("Omega Attribute Set");
	
	// CAPSULE
	GetCapsuleComponent()->SetCapsuleHalfHeight(80.f);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetCapsuleComponent()->SetCollisionObjectType(ECC_Enemy);

	// HEALTH BAR
	HealthBar = CreateDefaultSubobject<UWidgetComponent>("Health Bar");
	HealthBar->SetupAttachment(GetRootComponent());
}

void AEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	OmegaAIController = Cast<AOmegaAIController>(NewController);
	if (OmegaAIController)
	{
		OmegaAIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
		OmegaAIController->RunBehaviorTree(BehaviorTree);	
	}
	
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityActorInfo();

	if (UOmegaUserWidget* OmegaUserWidget = Cast<UOmegaUserWidget>(HealthBar->GetUserWidgetObject()))
	{
		OmegaUserWidget->SetWidgetController(this);
	}
	
	
	BindCallbacks();
}

// -------------------------------------
//  SETUP
// -------------------------------------

void AEnemyCharacter::BindCallbacks()
{
	if (const UOmegaAttributeSet* OmegaAS = Cast<UOmegaAttributeSet>(AttributeSet))
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(OmegaAS->GetHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
		{	
			OnHealthChanged.Broadcast(Data.NewValue);
		});

		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(OmegaAS->GetMaxHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
		{	
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		});


		const FOmegaGameplayTags GameplayTags = FOmegaGameplayTags::Get();
		FOnGameplayEffectTagCountChanged TagCountChangedDelegate = AbilitySystemComponent->RegisterGameplayTagEvent(GameplayTags.Effects_HitReact, EGameplayTagEventType::NewOrRemoved); 
		TagCountChangedDelegate.AddUObject(this, &AEnemyCharacter::HitReactTagChanged);

		// Broadcast initial attribute values
		OnHealthChanged.Broadcast(OmegaAS->GetHealth());
		OnMaxHealthChanged.Broadcast(OmegaAS->GetMaxHealth());
		
	}
}

// -------------------------------------
//  ENEMY INTERFACE
// -------------------------------------

void AEnemyCharacter::SetCombatTarget_Implementation(AActor* TargetActor)
{
	if (!OmegaAIController)
	{
		UE_LOG(LogTemp, Error, TEXT("[%hs] OmegaAIController is null!"), __FUNCTION__)
		return;
	}
	
	UBlackboardComponent* Blackboard = OmegaAIController->GetBlackboardComponent();
	Blackboard->SetValueAsObject(CombatTargetName, TargetActor);
	
}

void AEnemyCharacter::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	UOmegaAbilitySystemComponent* OmegaASC = Cast<UOmegaAbilitySystemComponent>(AbilitySystemComponent);
	if (OmegaASC)
	{
		OmegaASC->OnAbilityActorInfoSet();

		InitializeDefaultAttributes(DefaultPrimaryAttributes, 1.f);
		InitializeDefaultAttributes(DefaultSecondaryAttributes, 1.f);
		InitializeDefaultAttributes(DefaultTertiaryAttributes, 1.f);
	}
}

void AEnemyCharacter::HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewTagCount)
{
	bHitReacting = NewTagCount > 0;
	GetCharacterMovement()->MaxWalkSpeed = bHitReacting ? 0.f : GetOmegaMovementComponent()->GetBaseWalkSpeed();
}





