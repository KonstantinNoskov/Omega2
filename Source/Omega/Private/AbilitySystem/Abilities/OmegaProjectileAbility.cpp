 #include "AbilitySystem/Abilities/OmegaProjectileAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "OmegaAbilityTypes.h"
#include "OmegaGameplayTags.h"
#include "Actors/OmegaProjectile.h"
#include "Interfaces/CombatInterface.h"


void UOmegaProjectileAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	FVector ProjectileSocketLocation;
	bool bSpawnSocketExist = false;
	if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo()))
	{
		//ProjectileSocketLocation = CombatInterface->GetProjectileSpawnSocket(bSpawnSocketExist);
		ProjectileSocketLocation = CombatInterface->Execute_GetCombatSocketLocation(GetAvatarActorFromActorInfo(), bSpawnSocketExist);
	}

	if (!bSpawnSocketExist) return;
	
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(ProjectileSocketLocation);
	SpawnTransform.SetRotation(FRotator(0.f,GetAvatarActorFromActorInfo()->GetActorRotation().Yaw, 0.f).Quaternion());
	
	// Create and define projectile
	AOmegaProjectile* Projectile = GetWorld()->SpawnActorDeferred<AOmegaProjectile>(
		ProjectileClass,
		SpawnTransform,
		GetOwningActorFromActorInfo(),
		Cast<APawn>(GetAvatarActorFromActorInfo()),
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn
		);

	if (!IsValid(Projectile))
	{
		UE_LOG(LogTemp, Error, TEXT("[%hs] Spawned projectile is null! Probably the projectile class in %s is not set."), __FUNCTION__, *this->GetName())
		return;
	}
	
	// Assign damage effect spec handle to the projectile
	const UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());

	// Set Effect Context
	FGameplayEffectContextHandle EffectContextHandle = SourceASC->MakeEffectContext();
	FOmegaGameplayEffectContext* OmegaEffectContext = static_cast<FOmegaGameplayEffectContext*>(EffectContextHandle.Get());
	
	OmegaEffectContext->SetAbility(this);
	OmegaEffectContext->AddSourceObject(Projectile);

	for (auto DamageType : DamageTypes)
	{
		OmegaEffectContext->AddDamageType(DamageType.Key);
	}
	
	// Set Projectile Effect spec 
	const FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), EffectContextHandle);
	
	// Get GameplayTags
	const FOmegaGameplayTags GameplayTags = FOmegaGameplayTags::Get();

	// Damage depends on ability level
	for (auto& Pair : DamageTypes)
	{
		const float ScaledDamage = Pair.Value.GetValueAtLevel(GetAbilityLevel());
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, Pair.Key, ScaledDamage);
	}
	
	Projectile->DamageEffectSpecHandle = SpecHandle;
	
	// Finish spawning
	Projectile->FinishSpawning(SpawnTransform);
}
