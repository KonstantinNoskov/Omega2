#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "OmegaGameMode.generated.h"

class UCharacterTypeInfo;

UCLASS()
class OMEGA_API AOmegaGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category = "Omega|Character Class Defaults")
	UCharacterTypeInfo* CharacterClassInfo;
};
