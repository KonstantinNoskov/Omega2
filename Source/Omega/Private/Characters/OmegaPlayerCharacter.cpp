// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/OmegaPlayerCharacter.h"


// Sets default values
AOmegaPlayerCharacter::AOmegaPlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AOmegaPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOmegaPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AOmegaPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

