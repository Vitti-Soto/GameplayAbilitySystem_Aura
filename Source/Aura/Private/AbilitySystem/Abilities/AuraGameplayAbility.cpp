// Druid Mechanics - Aura Course


#include "AbilitySystem/Abilities/AuraGameplayAbility.h"
#include "AbilitySystem/AuraAttributeSet.h"

FString UAuraGameplayAbility::GetDescription(int32 Level)
{
    return FString::Printf(TEXT("<Default>%s, </><Level>%d</>"), L"Default Ability Name - LoremIpsum LoremIpsum LoremIpsum LoremIpsum LoremIpsum LoremIpsum LoremIpsum LoremIpsum LoremIpsum LoremIpsum LoremIpsum", Level);
}

FString UAuraGameplayAbility::GetNextLevelDescription(int32 Level)
{
    return FString::Printf(TEXT("<Default>Next Level, </><Level>%d</> \n<Default>Causes much more damage.</>"), Level);
}

FString UAuraGameplayAbility::GetLockedDescription(int32 LevelReq)
{
    return FString::Printf(TEXT("<Default>Spell locked until Level: </><Level>%d</>"), LevelReq);
}

float UAuraGameplayAbility::GetManaCost(float InLevel) const
{
    float ManaCost = 0;

    if (const UGameplayEffect* CostEffect = GetCostGameplayEffect())
    {
        for (FGameplayModifierInfo Mod : CostEffect->Modifiers)
        {
            if (Mod.Attribute == UAuraAttributeSet::GetManaAttribute())
            {
                Mod.ModifierMagnitude.GetStaticMagnitudeIfPossible(InLevel, ManaCost);
                break;
            }
        }
    }

    return ManaCost;
}

float UAuraGameplayAbility::GetCooldown(float InLevel) const
{
    float Cooldown = 0;

    if (const UGameplayEffect* CooldownEffect = GetCooldownGameplayEffect())
    {
        CooldownEffect->DurationMagnitude.GetStaticMagnitudeIfPossible(InLevel, Cooldown);
    }

    return Cooldown;
}
