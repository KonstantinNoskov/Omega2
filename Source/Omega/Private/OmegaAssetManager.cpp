#include "OmegaAssetManager.h"

#include "OmegaGameplayTags.h"

UOmegaAssetManager& UOmegaAssetManager::Get()
{
	check(GEngine)
	
	UOmegaAssetManager* OmegaAssetManager = Cast<UOmegaAssetManager>(GEngine->AssetManager);
	return *OmegaAssetManager;
}

void UOmegaAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FOmegaGameplayTags::InitializeNativeGameplayTags();
	FOmegaGameplayTags::StoreAnimationTags();
}
