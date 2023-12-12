// Druid Mechanics - Aura Course

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "AuraPlayerState.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

UCLASS()
class AURA_API AAuraPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	AAuraPlayerState();

	/** <IAbilitySystemInterface> */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	/** </IAbilitySystemInterface> */
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

protected:
	UPROPERTY(VisibleAnywhere, Category = "Combat")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, Category = "Combat")
	TObjectPtr<UAttributeSet> AttributeSet;
};
