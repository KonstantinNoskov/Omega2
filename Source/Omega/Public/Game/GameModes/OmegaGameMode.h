#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "OmegaGameMode.generated.h"

class UDamageWidgetData;
class UCharacterDefaultInfo;

UCLASS()
class OMEGA_API AOmegaGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category = "Omega|Character Class Defaults")
	UCharacterDefaultInfo* CharacterClassInfo;

	UPROPERTY(EditDefaultsOnly, Category = "Omega|UI")
	UDamageWidgetData* DamageWidgetData;
};
