#include "UI/Widgets/DamageTextComponent.h"


UDamageTextComponent::UDamageTextComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetWorldRotation(FRotator(0.f, 90.f, 0.f));
	SetWorldLocation(FVector(0, 2.f, 0));
	
}


