#include "OmegaGameplayTags.h"

#include "GameplayTagsManager.h"

FOmegaGameplayTags FOmegaGameplayTags::GameplayTags;

void FOmegaGameplayTags::InitializeNativeGameplayTags()
{

	// -------------------------------------
	//  PRIMARY ATTRIBUTES
	// -------------------------------------
	
	// Strength
	GameplayTags.Attributes_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Primary.Strength"),
			FString("Defines how much physical damage and health character has")
			);

	// Intelligence
	GameplayTags.Attributes_Primary_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Intelligence"),
		FString("Defines how much magic damage and mana character has")
		);

	// Dexterity
	GameplayTags.Attributes_Primary_Dexterity = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Dexterity"),
		FString("Defines chance to deal critical damage and block damage")
		);


	// -------------------------------------
	//  SECONDARY ATTRIBUTES
	// -------------------------------------
	
	// MaxHealth
	GameplayTags.Attributes_Secondary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Secondary.MaxHealth"),
			FString("Max amount of health")
			);

	// MaxMana
	GameplayTags.Attributes_Secondary_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Secondary.MaxMana"),
			FString("Max amount of mana")
			);

	// Physical Damage
	GameplayTags.Attributes_Secondary_PhysicalDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Secondary.PhysicalDamage"),
			FString("Physical Damage")
			);

	// Magic Damage
	GameplayTags.Attributes_Secondary_MagicDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Secondary.MagicDamage"),
			FString("Magic Damage")
			);

	// Fire Resistance
	GameplayTags.Attributes_Secondary_Resistance_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Secondary.FireResistance"),
			FString("Fire damage resistance")
			);
	
	// Cold Resistance
	GameplayTags.Attributes_Secondary_Resistance_Cold = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Secondary.ColdResistance"),
			FString("Cold damage resistance")
			);

	// Poison Resistance
	GameplayTags.Attributes_Secondary_Resistance_Poison = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Secondary.PoisonResistance"),
			FString("Posion damage resistance")
			);

	// Lightning Resistance
	GameplayTags.Attributes_Secondary_Resistance_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Secondary.LightningResistance"),
			FString("Lightning damage resistance")
			);


	// Crit Chance
	GameplayTags.Attributes_Secondary_CritChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Secondary.CritChance"),
			FString("Chance to critical hit")
			);


	// -------------------------------------
	//  TERTIARY ATTRIBUTES
	// -------------------------------------
	
	// Health
	GameplayTags.Attributes_Tertiary_Health = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Tertiary.Health"),
			FString("Current amount of health")
			);

	// Mana
	GameplayTags.Attributes_Tertiary_Mana = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Tertiary.Mana"),
			FString("Current amount of mana")
			);

	
	//  ELEMENTAL
	// ===============================================================================================================

	
	// OnFire
	GameplayTags.Elemental_Fire_OnFire = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Elemental.Fire.OnFire"),
			FString("Actor stays on fire")
			);

	// Burn
	GameplayTags.Elemental_Fire_Burn = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Elemental.Fire.Burn"),
			FString("Actor bruns after he came out of fire")
			);

	// InWater
	GameplayTags.Elemental_Water_InWater = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Elemental.Water.InWater"),
			FString("Actor stays in water")
			);

	// Wet
	GameplayTags.Elemental_Water_Wet = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Elemental.Water.Wet"),
			FString("Wet")
			);


	//  DAMAGE TYPES
	// ===============================================================================================================

	// Physical
	GameplayTags.Damage_Type_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Damage.Type.Physical"),
			FString("Physical")
			);
	
	// Fire
	GameplayTags.Damage_Type_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Damage.Type.Fire"),
			FString("Fire")
			);
		
	// Cold
	GameplayTags.Damage_Type_Cold = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Damage.Type.Cold"),
			FString("Cold")
			);
	

	// Poison
	GameplayTags.Damage_Type_Poison = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Damage.Type.Poison"),
			FString("Poison")
			);
	

	// Lightning
	GameplayTags.Damage_Type_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Damage.Type.Lightning"),
			FString("Lightning")
			);
	


	//  DAMAGE RESISTANCES
	// ===============================================================================================================

	// Physical
	GameplayTags.Attributes_Secondary_Resistance_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Secondary.Resistance.Physical"),
			FString("Physical Resistance")
			);

	// Fire
	GameplayTags.Attributes_Secondary_Resistance_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Secondary.Resistance.Fire"),
			FString("Fire Resistance")
			);

	// Cold
	GameplayTags.Attributes_Secondary_Resistance_Cold = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Secondary.Resistance.Cold"),
			FString("Cold Resistance")
			);
	
	// Poison
	GameplayTags.Attributes_Secondary_Resistance_Poison = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Secondary.Resistance.Poison"),
			FString("Poison Resistance")
			);

	// Lightning
	GameplayTags.Attributes_Secondary_Resistance_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Secondary.Resistance.Lightning"),
			FString("Lightning Resistance")
			);

	
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Type_Physical, GameplayTags.Attributes_Secondary_Resistance_Physical);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Type_Fire, GameplayTags.Attributes_Secondary_Resistance_Fire);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Type_Cold, GameplayTags.Attributes_Secondary_Resistance_Cold);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Type_Poison, GameplayTags.Attributes_Secondary_Resistance_Poison);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Type_Lightning, GameplayTags.Attributes_Secondary_Resistance_Lightning);

	
	//  COMBAT
	// ===============================================================================================================

	// Attack
	GameplayTags.Combat_Attack = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Combat.Attack"),
			FString("Defines where character is attacking")
			);

	// Melee Attack
	GameplayTags.Combat_Attack_Melee = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Combat.Attack.Melee"),
			FString("Defines where character is using melee attack")
			);

	// Range Attack
	GameplayTags.Combat_Attack_Range = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Combat.Attack.Range"),
			FString("Defines where character is using Range attack")
			);

	// Open Combo Window
	GameplayTags.Combat_Attack_Combo_WindowOpened = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Combat.Attack.Combo.WindowOpened"),
			FString("Defines when window for activating next combo attack is opened")
			);

	// Next Combo Attack Activated
	GameplayTags.Combat_Attack_Combo_Activated = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Combat.Attack.Combo.Activated"),
			FString("Defines when next combo attack is activated")
			);

	// Combo Attack Count
	GameplayTags.Combat_Attack_Combo_Count = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Combat.Attack.Combo.Count"),
			FString("Every stack of this tag associated with combo attack animation index. If tag not applied, index is '0'.")
			);
	
	
	
	
	//  MESSAGES
	// ===============================================================================================================
	
	// Health Potions
	GameplayTags.Message_HealthPotion_Small = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Message.HealthPotion.Small"),
			FString("Small health potion taken")
			);

	
	GameplayTags.Message_HealthPotion_Mid = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Message.HealthPotion.Mid"),
			FString("Mid health potion taken")
			);

	// Mana Potions
	GameplayTags.Message_ManaPotion_Small = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Message.ManaPotion.Small"),
			FString("Small Mana potion taken")
			);
	
	GameplayTags.Message_ManaPotion_Mid = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Message.ManaPotion.Mid"),
			FString("Mid Mana potion taken")
			);

	// Intelligence Potion
	GameplayTags.Message_Potion_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Message.Potion.Intelligence"),
			FString("Permanently add intelligence")
			);

	// Strength Potion
	GameplayTags.Message_Potion_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Message.Potion.Strength"),
			FString("Permanently add Strength")
			);

	// Dexterity Potion
	GameplayTags.Message_Potion_Dexterity = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Message.Potion.Dexterity"),
			FString("Permanently add Dexterity")
			);

	
	// -------------------------------------
	//  INPUT
	// -------------------------------------
	
	// Left Mouse Button
	GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Input.LMB"),
			FString("Left Mouse Button")
			);

	// Right Mouse Button
	GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Input.RMB"),
			FString("Right Mouse Button")
			);


	// -------------------------------------
	//  META
	// -------------------------------------

	// Damage
	GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Meta.Damage"),
			FString("Damage")
			);

	// Hit React
	GameplayTags.Effects_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Effects.HitReact"),
			FString("Tag granted when owner get a hit")
			);

	// Death
	GameplayTags.Effects_Death = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Effects.Death"),
			FString("Tag granted when owner dies")
			);


	//  Character Types
	// ===============================================================================================================

	// Undead
	GameplayTags.Character_Type_Undead = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Character.Type.Undead"),
			FString("Defines this character as an undead")
			);

	
	// ===============================================================================================================
	//  ATTACK TYPES
	// ===============================================================================================================

	// Melee
	GameplayTags.Character_AttackType_Melee = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Character.AttackType.Melee"),
			FString("Melee Attack")
			);

	// Range
	GameplayTags.Character_AttackType_Range = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Character.AttackType.Range"),
			FString("Range Attack")
			);

	// --------------------------------------------------------------------------------------------------------------

	
	//  COLORS
	// ===============================================================================================================

	// Damage Immune
	GameplayTags.Colors_Damage_Immune = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Colors.Damage.Immune"),
			FString("Defines damage widget color when the target is immune to the damage")
			);

	// Damage Blocked
	GameplayTags.Colors_Damage_Blocked = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Colors.Damage.Blocked"),
			FString("Defines damage widget color when the target is Blocked the damage")
			);

	// Damage Parry
	GameplayTags.Colors_Damage_Parry = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Colors.Damage.Parry"),
			FString("Defines damage widget color when the target is Parry the damage")
			);

	// Damage Crit
	GameplayTags.Colors_Damage_Crit = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Colors.Damage.Crit"),
			FString("Defines damage widget color when the target is getting Crit damage")
			);


	//  MOVEMENT
	// ===============================================================================================================

	// Falling
	GameplayTags.Movement_State_Falling = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Movement.State.Falling"),
			FString("Assigned when character in air(jumping, falling, еtc")
			);

	// Walking
	GameplayTags.Movement_State_Walking = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Movement.State.Walking"),
			FString("Assigned when character is moving on the ground")
			);

	// Flying
	GameplayTags.Movement_State_Flying = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Movement.State.Flying"),
			FString("Assigned when character is flying")
			);

	// Swimming
	GameplayTags.Movement_State_Swimming = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Movement.State.Swimming"),
			FString("Assigned when character is Swimming")
			);

	GameplayTags.MovementModeToTag.Add(EMovementMode::MOVE_Falling, GameplayTags.Movement_State_Falling);
	GameplayTags.MovementModeToTag.Add(EMovementMode::MOVE_Walking, GameplayTags.Movement_State_Walking);
	GameplayTags.MovementModeToTag.Add(EMovementMode::MOVE_Flying, GameplayTags.Movement_State_Flying);
	GameplayTags.MovementModeToTag.Add(EMovementMode::MOVE_Swimming, GameplayTags.Movement_State_Swimming);
}
