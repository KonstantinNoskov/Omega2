#pragma once

#include <Windows.ApplicationModel.Appointments.h>

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "DamageWidgetInfo.generated.h"


class UWidgetAnimation;

USTRUCT()
struct FDamageWidgetInfo
{
	GENERATED_BODY()
	
	float DamageMagnitude = 0.f; 

	UPROPERTY(EditDefaultsOnly)
	FText DamageStatus = FText();
	
	UPROPERTY(EditDefaultsOnly)
	FColor DamageColor = FColor::White;
};

UCLASS()
class OMEGA_API UDamageWidgetData : public UDataAsset
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, meta=(ForceInlineRow), displayname="Damage Widget Info")
	TMap<FGameplayTag, FDamageWidgetInfo> DamageWidgetDataMap;

	UPROPERTY(EditDefaultsOnly, meta=(ForceInlineRow), displayname="Damage Widget Info")
	TArray<FDamageWidgetInfo> DamageWidgetInfos;
	
	const FDamageWidgetInfo& GetDamageWidgetInfoByTag(const FGameplayTag& DamageTag);
	
};






