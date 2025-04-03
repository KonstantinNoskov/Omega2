#include "Interfaces/CombatInterface.h"


int32 ICombatInterface::GetPlayerLevel() const { return 0; }

FVector ICombatInterface::GetProjectileSpawnSocket(bool& bSocketExist)
{
	return FVector();
}
