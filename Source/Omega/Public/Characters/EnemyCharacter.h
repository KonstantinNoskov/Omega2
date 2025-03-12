#pragma once

#include "CoreMinimal.h"
#include "NonPlayerCharacter.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class OMEGA_API AEnemyCharacter : public ANonPlayerCharacter
{
	GENERATED_BODY()

public:

	AEnemyCharacter();

protected:

	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;


	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
