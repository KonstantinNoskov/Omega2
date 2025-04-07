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
	// -------------------------------------

	
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

	
	//  MESSAGES
	// -------------------------------------
	
	// Health Potions
	GameplayTags.Message_HealthPotion_Small = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Message.HealthPotion.Small"),
			FString("Small health potion taken")
			);

	
	GameplayTags.Message_HealthPotion_Mid = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Message.HealthPotion.Mid"),
			FString("Mid health potion taken")
			);

	// Mana Potion - Small
	GameplayTags.Message_ManaPotion_Small = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Message.ManaPotion.Small"),
			FString("Small Mana potion taken")
			);

	// Mana Potion - Mid
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


	//  ANIMATIONS
	// ===============================================================================================================
	
	
	
	// Death 
	GameplayTags.Animation_Death = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Animation.Death"),
			FString("Должен быть добавлен в AnimationTags класса UGGE2D_AnimInstance, чтобы воспроизвести анимацию смерти.")
			);

	// Idle 
	GameplayTags.Animation_Idle = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Animation.Idle"),
			FString("Должен быть добавлен в AnimationTags класса UGGE2D_AnimInstance, чтобы воспроизвести анимацию ожидания.")
			);

	// Dash 
	GameplayTags.Animation_Dash = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Animation.Dash"),
			FString("Должен быть добавлен в AnimationTags класса UGGE2D_AnimInstance, чтобы воспроизвести анимацию рывка.")
			);

	// Attack 
	GameplayTags.Animation_Attack = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Animation.Attack"),
			FString("Должен быть добавлен в AnimationTags класса UGGE2D_AnimInstance, чтобы воспроизвести анимацию атаки.")
			);
}


void FOmegaGameplayTags::StoreAnimationTags()
{
	
}