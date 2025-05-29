#include "AbilitySystem/Data/CharacterDefaultInfo.h"

const FCharacterTypeInfo& UCharacterDefaultInfo::GetCharacterTypeInfo(const FGameplayTag& CharacterTypeClass)
{
	return  CharacterTypeInfo.FindChecked(CharacterTypeClass);
}
