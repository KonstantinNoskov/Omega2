#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/Actor.h"
#include "OmegaProjectile.generated.h"


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

	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
private:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;
	
	UPROPERTY(Category = "Omega Projectile", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPaperFlipbookComponent> Sprite;

	UPROPERTY(Category = "Omega Projectile", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UNiagaraSystem> ImpactEffect;

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
