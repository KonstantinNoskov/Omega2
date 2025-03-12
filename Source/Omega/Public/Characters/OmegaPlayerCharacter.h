// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OmegaBaseCharacter.h"
#include "OmegaPlayerCharacter.generated.h"

UCLASS()
class OMEGA_API AOmegaPlayerCharacter : public AOmegaBaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AOmegaPlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
