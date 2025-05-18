#pragma once

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

private:

	static FOmegaGameplayTags GameplayTags;
	

public:

	/*
	 * @key			Damage Type tag
	 * @value		Damage Resistance tag 
	 */
	TMap<FGameplayTag, FGameplayTag> DamageTypesToResistances;
	TMap<EMovementMode, FGameplayTag> MovementModeToTag;
	
	
	//  PRIMARY ATTRIBUTE
	// ===============================================================================================================
	
	FGameplayTag Attributes_Primary_Strength;
	FGameplayTag Attributes_Primary_Intelligence;
	FGameplayTag Attributes_Primary_Dexterity;

	
	//  SECONDARY ATTRIBUTE
	// ===============================================================================================================
	
	FGameplayTag Attributes_Secondary_MaxHealth;
	FGameplayTag Attributes_Secondary_MaxMana;
	FGameplayTag Attributes_Secondary_PhysicalDamage;
	FGameplayTag Attributes_Secondary_MagicDamage;
	FGameplayTag Attributes_Secondary_CritChance;

	
	//  TERTIARY ATTRIBUTE
	// ===============================================================================================================

	FGameplayTag Attributes_Tertiary_Health;
	FGameplayTag Attributes_Tertiary_Mana;
	

	//  DAMAGE TYPES
	// ===============================================================================================================

	FGameplayTag Damage_Type_Physical;
	FGameplayTag Damage_Type_Fire;
	FGameplayTag Damage_Type_Cold;
	FGameplayTag Damage_Type_Poison;
	FGameplayTag Damage_Type_Lightning;

	
	//  DAMAGE RESISTANCES
	// ===============================================================================================================

	FGameplayTag Attributes_Secondary_Resistance_Physical;
	FGameplayTag Attributes_Secondary_Resistance_Fire;
	FGameplayTag Attributes_Secondary_Resistance_Cold;
	FGameplayTag Attributes_Secondary_Resistance_Poison;
	FGameplayTag Attributes_Secondary_Resistance_Lightning;

	
	
	//  DEBUFF STATUSES 
	// ===============================================================================================================
	
	FGameplayTag Elemental_Fire_OnFire;
	FGameplayTag Elemental_Fire_Burn;

	FGameplayTag Elemental_Water_InWater;
	FGameplayTag Elemental_Water_Wet;
	
	
	//  MESSAGES
	// ===============================================================================================================
	
	FGameplayTag Message_HealthPotion_Small;
	FGameplayTag Message_HealthPotion_Mid;
	
	FGameplayTag Message_ManaPotion_Small;
	FGameplayTag Message_ManaPotion_Mid;

	FGameplayTag Message_Potion_Intelligence;
	FGameplayTag Message_Potion_Strength;
	FGameplayTag Message_Potion_Dexterity;

	
	//  INPUT
	// ===============================================================================================================

	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;


	//  META
	// ===============================================================================================================

	FGameplayTag Damage;
	FGameplayTag Effects_HitReact;
	FGameplayTag Effects_Death;

	
	//  Character Types
	// ===============================================================================================================
	
	FGameplayTag Character_Type_Undead;


	//  COLORS
	// ===============================================================================================================

	FGameplayTag Colors_Damage_Immune;
	FGameplayTag Colors_Damage_Blocked;
	FGameplayTag Colors_Damage_Parry;
	FGameplayTag Colors_Damage_Crit;
	

	// COMBAT  
	// ===============================================================================================================
 
	FGameplayTag Combat_Attack;
	FGameplayTag Combat_Attack_Melee;
	FGameplayTag Combat_Attack_Range;
	FGameplayTag Combat_Attack_Combo_WindowOpened;
	FGameplayTag Combat_Attack_Combo_Activated;
	FGameplayTag Combat_Attack_Combo_Count;
	

	//  MOVEMENT
	// ===============================================================================================================
	
	FGameplayTag Movement_State_Falling;
	FGameplayTag Movement_State_Walking;
	FGameplayTag Movement_State_Flying;
	FGameplayTag Movement_State_Swimming;
	
};

