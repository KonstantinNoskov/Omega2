#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/Actor.h"
#include "OmegaProjectile.generated.h"


class APaperEffectActor;
class APaperFlipbookActor;
class UPaperFlipbook;
class UNiagaraSystem;
class UPaperFlipbookComponent;
class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class OMEGA_API AOmegaProjectile : public AActor
{
	GENERATED_BODY()

public:
	AOmegaProjectile();

protected:
	
	virtual void BeginPlay() override;
	void SpawnImpactEffect();

	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
private:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;
	
	UPROPERTY(Category = "Omega Projectile", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPaperFlipbookComponent> Sprite;

	UPROPERTY(Category = "Omega Projectile", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPaperFlipbook> ImpactSpriteEffect;
	
	UPROPERTY(Category = "Omega Projectile", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<APaperEffectActor> ImpactEffectClass;

	UPROPERTY(Category = "Omega Projectile", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USoundBase> SpawnSound;

	UPROPERTY(Category = "Omega Projectile", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USoundBase> ImpactSound;

	UPROPERTY(Category = "Omega Projectile", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USoundBase> MovementSound;

public:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;
	
	FGameplayEffectSpecHandle DamageEffectSpecHandle;
};
