#pragma once
#include <map>
// �з� : 
// �뵵 : 
// ���� : 
class Petroleum;
class PetroleumManager
{
private:	// member Var

public:
	PetroleumManager(); // default constructer ����Ʈ ������
	~PetroleumManager(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	PetroleumManager(const PetroleumManager& _other) = delete; // default Copy constructer ����Ʈ ���������
	PetroleumManager(PetroleumManager&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	PetroleumManager& operator=(const PetroleumManager& _other) = delete; // default Copy operator ����Ʈ ���� ������
	PetroleumManager& operator=(const PetroleumManager&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

private:


public:


};

