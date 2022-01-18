#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <GameEngineMath.h>

// 용도 : 전역으로 사용할 값들 정의
// Ex) 씬(레벨)전환시 다음 레벨로 넘겨줘야하는 값을 정의해서 사용
class Worm;
class GlobalValue
{
public:
	static std::string CurPlayMap;				// 현재 생성되는 맵(대기실화면에서 셋팅)
	static std::string CurPlayColMap;		// 현재 생성되는 맵타입의 충돌맵(대기실화면에서 셋팅)

	static std::unordered_map<std::string, float4> MapMinMaxInfo;
};

