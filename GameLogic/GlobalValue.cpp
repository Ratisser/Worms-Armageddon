#include "GlobalValue.h"
#include "Worm.h"
std::string GlobalValue::CurPlayMap = "MapTrain";				// ���� �����Ǵ� ���̸�(�׽�Ʈ���̹Ƿ� �ӽ÷� �ʱⰪ ����)
std::string GlobalValue::CurPlayColMap = "MapTrain_Ground";		// ���� �����Ǵ� ��Ÿ���� �浹���̸�(�׽�Ʈ���̹Ƿ� �ӽ÷� �ʱⰪ ����)

std::unordered_map<std::string, float4> GlobalValue::MapMinMaxInfo = std::unordered_map<std::string, float4>();
