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

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void Attack() const;
	
	virtual int32 GetPlayerLevel() const;
	
	virtual FVector GetProjectileSpawnLocation();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UPaperZDAnimInstance* GetAnimationInstance() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UPaperZDAnimSequence* GetHitReactionAnimation() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Die();
};
