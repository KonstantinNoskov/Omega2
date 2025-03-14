#pragma once

#include "CoreMinimal.h"
#include "Characters/OmegaCharacter.h"
#include "Interfaces/PlayerInterface.h"
#include "PlayerBaseCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class OMEGA_API APlayerBaseCharacter : public AOmegaCharacter, public IPlayerInterface
{
	GENERATED_BODY()

public:
	virtual void Landed(const FHitResult& Hit) override;

	APlayerBaseCharacter(const FObjectInitializer& ObjectInitializer);
	virtual void Tick(float DeltaSeconds) override;
	virtual void PossessedBy(AController* NewController) override;

protected:

	virtual void BeginPlay() override;

#pragma region CAMERA
	
protected:

	/**
	 *	Handles player camera behavior during gameplay
	 * 
	 *	@param DeltaTime - Delta time
	 */
	void HandleCameraBehavior(const float DeltaTime) const;
	

public:

	FORCEINLINE USpringArmComponent* GetSpringArm() const { return CharacterSpringArm; }
	FORCEINLINE UCameraComponent* GetCamera() const { return CharacterCamera; }

private:

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CharacterSpringArm;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> CharacterCamera;
	
	float InitialCameraDistance;


#pragma region COMBAT INTERFACE

public:
		
	virtual int32 GetPlayerLevel() const override;

#pragma endregion


protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "OmegaSpringArm")
	float MaxCameraDistance = 1000.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "OmegaSpringArm")
	float CameraDistanceUpdateSpeed = 1.f;

#pragma endregion

	virtual void InitAbilityActorInfo() override;
};
