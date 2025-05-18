#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"


class UPaperZDAnimInstance;
class UPaperZDAnimSequence;

UINTERFACE(BlueprintType, Blueprintable)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

class OMEGA_API ICombatInterface
{
	GENERATED_BODY()

public:
	
	virtual int32 GetPlayerLevel() const;
	
	virtual FVector GetProjectileSpawnSocket(bool& bSocketExist);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UPaperZDAnimInstance* GetAnimationInstance() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UPaperZDAnimSequence* GetHitReactionAnimation() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UPaperZDAnimSequence* GetDeathAnimation() const;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Die();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool IsDead() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	AActor* GetAvatar();

	
	//  ATTACK
	// ===============================================================================================================

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Attack();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnAttackFinished();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetComboActivated(bool NewComboActivated);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool IsComboActivated() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetIsAttacking(bool bAttacking);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetIsAttackWindowOpened(const FGameplayTag& ComboWindowOpenedTag);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool IsAttackWindowOpened() const;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UPaperZDAnimSequence* GetAttackAnimation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	TArray<UPaperZDAnimSequence*> GetAttackAnimations();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	TArray<UPaperZDAnimSequence*> GetAirAttackAnimations();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ResetAttack();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FVector GetCombatSocketLocation() const;
	
	
	// ===============================================================================================================

	
};
