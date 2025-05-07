#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "OmegaAbilitySystemLibrary.generated.h"


UCLASS()
class OMEGA_API UOmegaAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	
	/**
	 * 
	 * @param ContextHandle
	 *
	 * @return true if attribute set is immune to a gameplay effect  
	 */
	UFUNCTION(BlueprintPure, Category = "Omega Ability System Library")
	static bool IsImmuneToEffect(const FGameplayEffectContextHandle& ContextHandle);

	/**
	 *	Set Immune to effect status
	 */
	UFUNCTION(BlueprintCallable, Category = "Omega Ability System Library")
	static void SetIsImmuneToEffect(UPARAM(ref) FGameplayEffectContextHandle& ContextHandle, bool bIsImmuneToEffect);

	/**
	 * @param ContextHandle
	 *
	 * @return true if 
	 */
	UFUNCTION(BlueprintPure, Category = "Omega Ability System Library")
	static bool IsBlockedEffect(const FGameplayEffectContextHandle& ContextHandle);

	/**
	 * @param ContextHandle
	 *
	 * @return true if 
	 */
	UFUNCTION(BlueprintPure, Category = "Omega Ability System Library")
	static bool IsParryEffect(const FGameplayEffectContextHandle& ContextHandle);


	
};


