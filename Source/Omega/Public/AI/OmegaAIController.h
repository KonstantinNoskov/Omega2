#pragma once

#include "CoreMinimal.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "OmegaAIController.generated.h"

class UBehaviorTreeComponent;

UCLASS()
class OMEGA_API AOmegaAIController : public AAIController
{
	GENERATED_BODY()

public:

	AOmegaAIController();
	
	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;
	
	/*UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;*/

};
