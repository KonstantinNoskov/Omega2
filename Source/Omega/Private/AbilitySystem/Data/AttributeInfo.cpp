#include "AbilitySystem/Data/AttributeInfo.h"

FOmegaAttributeInfo UAttributeInfo::FindAttributeInfoByTag(const FGameplayTag& AttributeTag, bool bLogNotFound)
{
	// Loop through Primary Attributes
	for (auto Attribute : PrimaryAttributesInfo)
	{	
		if (Attribute.Value.AttributeTag.MatchesTagExact(AttributeTag))
		{
			return Attribute.Value;
		}
	}

	// Loop through Secondary Attributes
	for (auto Attribute : SecondaryAttributesInfo)
	{	
		if (Attribute.Value.AttributeTag.MatchesTagExact(AttributeTag))
		{
			return Attribute.Value;
		}
	}

	// Loop through Tertiary Attributes
	for (auto Attribute : TertiaryAttributesInfo)
	{	
		if (Attribute.Value.AttributeTag.MatchesTagExact(AttributeTag))
		{
			return Attribute.Value;
		}
	}
	
	if (bLogNotFound)
		{ UE_LOG(LogTemp, Error, TEXT("[%hs] GameplayTagInfo not found by Tag '[%s]'"), __FUNCTION__, *AttributeTag.ToString())	}

	return FOmegaAttributeInfo();
}
