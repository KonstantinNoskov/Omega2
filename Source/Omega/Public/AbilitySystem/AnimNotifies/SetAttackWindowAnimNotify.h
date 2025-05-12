#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "PaperZDAnimNotify.h"
#include "SetAttackWindowAnimNotify.generated.h"


UCLASS()
class OMEGA_API USetAttackWindowAnimNotify : public UPaperZDAnimNotify
{
	GENERATED_BODY()

public:
	
	virtual void OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance = nullptr) const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bAttackWindowOpened = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag ComboWindowOpenedTag = FGameplayTag::EmptyTag;
};
