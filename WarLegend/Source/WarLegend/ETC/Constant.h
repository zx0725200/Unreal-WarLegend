#pragma once
#include "CoreMinimal.h"

namespace Constant
{
	inline const TCHAR* SaveData = TEXT("SaveData");
	
#pragma region Monster
	constexpr int32 MaxLapCount = 5;
	constexpr int32 MonsterSpawnNum = 10;
	constexpr float MonsterAcceptRange = 50;
	constexpr float MonsterSpawnInterval = 3.0f;
#pragma endregion
	
	constexpr float DungeonExitTime = 0.5f;
	constexpr float MapSize = 1800.0f;
}
