#include "Actors/PaperEffectActor.h"

#include "PaperFlipbookComponent.h"


APaperEffectActor::APaperEffectActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	GetRenderComponent()->SetLooping(false);
}



void APaperEffectActor::BeginPlay()
{
	Super::BeginPlay();
	HandleEffectDestroy();
}


void APaperEffectActor::HandleEffectDestroy()
{
	// Destroy immediately if source effect is empty
	if (!GetRenderComponent()->GetFlipbook()) Destroy();
	
	float EffectLifeSpan = 0.f;
	
	// Init Destroy Delegate
	FTimerDelegate TimerDelegate;
	TimerDelegate.BindLambda([this]()
	{
		Destroy();
	});
	
	// Start effect animation
	GetRenderComponent()->Play();

	// Init destroy timer
	EffectLifeSpan = GetRenderComponent()->GetFlipbookLength();
	GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle, TimerDelegate, EffectLifeSpan, false);
}

