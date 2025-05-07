#include "UI/Widgets/DamageTextComponent.h"


UDamageTextComponent::UDamageTextComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetUsingAbsoluteRotation(true);
	SetWorldRotation(FRotator(0.f,90.f,0.f));
}

