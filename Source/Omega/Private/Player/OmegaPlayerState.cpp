#include "Player/OmegaPlayerState.h"

#include "AbilitySystem/OmegaAbilitySystemComponent.h"
#include "AbilitySystem/OmegaAttributeSet.h"

AOmegaPlayerState::AOmegaPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UOmegaAbilitySystemComponent>("Omega Ability System");
	AttributeSet = CreateDefaultSubobject<UOmegaAttributeSet>("Omega Attribute Set");
}
