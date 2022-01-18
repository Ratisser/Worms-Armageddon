#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <GameEngineMath.h>

// �뵵 : �������� ����� ���� ����
// Ex) ��(����)��ȯ�� ���� ������ �Ѱ�����ϴ� ���� �����ؼ� ���
class Worm;
class GlobalValue
{
public:
	static std::string CurPlayMap;				// ���� �����Ǵ� ��(����ȭ�鿡�� ����)
	static std::string CurPlayColMap;		// ���� �����Ǵ� ��Ÿ���� �浹��(����ȭ�鿡�� ����)

	static std::unordered_map<std::string, float4> MapMinMaxInfo;
};

