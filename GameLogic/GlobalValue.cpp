#include "GlobalValue.h"
#include "Worm.h"
std::string GlobalValue::CurPlayMap = "MapTrain";				// 현재 생성되는 맵이름(테스트중이므로 임시로 초기값 지정)
std::string GlobalValue::CurPlayColMap = "MapTrain_Ground";		// 현재 생성되는 맵타입의 충돌맵이름(테스트중이므로 임시로 초기값 지정)

std::unordered_map<std::string, float4> GlobalValue::MapMinMaxInfo = std::unordered_map<std::string, float4>();
