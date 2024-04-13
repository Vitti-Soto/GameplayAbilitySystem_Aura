// Druid Mechanics - Aura Course


#include "AbilitySystem/Abilities/AuraFireBolt.h"
#include "Aura/Public/AuraGameplayTags.h"

FString UAuraFireBolt::GetDescription(int32 Level)
{

	const int32 Damage = GetDamageByDamageType(Level, FAuraGameplayTags::Get().Damage_Fire);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	if (Level == 1)
	{
		return FString::Printf(TEXT(
			// Title
			"<Title>FIRE BOLT</>\n"
			// Details
			"<Small>Spell Level: </><Level>%d</>\n" // Level
			"<Small>Mana Cost: </><ManaCost>%.1f</>\n" // ManaCost
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n" // Cooldown
			// Description
			"<Default>Launches a bolt of fire, "
			"exploding on impact and dealing "
			"</><Damage> % d</><Default> fire damage " // Damage
			"with a x chance to burn.</>"),  
			// Values
			Level,
			ManaCost,
			Cooldown,
			Damage);
	}
	else
	{
		return FString::Printf(TEXT(
			// Title
			"<Title>FIRE BOLT</>\n"
			// Details
			"<Small>Spell Level: </><Level>%d</>\n" // Level
			"<Small>Mana Cost: </><ManaCost>%.1f</>\n" // ManaCost
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n" // Cooldown
			// Description
			"<Default>Launches %d bolts of fire, " // FMath::Min
			"exploding on impact and dealing "
			"</><Damage> % d</><Default> fire damage " // Damage
			"with a x chance to burn.</>"),
			// Values
			Level,
			ManaCost,
			Cooldown,
			FMath::Min(Level, NumProjectiles),
			Damage);
	}
}

FString UAuraFireBolt::GetNextLevelDescription(int32 Level)
{
	const int32 Damage = GetDamageByDamageType(Level, FAuraGameplayTags::Get().Damage_Fire);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	return FString::Printf(TEXT(
		// Title
		"<Title>NEXT LEVEL</>\n"
		// Details
		"<Small>Spell Level: </><Level>%d</>\n" // Level
		"<Small>Mana Cost: </><ManaCost>%.1f</>\n" // ManaCost
		"<Small>Cooldown: </><Cooldown>%.1f</>\n\n" // Cooldown
		// Description
		"<Default>Launches %d bolts of fire, " // FMath::Min
		"exploding on impact and dealing "
		"</><Damage> % d</><Default> fire damage " // Damage
		"with a x chance to burn.</>"),
		// Values
		Level,
		ManaCost,
		Cooldown,
		FMath::Min(Level, NumProjectiles),
		Damage);
}
