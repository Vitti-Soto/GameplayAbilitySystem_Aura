// Druid Mechanics - Aura Course


#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"
#include "AbilitySystemComponent.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Interaction/CombatInterface.h"
#include "AuraAbilityTypes.h"

UExecCalc_Damage::UExecCalc_Damage()
{
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
	RelevantAttributesToCapture.Add(DamageStatics().ArmorPenDef);
	RelevantAttributesToCapture.Add(DamageStatics().BlockChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitDamageDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitResistanceDef);
	
	RelevantAttributesToCapture.Add(DamageStatics().ArcaneResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().FireResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().LightningResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().PhysicalResistanceDef);
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;
	ICombatInterface* SourceCombatInterface = Cast<ICombatInterface>(SourceAvatar);
	ICombatInterface* TargetCombatInterface = Cast<ICombatInterface>(TargetAvatar);

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	FGameplayEffectContextHandle EffectContextHandle = Spec.GetContext();

	// Gather tags from source and target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;
	const UCharacterClassInfo* CharacterClassInfo = UAuraAbilitySystemLibrary::GetCharacterClassInfo(SourceAvatar);

	// Get Damage Set by Caller Magnitude
	float Damage = 0.f;
	for (const TPair<FGameplayTag, FGameplayTag>& Pair : FAuraGameplayTags::Get().DamageTypesToResistances)
	{
		const FGameplayTag DamageType = Pair.Key;
		const FGameplayTag ResistanceTag = Pair.Value;

		checkf(AuraDamageStatics().TagsToCaptureDefs.Contains(ResistanceTag), TEXT("TagsToCaptureDefs doesn't contain Tag: [%s] in ExecCalc_Damage"), *ResistanceTag.ToString())
		const FGameplayEffectAttributeCaptureDefinition CaptureDef = AuraDamageStatics().TagsToCaptureDefs[ResistanceTag];
		
		float DamageTypeValue = Spec.GetSetByCallerMagnitude(Pair.Key);

		float Resistance = 0.f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(CaptureDef, EvaluationParameters, Resistance);
		Resistance = FMath::Clamp(Resistance, 0.f, 100.f);
		
		DamageTypeValue *= (100.f - Resistance) / 100.f;
		Damage += DamageTypeValue; // SetCallerByMagnitude has default 0 if tag not found, so this is safe
	}

	// Capture BlockChance on Target, and Determine if there was a successful Block
	float TargetBlockChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		DamageStatics().BlockChanceDef,
		EvaluationParameters,
		TargetBlockChance
	);
	TargetBlockChance = FMath::Max<float>(TargetBlockChance, 0.f);

	// If Block, halve the damage, setting the EffectContextHandle to know it is Blocked
	const bool bBlocked = FMath::RandRange(1, 100) <= TargetBlockChance;
	UAuraAbilitySystemLibrary::SetIsBlockedHit(EffectContextHandle, bBlocked);
	Damage = bBlocked ? Damage * 0.5f : Damage;

	// Capture Target Armor and Source Armor Pen and Determine how much Armor is Ignored
	float TargetArmor = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		DamageStatics().ArmorDef,
		EvaluationParameters,
		TargetArmor
	);
	TargetArmor = FMath::Max<float>(TargetArmor, 0.f);

	float SourceArmorPen = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		DamageStatics().ArmorPenDef,
		EvaluationParameters,
		SourceArmorPen
	);
	SourceArmorPen = FMath::Max<float>(SourceArmorPen, 0.f);

	// Armor Pen ignores a percentage of Target's Armor 
	// 2 points of ArmorPen required to ignore 1 point of Armor
	const FRealCurve* ArmorPenCurve = CharacterClassInfo->DamageCalcCoefficients->FindCurve(FName("ArmorPen"), FString());
	const float ArmorPenCoefficient = ArmorPenCurve->Eval(SourceCombatInterface->GetPlayerLevel());
	const float EffectiveArmor = TargetArmor * (100 - SourceArmorPen * ArmorPenCoefficient) / 100.f;
	// Reduces damage taken by a percent
	const FRealCurve* EffectiveArmorCurve = CharacterClassInfo->DamageCalcCoefficients->FindCurve(FName("EffectiveArmor"), FString());
	const float EffectiveArmorCoefficient = EffectiveArmorCurve->Eval(TargetCombatInterface->GetPlayerLevel());
	Damage *= (100 - EffectiveArmor * EffectiveArmorCoefficient) / 100.f;

	// Capture Critical Hit - Chance and Damage on Source, Resistance on Target
	float SourceCriticalHitChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		DamageStatics().CriticalHitChanceDef,
		EvaluationParameters,
		SourceCriticalHitChance
	);
	SourceCriticalHitChance = FMath::Max<float>(SourceCriticalHitChance, 0.f);

	float SourceCriticalHitDamage = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		DamageStatics().CriticalHitDamageDef,
		EvaluationParameters,
		SourceCriticalHitDamage
	);
	SourceCriticalHitDamage = FMath::Max<float>(SourceCriticalHitDamage, 0.f);

	float TargetCriticalHitResistance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		DamageStatics().CriticalHitResistanceDef,
		EvaluationParameters,
		TargetCriticalHitResistance
	);
	TargetCriticalHitResistance = FMath::Max<float>(TargetCriticalHitResistance, 0.f);

	// Critical Hit Resistance Effectiveness, reduces Critical Hit Chance by a percent
	const FRealCurve* CriticalHitResistanceCurve = CharacterClassInfo->DamageCalcCoefficients->FindCurve(FName("CriticalHitResistance"), FString());
	const float CriticalHitResistanceCoefficient = CriticalHitResistanceCurve->Eval(TargetCombatInterface->GetPlayerLevel());
	const float EffectiveCriticalHitChance = SourceCriticalHitChance - (TargetCriticalHitResistance * CriticalHitResistanceCoefficient);

	// If Crit, 1.5x the Damage + Bonus, setting the EffectContextHandle to know it is a Critical
	const bool bCritical = FMath::RandRange(1, 100) < EffectiveCriticalHitChance;
	UAuraAbilitySystemLibrary::SetIsCriticalHit(EffectContextHandle, bCritical);
	Damage = bCritical ? (Damage * 1.5f) + SourceCriticalHitDamage : Damage;

	// Outputting Damage
	const FGameplayModifierEvaluatedData EvaluatedData(
		UAuraAttributeSet::GetIncomingDamageAttribute(), 
		EGameplayModOp::Additive, 
		Damage
	);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}
