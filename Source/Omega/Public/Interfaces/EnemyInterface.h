#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnemyInterface.generated.h"

UINTERFACE(BlueprintType, Blueprintable)
class UEnemyInterface : public UInterface
{
	GENERATED_BODY()
};

class OMEGA_API IEnemyInterface
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetCombatTarget(AActor* TargetActor);
	
};
