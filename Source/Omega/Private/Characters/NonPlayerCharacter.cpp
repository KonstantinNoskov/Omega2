

#include "Characters/NonPlayerCharacter.h"



ANonPlayerCharacter::ANonPlayerCharacter()
{

	PrimaryActorTick.bCanEverTick = true;
}


void ANonPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}


void ANonPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ANonPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

