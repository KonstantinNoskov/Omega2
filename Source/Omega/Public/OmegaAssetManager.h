#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "OmegaAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class OMEGA_API UOmegaAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:

	static UOmegaAssetManager& Get();

	virtual void StartInitialLoading() override;
};
