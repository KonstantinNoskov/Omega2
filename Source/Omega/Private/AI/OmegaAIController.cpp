#include "AI/OmegaAIController.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

AOmegaAIController::AOmegaAIController()
{
	PrimaryActorTick.bCanEverTick = true;

	Blackboard = CreateDefaultSubobject<UBlackboardComponent>("Blackboard Component");
	check(Blackboard);
	
	/*
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>("BehaviorTree Component");
	check(BehaviorTreeComponent);*/
}

void AOmegaAIController::BeginPlay()
{
	Super::BeginPlay();
	
}

void AOmegaAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

