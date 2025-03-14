#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "OmegaHUD.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
struct FWidgetControllerParams;
class UOverlayWidgetController;
class UOmegaUserWidget;

UCLASS()
class OMEGA_API AOmegaHUD : public AHUD
{
	GENERATED_BODY()

protected:
	
	virtual void BeginPlay() override;
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& InParams);

public:

	UFUNCTION()
	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

	
	UPROPERTY()
	TObjectPtr<UOmegaUserWidget> OverlayWidget;

private:

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOmegaUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;


};
