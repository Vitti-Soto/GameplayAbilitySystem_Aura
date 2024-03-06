// Druid Mechanics - Aura Course


#include "AbilitySystem/Abilities/AuraSummonAbility.h"

TArray<FVector> UAuraSummonAbility::GetSpawnLocations()
{
	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	const FVector Location = GetAvatarActorFromActorInfo()->GetActorLocation();
	const float DeltaSpread = SpawnSpread / NumMinions;
	const float DeltaAdjust = DeltaSpread / 2.f;

	TArray<FVector> SpawnLocations;

	const FVector RightOfSpread = Forward.RotateAngleAxis(SpawnSpread / 2.f, FVector::UpVector);

	for (int32 i = 0; i < NumMinions; i++)
	{
		const FVector Direction = RightOfSpread.RotateAngleAxis((-DeltaSpread * i) - DeltaAdjust, FVector::UpVector);
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



		/*
		*	DrawDebugSphere(
		*		GetWorld(),
		*		ChosenSpawnLocation,
		*		20.f,
		*		12,
		*		FColor::Cyan,
		*		false,
		*		3.f);
		*
		*	UKismetSystemLibrary::DrawDebugArrow(
		*		GetAvatarActorFromActorInfo(),
		*		Location,
		*		Location + Direction * MaxSpawnDistance,
		*		4.f,
		*		FLinearColor::Blue,
		*		3.f);
		*
		*	DrawDebugSphere(
		*		GetWorld(),
		*		Location + Direction * MinSpawnDistance,
		*		10.f,
		*		12,
		*		FColor::Green,
		*		false,
		*		3.f);
		*
		*	DrawDebugSphere(
		*		GetWorld(),
		*		Location + Direction * MaxSpawnDistance,
		*		10.f,
		*		12,
		*		FColor::Red,
		*		false,
		*		3.f);
		*/
	}

	return SpawnLocations;
}

TSubclassOf<APawn> UAuraSummonAbility::GetRandomMinionClass()
{
	const int32 Selection = FMath::RandRange(0, MinionClasses.Num() - 1);

	return MinionClasses[Selection];
}
