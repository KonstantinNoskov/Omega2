#include "AbilitySystem/Data/CharacterDefaultInfo.h"

const FCharacterTypeDefaultInfo& UCharacterDefaultInfo::GetClassDefaultInfo(const FGameplayTag& CharacterClass)
{
	return  CharacterClassInformation.FindChecked(CharacterClass);
}
