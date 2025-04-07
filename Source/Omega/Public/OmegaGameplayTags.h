﻿#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"


/**
 * OmegaGameplayTags
 *
 * Singleton containing native Gameplay Tags
 */

struct FOmegaGameplayTags
{
	

	static const FOmegaGameplayTags& Get() { return GameplayTags; }
	static void InitializeNativeGameplayTags();
	static void StoreAnimationTags();
	FORCEINLINE static const FGameplayTagContainer& GetAnimationTags() { return AnimationTags; }
	

private:

	static FOmegaGameplayTags GameplayTags;
	static FGameplayTagContainer AnimationTags;
	
	
	
public:
	
	// -------------------------------------
	//  PRIMARY ATTRIBUTE
	// -------------------------------------
	
	FGameplayTag Attributes_Primary_Strength;
	FGameplayTag Attributes_Primary_Intelligence;
	FGameplayTag Attributes_Primary_Dexterity;


	// -------------------------------------
	//  SECONDARY ATTRIBUTE
	// -------------------------------------
	
	FGameplayTag Attributes_Secondary_MaxHealth;
	FGameplayTag Attributes_Secondary_MaxMana;
	FGameplayTag Attributes_Secondary_PhysicalDamage;
	FGameplayTag Attributes_Secondary_MagicDamage;
	FGameplayTag Attributes_Secondary_CritChance;


	// -------------------------------------
	//  TERTIARY ATTRIBUTE
	// -------------------------------------

	FGameplayTag Attributes_Tertiary_Health;
	FGameplayTag Attributes_Tertiary_Mana;

	
	// -------------------------------------
	//  ELEMENTAL
	// -------------------------------------
	
	FGameplayTag Elemental_Fire_OnFire;
	FGameplayTag Elemental_Fire_Burn;

	FGameplayTag Elemental_Water_InWater;
	FGameplayTag Elemental_Water_Wet;

	
	// -------------------------------------
	//  MESSAGES
	// -------------------------------------
	
	FGameplayTag Message_HealthPotion_Small;
	FGameplayTag Message_HealthPotion_Mid;
	
	FGameplayTag Message_ManaPotion_Small;
	FGameplayTag Message_ManaPotion_Mid;

	FGameplayTag Message_Potion_Intelligence;
	FGameplayTag Message_Potion_Strength;
	FGameplayTag Message_Potion_Dexterity;

	
	//  INPUT
	// -------------------------------------

	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;


	//  META
	// -------------------------------------

	FGameplayTag Damage;
	FGameplayTag Effects_HitReact;
	FGameplayTag Effects_Death;


	//  ANIMATION 
	// ===============================================================================================================
	
	FGameplayTag Animation_Death;
	FGameplayTag Animation_Idle;
	FGameplayTag Animation_Dash;
	FGameplayTag Animation_Attack;

	
};

