#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "PaperCharacter.h"
#include "PaperFlipbookComponent.h"
#include "PaperZDAnimationComponent.h"
#include "PaperZDAnimInstance.h"
#include "Interfaces/CombatInterface.h"

#include "OmegaCharacter.generated.h"

class UDamageTextComponent;
class UPaperZDAnimSequence;
class UGameplayAbility;
class UOmegaMovementComponent;
class UGameplayEffect;
class UAttributeSet;
class UAbilitySystemComponent;
class UPaperZDAnimationComponent;

UCLASS(BlueprintType)
class OMEGA_API AOmegaCharacter : public APaperCharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:

	AOmegaCharacter(const FObjectInitializer& ObjectInitializer);

protected:

	virtual void BeginPlay() override;

public:
	
	virtual void PossessedBy(AController* NewController) override;

	FORCEINLINE virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override		{ return AbilitySystemComponent; }
	FORCEINLINE UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	
	// -------------------------------------
	//  MOVEMENT
	// -------------------------------------
	
public:
	
	virtual UPawnMovementComponent* GetMovementComponent() const override;

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Omega Movement")
	TObjectPtr<UOmegaMovementComponent> OmegaMovementComponent;

public:

	UFUNCTION(BlueprintPure, Category = "Omega|Movement")
	UOmegaMovementComponent* GetOmegaMovementComponent();	

protected:
	
	/**
	 * Assign owner & avatar actor to Ability system 
	 */
	virtual void InitAbilityActorInfo();

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PaperZD", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPaperZDAnimationComponent> PaperAnimation;


	//  ABILITY SYSTEM
	// ===============================================================================================================

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

public:
	
	virtual bool ProcessConsoleExec(const TCHAR* Cmd, FOutputDevice& Ar, UObject* Executor) override;


	//  ATTRIBUTE SET
	// ===============================================================================================================

protected:
	
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
	
	void InitializeDefaultAttributes(const TSubclassOf<UGameplayEffect>& DefaultAttributesEffect, float Level) const;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Default Attributes", DisplayName = "Primary Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Default Attributes", DisplayName = "Secondary Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Default Attributes", DisplayName = "Tertiary Attributes")
	TSubclassOf<UGameplayEffect> DefaultTertiaryAttributes;

	
	// -------------------------------------
	//  ABILITIES
	// -------------------------------------

protected:

	void AddCharacterAbilities();

public:
	
	
	virtual FVector GetProjectileSpawnLocation() override;
	

protected:
	
	UPROPERTY(EditAnywhere, Category = "Omega|Combat")
	FName ProjectileSpawnSocket;
	
private:
	
	UPROPERTY(EditAnywhere, Category = "Omega|Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	
	// -------------------------------------
	//  COMBAT 
	// -------------------------------------

public:
	
	FORCEINLINE virtual UPaperZDAnimInstance* GetAnimationInstance_Implementation() const override		{ return PaperAnimation->GetAnimInstance(); }
	FORCEINLINE virtual UPaperZDAnimSequence* GetHitReactionAnimation_Implementation() const override	{ return HitReactAnimation; }

	virtual void Die_Implementation() override;

private:

	UPROPERTY(EditDefaultsOnly, Category = "Omega|Combat")
	TObjectPtr<UPaperZDAnimSequence> HitReactAnimation;

	UPROPERTY(EditDefaultsOnly, Category = "Omega|Combat")
	TObjectPtr<UPaperZDAnimSequence> DeathAnimation;
	
	UPROPERTY(EditDefaultsOnly, Category = "Omega|Combat")
	float PostDeathLifeSpan = 5.f;
	
};
