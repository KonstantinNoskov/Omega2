#include "AbilitySystem/Tasks/ProjectileDirectionTask.h"

UProjectileDirectionTask* UProjectileDirectionTask::CreateProjectileDirection(UGameplayAbility* OwningAbility)
{
	UProjectileDirectionTask* MyObj = NewAbilityTask<UProjectileDirectionTask>(OwningAbility);

	return MyObj;
}

void UProjectileDirectionTask::Activate()
{
	APlayerController* PC = Ability->GetCurrentActorInfo()->PlayerController.Get();

	const FVector Direction = Ability->GetAvatarActorFromActorInfo()->GetActorForwardVector();

	ProjectileDirectionSet.Broadcast(Direction);
	
}
