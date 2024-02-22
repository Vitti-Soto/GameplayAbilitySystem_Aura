// Druid Mechanics - Aura Course


#include "AuraGameplayTags.h"
#include "GameplayTagsManager.h"

FAuraGameplayTags FAuraGameplayTags::GameplayTags;

void FAuraGameplayTags::InitializeNativeGameplayTags()
{
	/* Primary Attributes */
	GameplayTags.Attributes_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Strength"), 
		FString("Physical Damage, Armor Pen, and Critical Hit"));
	GameplayTags.Attributes_Primary_Intellect = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Intellect"), 
		FString("Magical Damage, Mana, and Mana Regeneration"));
	GameplayTags.Attributes_Primary_Resilience = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Resilience"), 
		FString("Armor, Block Chance, and Critical Hit Resistance"));
	GameplayTags.Attributes_Primary_Vigor = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Vigor"), 
		FString("Health and Health Regeneration"));

	/* Secondary Attributes */
	GameplayTags.Attributes_Secondary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxHealth"), 
		FString("Maximum amount of Health obtainable"));
	GameplayTags.Attributes_Secondary_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxMana"), 
		FString("Maximum amount of Mana obtainable"));
	GameplayTags.Attributes_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.Armor"), 
		FString("Reduces damage taken, improves Block Chance"));
	GameplayTags.Attributes_Secondary_ArmorPen = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.ArmorPen"), 
		FString("Ignores percentage of enemy Armor"));
	GameplayTags.Attributes_Secondary_BlockChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.BlockChance"), 
		FString("Chance to cut incoming damage in half"));
	GameplayTags.Attributes_Secondary_CriticalHitChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalHitChance"), 
		FString("Chance to double damage plus Critical Hit bonus"));
	GameplayTags.Attributes_Secondary_CriticalHitDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalHitDamage"), 
		FString("Bonus damage added when a Critical Hit is scored"));
	GameplayTags.Attributes_Secondary_CriticalHitResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalHitResistance"), 
		FString("Reduces Critical Hit Chance of attacking enemies"));
	GameplayTags.Attributes_Secondary_HealthRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.HealthRegeneration"), 
		FString("Amount of Health regenerated every 1 second"));
	GameplayTags.Attributes_Secondary_ManaRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.ManaRegeneration"), 
		FString("Amount of Mana regenerated every 1 second"));
	
	/* Input Tags */
	GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.LMB"), 
		FString("Left Mouse Button"));
	GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.RMB"), 
		FString("Right Mouse Button"));
	GameplayTags.InputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.1"), 
		FString("Number 1 Key"));
	GameplayTags.InputTag_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.2"), 
		FString("Number 2 Key"));
	GameplayTags.InputTag_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.3"), 
		FString("Number 3 Key"));
	GameplayTags.InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.4"), 
		FString("Number 4 Key"));

	/* Resistances */
	GameplayTags.Attributes_Resistance_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Fire"), 
		FString("Resistance to Fire Damage"));
	GameplayTags.Attributes_Resistance_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Lightning"), 
		FString("Resistance to Lightning Damage"));
	GameplayTags.Attributes_Resistance_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Arcane"), 
		FString("Resistance to Arcane Damage"));
	GameplayTags.Attributes_Resistance_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Physical"), 
		FString("Resistance to Physical Damage"));

	/* Damage and Damage Types */
	GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage"), 
		FString("Damage"));

	GameplayTags.Damage_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Fire"), 
		FString("Fire Damage Type"));
	GameplayTags.Damage_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Lightning"), 
		FString("Lightning Damage Type"));
	GameplayTags.Damage_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Arcane"), 
		FString("Arcane Damage Type"));
	GameplayTags.Damage_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Physical"), 
		FString("Physical Damage Type"));

	/* Linking Damage Types to Resistances in Map */
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Arcane, GameplayTags.Attributes_Resistance_Arcane);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Fire, GameplayTags.Attributes_Resistance_Fire);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Lightning, GameplayTags.Attributes_Resistance_Lightning);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Physical, GameplayTags.Attributes_Resistance_Physical);

	/* Effects */
	GameplayTags.Effects_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Effects.HitReact"), 
		FString("Tag granted when Hit Reacting"));

	/* Abilities */
	GameplayTags.Abilities_Attack = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Attack"), 
		FString("Attack Ability Tag"));

	/* Montages */
	GameplayTags.Montage_Attack_Weapon = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Montage.Attack.Weapon"),
		FString("Weapon"));
	GameplayTags.Montage_Attack_LeftHand = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Montage.Attack.RightHand"), 
		FString("Right Hand"));
	GameplayTags.Montage_Attack_RightHand = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Montage.Attack.LeftHand"), 
		FString("Left Hand"));
}
