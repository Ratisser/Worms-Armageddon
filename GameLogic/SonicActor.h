#pragma once
#include <GameEngineActor.h>

// �з� :
// �뵵 :
// ���� :
class SonicActor : public GameEngineActor
{
private:	// member Var

public:		
	SonicActor(); // default constructer ����Ʈ ������
	~SonicActor(); // default destructer ����Ʈ �Ҹ���

public:		// delete constructer
	SonicActor(const SonicActor& _other) = delete; // default Copy constructer ����Ʈ ���������
	SonicActor(SonicActor&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

public:		//delete operator
	SonicActor& operator=(const SonicActor& _other) = delete; // default Copy operator ����Ʈ ���� ������
	SonicActor& operator=(const SonicActor&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:		//member Func
};

