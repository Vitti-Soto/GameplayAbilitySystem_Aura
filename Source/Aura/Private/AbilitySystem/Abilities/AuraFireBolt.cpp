// Druid Mechanics - Aura Course


#include "AbilitySystem/Abilities/AuraFireBolt.h"

FString UAuraFireBolt::GetDescription(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
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
			"</><Damage> % d</><Default> fire damage " // ScaledDamage
			"with a x chance to burn.</>"),  
			// Values
			Level,
			ManaCost,
			Cooldown,
			ScaledDamage);
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
			"</><Damage> % d</><Default> fire damage " // ScaledDamage
			"with a x chance to burn.</>"),
			// Values
			Level,
			ManaCost,
			Cooldown,
			FMath::Min(Level, NumProjectiles),
			ScaledDamage);
	}
}

FString UAuraFireBolt::GetNextLevelDescription(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
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
		"</><Damage> % d</><Default> fire damage " // ScaledDamage
		"with a x chance to burn.</>"),
		// Values
		Level,
		ManaCost,
		Cooldown,
		FMath::Min(Level, NumProjectiles),
		ScaledDamage);
}
