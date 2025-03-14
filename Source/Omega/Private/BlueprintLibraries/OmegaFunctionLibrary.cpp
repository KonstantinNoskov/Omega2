// Fill out your copyright notice in the Description page of Project Settings.


#include "BlueprintLibraries/OmegaFunctionLibrary.h"

#include "GameplayAbilitySpec.h"
#include "PaperSprite.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Game/GameModes/OmegaGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "AbilitySystemComponent.h"

FVector2D UOmegaFunctionLibrary::GetSourceSize(UPaperSprite* Sprite)
{
	return Sprite->GetSourceSize();
}

void UOmegaFunctionLibrary::GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC)
{
	// Check for GameMode
	AOmegaGameMode* OmegaGameMode = Cast<AOmegaGameMode>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (!OmegaGameMode) return;

	// Check for Character Class Info 
	if (!OmegaGameMode->CharacterClassInfo)
	{
		UE_LOG(LogTemp, Error, TEXT("[%hs] Character Class Info is null. Check for game mode defaults."), __FUNCTION__);
		return;
	}

	
	UCharacterClassInfo* CharacterClassInfo = OmegaGameMode->CharacterClassInfo;
	
	for (const TSubclassOf<UGameplayAbility> AbilityClass : CharacterClassInfo->CommonAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		ASC->GiveAbility(AbilitySpec);
	}
}
