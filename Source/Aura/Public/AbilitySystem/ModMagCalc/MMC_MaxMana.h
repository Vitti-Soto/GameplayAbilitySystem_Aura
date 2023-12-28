// Druid Mechanics - Aura Course

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_MaxMana.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UMMC_MaxMana : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
	
public:
	UMMC_MaxMana();

	/** <UGameplayModMagnitudeCalculation> */
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
	/** </UGameplayModMagnitudeCalculation> */

private:
	FGameplayEffectAttributeCaptureDefinition IntellectDef;
};
