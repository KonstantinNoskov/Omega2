#pragma once

#include <Windows.ApplicationModel.Appointments.h>

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "DamageWidgetInfo.generated.h"


class UWidgetAnimation;


UCLASS()
class OMEGA_API UDamageWidgetData : public UDataAsset
{
	GENERATED_BODY()

public:
	
	const FColor& GetDamageTypeColorByTag(const FGameplayTag& GameplayTag);
	
	// Damage Type Color
	UPROPERTY(EditDefaultsOnly, meta=(ForceInlineRow), displayname="Damage Type Color")
	TMap<FGameplayTag, FColor> DamageTypeColorsMap;
	
};






