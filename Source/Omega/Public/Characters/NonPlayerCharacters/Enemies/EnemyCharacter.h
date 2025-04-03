#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Characters/OmegaCharacter.h"
#include "Interfaces/EnemyInterface.h"
#include "UI/WidgetControllers/OmegaWidgetController.h"
#include "EnemyCharacter.generated.h"

class UWidgetComponent;
class AOmegaAIController;
class UBehaviorTree;

UCLASS()
class OMEGA_API AEnemyCharacter : public AOmegaCharacter, public IEnemyInterface
{
	GENERATED_BODY()

public:
	AEnemyCharacter(const FObjectInitializer& ObjectInitializer);

	virtual void PossessedBy(AController* NewController) override;
	void BindCallbacks();

protected:
	
	virtual void BeginPlay() override;

	
	// -------------------------------------
	//  COMBAT INTERFACE
	// -------------------------------------

public:
	
	FORCEINLINE virtual int32 GetPlayerLevel() const override { return Level; }

	
	// -------------------------------------
	//  ENEMY INTERFACE
	// -------------------------------------

	virtual void SetCombatTarget_Implementation(AActor* TargetActor) override;


	// -------------------------------------
	//  DELEGATES
	// -------------------------------------
	
	UPROPERTY(BlueprintAssignable)
	FOnAttributeValueChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeValueChangedSignature OnMaxHealthChanged;

	
	// -------------------------------------
	//  AI
	// -------------------------------------
	
	UPROPERTY(EditAnywhere, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY()
	TObjectPtr<AOmegaAIController> OmegaAIController;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	FName CombatTargetName = "CombatTarget";


protected:
	
	virtual void InitAbilityActorInfo() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;

	
	// -------------------------------------
	//  WIDGET
	// -------------------------------------

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;

	
	// -------------------------------------
	//  HIT REACT
	// -------------------------------------

public:
	
	void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewTagCount);

	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	bool bHitReacting = false;

	void DeathTagChanged(const FGameplayTag CallbackTag, int32 NewTagCount);

	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	bool bDead = false;
	
};
