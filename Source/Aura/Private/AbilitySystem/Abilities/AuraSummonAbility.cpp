// Druid Mechanics - Aura Course


#include "AbilitySystem/Abilities/AuraSummonAbility.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"

TArray<FVector> UAuraSummonAbility::GetSpawnLocations()
{
	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	const FVector Location = GetAvatarActorFromActorInfo()->GetActorLocation();

	TArray<FVector> Directions = UAuraAbilitySystemLibrary::EvenlyRotatedVectors(Forward, FVector::UpVector, SpawnSpread, NumMinions);

	TArray<FVector> SpawnLocations;

	for (const FVector& Direction : Directions)
	{
		FVector ChosenSpawnLocation = Location + Direction * FMath::FRandRange(MinSpawnDistance, MaxSpawnDistance);

		FHitResult Hit;
		GetWorld()->LineTraceSingleByChannel(Hit,
			ChosenSpawnLocation + FVector(0.f, 0.f, 400.f),
			ChosenSpawnLocation - FVector(0.f, 0.f, 400.f),
			ECC_Visibility);

		if (Hit.bBlockingHit)
		{
			ChosenSpawnLocation = Hit.ImpactPoint;
		}

		SpawnLocations.Add(ChosenSpawnLocation);
	}

	return SpawnLocations;
}

TSubclassOf<APawn> UAuraSummonAbility::GetRandomMinionClass()
{
	const int32 Selection = FMath::RandRange(0, MinionClasses.Num() - 1);

	return MinionClasses[Selection];
}
