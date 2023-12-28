// Druid Mechanics - Aura Course

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "AuraCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()
	
public:
	AAuraCharacter();

	/** <ACharacter> */
	virtual void PossessedBy(AController* NewController) override;
	/** </ACharacter> */
	/** <APawn> */
	virtual void OnRep_PlayerState() override;
	/** </APawn> */

	/** <ICombatInterface> */
	virtual int32 GetPlayerLevel() override;
	/** </ICombatInterface> */

	virtual void InitAbilityActorInfo() override;

private:
	
};
