// Druid Mechanics - Aura Course


#include "AbilitySystem/Data/LevelUpInfo.h"

int32 ULevelUpInfo::FindLevelForXP(int32 InXP) const
{
	int32 Level = 1;
	bool bSearching = true;

	while (bSearching)
	{
		if (LevelUpInfo.Num() <= Level) return Level;

		if (InXP >= LevelUpInfo[Level].LevelUpReq)
		{
			++Level;
		}
		else
		{
			bSearching = false;
		}
	}
	
	return Level;
}
