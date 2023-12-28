// Druid Mechanics - Aura Course

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_MaxHealth.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UMMC_MaxHealth : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
	
public:
	UMMC_MaxHealth();

	/** <UGameplayModMagnitudeCalculation> */
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
	/** </UGameplayModMagnitudeCalculation> */

private:
	FGameplayEffectAttributeCaptureDefinition VigorDef;
};
