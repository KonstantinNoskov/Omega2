#include "Actors/EffectActors/OmegaEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/OmegaAbilitySystemComponent.h"
#include "Components/SphereComponent.h"

AOmegaEffectActor::AOmegaEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	
	SetRootComponent(CreateDefaultSubobject<USphereComponent>("Scene Root"));
	
}

void AOmegaEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
	
}

void AOmegaEffectActor::ApplyEffectToTarget(AActor* TargetActor, const TSubclassOf<UGameplayEffect>& InGameplayEffectClass)
{
	// Gameplay effect valid check
	checkf(InGameplayEffectClass, TEXT("[%hs]: GameplayEffect is null! Set GameplayEffect in Effect Actor's defaults."), __FUNCTION__)

	UOmegaAbilitySystemComponent* OmegaASC = Cast<UOmegaAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor));
	if (!IsValid(OmegaASC)) return;
	
	// Creating EffectContextHandle 
	FGameplayEffectContextHandle EffectContextHandle = OmegaASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	
	// Creating EffectSpecHandle based on EffectContextHandle
	const FGameplayEffectSpecHandle EffectSpecHandle = OmegaASC->MakeOutgoingSpec(InGameplayEffectClass, ActorLevel, EffectContextHandle);
	
	// Making Target ability system apply effect to itself and store it.
	const FActiveGameplayEffectHandle ActiveGameplayEffectHandle = OmegaASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data);
}

void AOmegaEffectActor::OnOverlap(AActor* TargetActor)
{
	// Apply logic on overlap
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)		{	ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);	}
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)	{	ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);	}
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)	{	ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);	}
	
	// Handle Effect Removal 
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (!TargetASC) return; 
	
	// Duration
	if (DurationEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnOverlap && DurationGameplayEffectClass) { TargetASC->RemoveActiveGameplayEffectBySourceEffect(DurationGameplayEffectClass, TargetASC); }
}

void AOmegaEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)	{	ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);	}
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)	{	ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);	}
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)	{	ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);	}
	
	// Removal logic
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (!TargetASC) return; 
	
	// Infinite
	if (InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap && InfiniteGameplayEffectClass)	{ TargetASC->RemoveActiveGameplayEffectBySourceEffect(InfiniteGameplayEffectClass, TargetASC); }
}


