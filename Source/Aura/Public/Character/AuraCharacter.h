// Druid Mechanics - Aura Course

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/PlayerInterface.h"
#include "AuraCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UNiagaraComponent;

/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase, public IPlayerInterface
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

	/** <IPlayerInterface> */
	virtual void AddToXP_Implementation(int32 InXP) override;
	virtual int32 GetXP_Implementation() const override;
	virtual int32 GetAttributePointsReward_Implementation(int32 Level) const override;
	virtual int32 GetSpellPointsReward_Implementation(int32 Level) const override;
	virtual void LevelUp_Implementation() override;
	virtual int32 FindLevelForXP_Implementation(int32 InXP) const override;
	virtual void AddToPlayerLevel_Implementation(int32 InLevel) override;
	virtual void AddAttributePoints_Implementation(int32 InAttributePoints) override;
	virtual void AddSpellPoints_Implementation(int32 InSpellPoints) override;
	/** </IPlayerInterface> */

	/** <ICombatInterface> */
	virtual int32 GetPlayerLevel_Implementation() override;
	/** </ICombatInterface> */

	virtual void InitAbilityActorInfo() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UNiagaraComponent> LevelUpNiagaraComponent;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> TopDownCameraComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> CameraBoom;

	UFUNCTION(NetMulticast, Reliable)
	void MulticastLevelUpParticles() const;
};
