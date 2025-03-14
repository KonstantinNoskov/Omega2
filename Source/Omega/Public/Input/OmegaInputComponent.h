#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "OmegaInputConfig.h"
#include "OmegaInputComponent.generated.h"


struct FOmegaInputAction;
class UOmegaInputConfig;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class OMEGA_API UOmegaInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	
	UOmegaInputComponent();

	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
	void BindAbilityActions(const UOmegaInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, HeldFuncType HeldFunc, ReleasedFuncType ReleasedFunc);
	
};

template <class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
void UOmegaInputComponent::BindAbilityActions(const UOmegaInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, HeldFuncType HeldFunc, ReleasedFuncType ReleasedFunc)
{
	check(InputConfig)

	for (const FOmegaInputAction& Action : InputConfig->AbilityInputAction)
	{
		if (!Action.InputAction || !Action.InputTag.IsValid()) return;
		
		// Pressed
		if (PressedFunc)
		{
			BindAction(Action.InputAction, ETriggerEvent::Started, Object, PressedFunc, Action.InputTag);
		}

		// Held
		if (HeldFunc)
		{
			BindAction(Action.InputAction, ETriggerEvent::Triggered, Object, HeldFunc, Action.InputTag);
		}

		// Released
		if (ReleasedFunc)
		{
			BindAction(Action.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, Action.InputTag);
		}
	}
}

