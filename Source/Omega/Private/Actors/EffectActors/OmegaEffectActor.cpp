#include "Actors/EffectActors/OmegaEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "OmegaAbilityTypes.h"
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

	DurationPolicyToDamage.Add(InstantEffectApplicationPolicy, InstantDamage);
	DurationPolicyToDamage.Add(DurationEffectApplicationPolicy, DurationDamage);
	DurationPolicyToDamage.Add(InfiniteEffectApplicationPolicy, InfiniteDamage);
	
}

void AOmegaEffectActor::ApplyEffectToTarget(AActor* TargetActor, const TSubclassOf<UGameplayEffect>& InGameplayEffectClass, const EEffectApplicationPolicy& ApplyPolicy)
{
	// Gameplay effect valid check
	checkf(InGameplayEffectClass, TEXT("[%hs]: GameplayEffect is null! Set GameplayEffect in Effect Actor's defaults."), __FUNCTION__)

	UOmegaAbilitySystemComponent* OmegaASC = Cast<UOmegaAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor));
	if (!IsValid(OmegaASC)) return;
	
	// Creating EffectContextHandle 
	FGameplayEffectContextHandle EffectContextHandle = OmegaASC->MakeEffectContext();
	FOmegaGameplayEffectContext* OmegaEffectContext = static_cast<FOmegaGameplayEffectContext*>(EffectContextHandle.Get());
	OmegaEffectContext->AddSourceObject(this);

	TMap<FGameplayTag, FScalableFloat> DamageTypeMapToChooseFrom = DurationPolicyToDamage[ApplyPolicy];
	
	// Creating EffectSpecHandle based on EffectContextHandle
	const FGameplayEffectSpecHandle EffectSpecHandle = OmegaASC->MakeOutgoingSpec(InGameplayEffectClass, ActorLevel, EffectContextHandle);
	for (TTuple<FGameplayTag, FScalableFloat> Pair : DamageTypeMapToChooseFrom)
	{
		if (!Pair.Value.IsValid()) return;
	
		OmegaEffectContext->AddDamageType(Pair.Key);

		const FRealCurve* DamageCurve = Pair.Value.Curve.CurveTable->FindCurve("Fire_OnFire", "");
		
		const FGameplayTag DamageTypeTag = Pair.Key;
		float ScaledDamage = Pair.Value.GetValueAtLevel(EffectLevel);
		
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(EffectSpecHandle, DamageTypeTag, ScaledDamage);
	}
	
	// Making Target ability system apply effect to itself and store it.
	const FActiveGameplayEffectHandle ActiveGameplayEffectHandle = OmegaASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data);
}

void AOmegaEffectActor::OnOverlap(AActor* TargetActor)
{
	// Apply logic on overlap
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)		{	ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass, InstantEffectApplicationPolicy);	}
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)	{	ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass, DurationEffectApplicationPolicy);	}
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)	{	ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass, InfiniteEffectApplicationPolicy);	}

	// Handle Effect Removal 
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (!TargetASC) return; 
	
	// Duration
	if (DurationEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnOverlap && DurationGameplayEffectClass) { TargetASC->RemoveActiveGameplayEffectBySourceEffect(DurationGameplayEffectClass, TargetASC); }
}

void AOmegaEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)	{	ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass, InstantEffectApplicationPolicy);	}
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)	{	ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass, DurationEffectApplicationPolicy);	}
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)	{	ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass, InfiniteEffectApplicationPolicy);	}
	
	// Removal logic
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (!TargetASC) return; 
	
	// Infinite
	if (InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap && InfiniteGameplayEffectClass)	{ TargetASC->RemoveActiveGameplayEffectBySourceEffect(InfiniteGameplayEffectClass, TargetASC); }
}


