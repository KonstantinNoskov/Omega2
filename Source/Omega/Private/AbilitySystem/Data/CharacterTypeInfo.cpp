#include "AbilitySystem/Data/CharacterTypeInfo.h"

const FCharacterTypeDefaultInfo& UCharacterTypeInfo::GetClassDefaultInfo(const FGameplayTag& CharacterClass)
{
	return  CharacterClassInformation.FindChecked(CharacterClass);
}
