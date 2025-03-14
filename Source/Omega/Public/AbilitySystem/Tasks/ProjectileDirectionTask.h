#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "ProjectileDirectionTask.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FProjectileDirectionSignature, const FVector&, Direction);

UCLASS()
class OMEGA_API UProjectileDirectionTask : public UAbilityTask
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (DisplayName = "ProjectileDirection", HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true"))
	static UProjectileDirectionTask* CreateProjectileDirection(UGameplayAbility* OwningAbility);

protected:
	
	virtual void Activate() override;

	UPROPERTY(BlueprintAssignable)
	FProjectileDirectionSignature ProjectileDirectionSet;


};
