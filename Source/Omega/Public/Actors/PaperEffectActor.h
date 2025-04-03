#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookActor.h"
#include "PaperEffectActor.generated.h"

UCLASS()
class OMEGA_API APaperEffectActor : public APaperFlipbookActor
{
	GENERATED_BODY()

public:
	
	APaperEffectActor();
	void HandleEffectDestroy();

protected:
	
	virtual void BeginPlay() override;

	
	private:

	FTimerHandle DestroyTimerHandle;
};
