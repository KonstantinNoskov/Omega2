#include "AbilitySystem/Data/DamageWidgetInfo.h"

const FColor& UDamageWidgetData::GetDamageTypeColorByTag(const FGameplayTag& GameplayTag)
{
	return DamageTypeColorsMap.Contains(GameplayTag) ? DamageTypeColorsMap[GameplayTag] : FColor::Black;
}
