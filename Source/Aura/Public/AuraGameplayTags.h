// Druid Mechanics - Aura Course

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * AuraGameplayTags
 * 
 * Singleton containing native Gameplay Tags
 */
struct FAuraGameplayTags
{
public:
	static const FAuraGameplayTags& Get() { return GameplayTags; }
	static void InitializeNativeGameplayTags();

	/* Primary Attributes */
	FGameplayTag Attributes_Primary_Strength;
	FGameplayTag Attributes_Primary_Intellect;
	FGameplayTag Attributes_Primary_Resilience;
	FGameplayTag Attributes_Primary_Vigor;

	/* Secondary Attributes */
	FGameplayTag Attributes_Secondary_MaxHealth;
	FGameplayTag Attributes_Secondary_MaxMana;
	FGameplayTag Attributes_Secondary_Armor;
	FGameplayTag Attributes_Secondary_ArmorPen;
	FGameplayTag Attributes_Secondary_BlockChance;
	FGameplayTag Attributes_Secondary_CriticalHitChance;
	FGameplayTag Attributes_Secondary_CriticalHitDamage;
	FGameplayTag Attributes_Secondary_CriticalHitResistance;
	FGameplayTag Attributes_Secondary_HealthRegeneration;
	FGameplayTag Attributes_Secondary_ManaRegeneration;

	/* Resistance Attributes */
	FGameplayTag Attributes_Resistance_Fire;
	FGameplayTag Attributes_Resistance_Lightning;
	FGameplayTag Attributes_Resistance_Arcane;
	FGameplayTag Attributes_Resistance_Physical;

	/* Meta Attributes */
	FGameplayTag Attributes_Meta_IncomingXP;

	/* Inputs */
	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_1;
	FGameplayTag InputTag_2;
	FGameplayTag InputTag_3;
	FGameplayTag InputTag_4;

	/* Damage and Damage Types */
	FGameplayTag Damage;
	FGameplayTag Damage_Fire;
	FGameplayTag Damage_Lightning;
	FGameplayTag Damage_Arcane;
	FGameplayTag Damage_Physical;

	/* Abilities */
	FGameplayTag Abilities_Attack;
	FGameplayTag Abilities_Summon;

	FGameplayTag Abilities_Fire_FireBolt;

	/* Cooldowns */
	FGameplayTag Cooldown_Fire_FireBolt;

	/* Damage Types to Resistances Map */
	TMap<FGameplayTag, FGameplayTag> DamageTypesToResistances;

	/* Effect */
	FGameplayTag Effects_HitReact;

	/* Cues */
	FGameplayTag GameplayCue_MeleeImpact;

	/* Combat Socket */
	FGameplayTag CombatSocket_Weapon;
	FGameplayTag CombatSocket_LeftHand;
	FGameplayTag CombatSocket_RightHand;
	FGameplayTag CombatSocket_Tail;

	/* Montages */
	FGameplayTag Montage_Attack_1;
	FGameplayTag Montage_Attack_2;
	FGameplayTag Montage_Attack_3;
	FGameplayTag Montage_Attack_4;

	FGameplayTag Montage_Summon_1;
	
private:
	static FAuraGameplayTags GameplayTags;

};