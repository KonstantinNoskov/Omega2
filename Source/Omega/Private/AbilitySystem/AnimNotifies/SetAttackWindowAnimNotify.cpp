#include "AbilitySystem/AnimNotifies/SetAttackWindowAnimNotify.h"

#include "PaperZDAnimInstance.h"
#include "Interfaces/CombatInterface.h"


void USetAttackWindowAnimNotify::OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	if (!OwningInstance) return;
	
	if (OwningInstance->GetOwningActor()->Implements<UCombatInterface>())
	{
		ICombatInterface::Execute_SetIsAttackWindowOpened(OwningInstance->GetOwningActor(), ComboWindowOpenedTag);
	}
}
