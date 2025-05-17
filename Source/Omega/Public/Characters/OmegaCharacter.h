#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "PaperCharacter.h"
#include "PaperFlipbookComponent.h"
#include "PaperZDAnimationComponent.h"
#include "PaperZDAnimInstance.h"
#include "Interfaces/CombatInterface.h"

#include "OmegaCharacter.generated.h"

struct FGameplayTagContainer;
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
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PaperZD", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPaperZDAnimationComponent> PaperAnimation;

	UPROPERTY(EditDefaultsOnly, Category = "Omega|Combat")
	float PostDeathLifeSpan = 5.f;

	//  ABILITY SYSTEM
	// ===============================================================================================================

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Omega|Character Tags", DisplayName = "Type")
	FGameplayTagContainer CharacterTypeTags;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Omega|Character Tags", DisplayName = "AttackType")
	FGameplayTagContainer CharacterAttackTypeTags;

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
	void AddCharacterTags();
	void ModifyAttributesByTag() const;

public:
	
	
	virtual FVector GetProjectileSpawnSocket(bool& bSocketExist) override;
	

protected:
	
	UPROPERTY(EditAnywhere, Category = "Omega|Combat")
	FName ProjectileSpawnSocket;
	
private:
	
	UPROPERTY(EditAnywhere, Category = "Omega|Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	
	//  COMBAT INTERFACE
	// ===============================================================================================================
	
public:

	virtual AActor* GetAvatar_Implementation() const override;

	// Animations
	FORCEINLINE virtual UPaperZDAnimInstance* GetAnimationInstance_Implementation() const override
	{
		if (!PaperAnimation) return nullptr; 
		return PaperAnimation->GetAnimInstance();
	}
	FORCEINLINE virtual UPaperZDAnimSequence* GetHitReactionAnimation_Implementation() const override		{ return HitReactAnimation; }
	FORCEINLINE virtual UPaperZDAnimSequence* GetDeathAnimation_Implementation() const override				{ return DeathAnimation; }
	virtual UPaperZDAnimSequence* GetAttackAnimation_Implementation() override;

	// Attack
	virtual void Attack_Implementation() override;
	virtual void OnAttackFinished_Implementation() override;
	virtual FVector GetCombatSocketLocation_Implementation() const override;

	// Combo
	virtual void SetIsAttackWindowOpened_Implementation(const FGameplayTag& ComboWindowOpenedTag) override;
	virtual void ResetAttack_Implementation() override;
	
	// Death
	virtual void Die_Implementation() override;
	virtual bool IsDead_Implementation() const override;

private:

	UPROPERTY(EditDefaultsOnly, Category = "Omega|Combat")
	TObjectPtr<UPaperZDAnimSequence> HitReactAnimation;

	UPROPERTY(EditDefaultsOnly, Category = "Omega|Combat")
	TObjectPtr<UPaperZDAnimSequence> DeathAnimation;

	UPROPERTY(EditDefaultsOnly, Category = "Omega|Combat|Animations", DisplayName = "Ground")
	TArray<TObjectPtr<UPaperZDAnimSequence>> AttackAnimations;

	UPROPERTY(EditDefaultsOnly, Category = "Omega|Combat|Animations", DisplayName = "Air")
	TArray<TObjectPtr<UPaperZDAnimSequence>> AirAttackAnimations;
};
