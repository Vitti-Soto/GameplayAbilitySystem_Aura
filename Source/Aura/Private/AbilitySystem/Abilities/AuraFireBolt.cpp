// Druid Mechanics - Aura Course


#include "AbilitySystem/Abilities/AuraFireBolt.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Actor/AuraProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

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
			FMath::Min(Level, MaxNumProjectiles),
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
		FMath::Min(Level, MaxNumProjectiles),
		ScaledDamage);
}

void UAuraFireBolt::SpawnProjectiles(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTag, bool bOverridePitch, float PitchOverride, AActor* HomingTarget)
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer) return;

	// Make this the Avatar Actor's Location instead, otherwise clicking under Aura will give weird results
	const FVector SocketLocation = ICombatInterface::Execute_GetCombatSocketLocation(
		GetAvatarActorFromActorInfo(),
		SocketTag);

	FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();

	if (bOverridePitch)
	{
		Rotation.Pitch = PitchOverride;
	}

	const FVector Forward = Rotation.Vector();
	const int32 NumProjectiles = FMath::Min(GetAbilityLevel(), MaxNumProjectiles);

	TArray<FRotator> Rotations = UAuraAbilitySystemLibrary::EvenlySpacedRotators(Forward, FVector::UpVector, ProjectileSpread, NumProjectiles);

	for (const FRotator& Rot : Rotations)
	{
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		SpawnTransform.SetRotation(Rot.Quaternion());

		AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(
			ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		Projectile->DamageEffectParams = MakeDamageEffectParamsFromClassDefaults();

		if (HomingTarget && HomingTarget->Implements<UCombatInterface>())
		{
			Projectile->ProjectileMovement->HomingTargetComponent = HomingTarget->GetRootComponent();
		}
		else
		{
			Projectile->HomingTargetSceneComponent = NewObject<USceneComponent>(USceneComponent::StaticClass());
			Projectile->HomingTargetSceneComponent->SetWorldLocation(ProjectileTargetLocation);
			Projectile->ProjectileMovement->HomingTargetComponent = Projectile->HomingTargetSceneComponent;
		}
		Projectile->ProjectileMovement->HomingAccelerationMagnitude = FMath::FRandRange(HomingAccelerationMin, HomingAccelerationMax);
		Projectile->ProjectileMovement->bIsHomingProjectile = bIsHoming;

		Projectile->FinishSpawning(SpawnTransform);
	}
}
