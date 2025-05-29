#include "Actors/OmegaProjectile.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "OmegaAbilityTypes.h"
#include "OmegaCollisionChannels.h"
#include "PaperFlipbookComponent.h"
#include "Actors/PaperEffectActor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

AOmegaProjectile::AOmegaProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	SetRootComponent(Sphere);

#pragma region SPHERE COLLISION
	
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	Sphere->SetCollisionObjectType(ECC_Projectile);
	Sphere->SetCollisionResponseToChannel(ECC_Enemy, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_Player, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);

#pragma endregion

	Sprite = CreateDefaultSubobject<UPaperFlipbookComponent>("Sprite");
	Sprite->SetupAttachment(GetRootComponent());
	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile Movement");
	ProjectileMovement->InitialSpeed = 550.f;
	ProjectileMovement->MaxSpeed = 550.f;
	ProjectileMovement->ProjectileGravityScale = 0.f;
}

void AOmegaProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AOmegaProjectile::OnSphereOverlap);

	UGameplayStatics::PlaySoundAtLocation(this, SpawnSound, GetActorLocation(), FRotator::ZeroRotator);
}



void AOmegaProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                       const FHitResult& SweepResult)
{
	// Check for instigator. Projectile SHOULD NOT collide with it's instigator 
	if (OtherActor == GetInstigator()) return;

	// Play impact sound
	UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(), FRotator::ZeroRotator);

	// Spawn paper impact effect
	SpawnImpactEffect();
	
	// Apply damage 
	if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
	{
		if (DamageEffectSpecHandle.IsValid())
		{
			TargetASC->ApplyGameplayEffectSpecToSelf(*DamageEffectSpecHandle.Data);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("[%hs] Projectile ability doesn't have a damage effect. Check for omega projectile ability damage effect class. "), __FUNCTION__);
		}
	}
	Destroy();
}

void AOmegaProjectile::SpawnImpactEffect()
{
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(GetActorLocation());
	SpawnTransform.SetRotation(GetActorRotation().Quaternion());
	
	// Effect class Valid check
	if (!ImpactEffectClass) return;

	// Create and define Impact Effect
	APaperEffectActor* ImpactEffect = GetWorld()->SpawnActorDeferred<APaperEffectActor>(
		ImpactEffectClass,
		SpawnTransform,
		this,
		nullptr,
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn
	);

	if (ImpactEffect)
	{
		ImpactEffect->GetRenderComponent()->SetFlipbook(ImpactSpriteEffect);

		// Finish spawning
		ImpactEffect->FinishSpawning(SpawnTransform);
	}
}


