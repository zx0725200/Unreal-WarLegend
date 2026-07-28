#pragma once
#include "CoreMinimal.h"

namespace Constant
{
	inline const TCHAR* SaveData = TEXT("SaveData");
	
#pragma region CharacterSetting
	constexpr float BattleArmLength = 500.f;
	constexpr float TopDownArmLength = 800.f;
	constexpr float BattleMaxWalkSpeed = 400.f;
	constexpr float BattleRotationYawRate = 500.f;
	constexpr float BattleBrakingDeceleration = 2000.f;
	constexpr float CityRotationYawRate = 640.f;
	
	const FRotator TopDownArmRotation = FRotator(-60.f, 0.f, 0.f);
	const FVector PlayerSpawnLocation = FVector(-2535.000000,-2410.000000,782.012612);
#pragma endregion
	
#pragma region Monster
	constexpr int32 MaxLapCount = 5;
	constexpr int32 MonsterSpawnNum = 10;
	constexpr float MonsterAcceptRange = 50;
	constexpr float MonsterSpawnInterval = 3.0f;
#pragma endregion
	
	constexpr float DungeonExitTime = 0.5f;

#pragma region DungeonEntrySequence
	constexpr float DungeonEntryDropHeight = 900.f; // 아레나 상공에서 낙하를 시작할 높이
	constexpr float DungeonFadeOutTime = 0.3f;		// 검정으로 어두워지는 시간
	constexpr float DungeonFadeInTime = 0.6f;		// 밝아지며 낙하하는 시간
#pragma endregion

	constexpr float MapSize = 1800.0f;
	constexpr int32 PageSize = 5;
	constexpr int32 One = 1;
	constexpr int32 Ten = 10;
	constexpr int32 All = 30;
}
