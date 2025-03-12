
#pragma once

#include "CoreMinimal.h"
#include "OmegaBaseCharacter.h"
#include "NonPlayerCharacter.generated.h"

UCLASS()
class OMEGA_API ANonPlayerCharacter : public AOmegaBaseCharacter
{
	GENERATED_BODY()

public:

	ANonPlayerCharacter();

protected:

	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;

	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
