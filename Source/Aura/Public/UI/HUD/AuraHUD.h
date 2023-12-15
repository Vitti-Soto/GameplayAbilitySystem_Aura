// Druid Mechanics - Aura Course

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

class UAuraUserWidget;
class UOverlayWidgetController;
class UAbilitySystemComponent;
class UAttributeSet;
struct FWidgetControllerParams;

UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams WCParams);
	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

	UPROPERTY(VisibleAnywhere, Category = "Overlay")
	TObjectPtr<UAuraUserWidget> OverlayWidget;

protected:

private:
	UPROPERTY(EditAnywhere, Category = "Overlay")
	TSubclassOf<UAuraUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere, Category = "Overlay")
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
};
