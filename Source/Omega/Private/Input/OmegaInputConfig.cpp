#include "Input/OmegaInputConfig.h"

#include "OmegaTypes.h"

const UInputAction* UOmegaInputConfig::FindAbilityInputActionByTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	
	for (const FOmegaInputAction& Action : AbilityInputAction)
	{
		if (Action.InputAction && Action.InputTag == InputTag)
		{
			return Action.InputAction;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("[%hs] Can't find ability by tag"), __FUNCTION__)
	}

	return nullptr;
}
