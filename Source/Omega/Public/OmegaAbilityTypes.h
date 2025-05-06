#pragma once

#include "GameplayEffectTypes.h"
#include "OmegaAbilityTypes.generated.h"


USTRUCT(BlueprintType)
struct FOmegaGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()
	
	virtual UScriptStruct* GetScriptStruct() const override;
	virtual bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess) override;

	virtual FOmegaGameplayEffectContext* Duplicate() const override;


	// Getters
	FORCEINLINE bool IsImmune() const		{ return bImmune; }
	FORCEINLINE bool IsParried() const		{ return bParried; }
	FORCEINLINE bool IsBlocked() const		{ return bBlocked; }
	
	// Setters
	void SetIsImmune(bool InbImmune)		{ bImmune = InbImmune; }
	void SetIsParried(bool InbParried)		{ bImmune = InbParried; }
	void SetIsBlocked(bool InbBlocked)		{ bBlocked = InbBlocked; }

protected:

	UPROPERTY()
	bool bImmune = false;

	UPROPERTY()
	bool bParried = false;

	UPROPERTY()
	bool bBlocked = false;
};

template<>
struct TStructOpsTypeTraits<FOmegaGameplayEffectContext> : TStructOpsTypeTraitsBase2<FOmegaGameplayEffectContext>
{
	enum
	{
		WithCopy = true,
		WithNetSerializer = true
	};
};