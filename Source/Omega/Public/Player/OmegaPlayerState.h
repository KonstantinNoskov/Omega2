#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "OmegaPlayerState.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;

UCLASS()
class OMEGA_API AOmegaPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:

	AOmegaPlayerState();

	FORCEINLINE virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override		{ return AbilitySystemComponent; }
	FORCEINLINE UAttributeSet* GetAttributeSet() const											{ return AttributeSet; }
	FORCEINLINE int32 GetPlayerLevel() const													{ return Level; } 

private:
	
	UPROPERTY(VisibleAnywhere)
	int32 Level = 1;


protected:
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
};
