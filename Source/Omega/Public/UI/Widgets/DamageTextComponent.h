#pragma once

#include "CoreMinimal.h"
#include "OmegaTypes.h"
#include "Components/WidgetComponent.h"
#include "DamageTextComponent.generated.h"


UCLASS()
class OMEGA_API UDamageTextComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:

	UDamageTextComponent();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetDamageText(const FDamageEffectContextData& DamageHandle);
};
