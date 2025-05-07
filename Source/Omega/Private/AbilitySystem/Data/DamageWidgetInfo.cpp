#include "AbilitySystem/Data/DamageWidgetInfo.h"

const FDamageWidgetInfo& UDamageWidgetData::GetDamageWidgetInfoByTag(const FGameplayTag& DamageTag)
{
	return DamageWidgetDataMap[DamageTag];
}
