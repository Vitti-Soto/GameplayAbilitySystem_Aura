// Druid Mechanics - Aura Course


#include "AbilitySystem/ModMagCalc/MMC_MaxMana.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxMana::UMMC_MaxMana()
{
	IntellectDef.AttributeToCapture = UAuraAttributeSet::GetIntellectAttribute();
	IntellectDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	IntellectDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(IntellectDef);
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Gather tags from source and target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float Intellect = 0.f;
	GetCapturedAttributeMagnitude(IntellectDef, Spec, EvaluationParameters, Intellect);
	Intellect = FMath::Max<float>(Intellect, 0.f);

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 PlayerLevel = CombatInterface->GetPlayerLevel();

	return 25.f + 2.f * Intellect + 5.f * PlayerLevel;
}
