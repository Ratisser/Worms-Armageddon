#pragma once
#include <GameEngineActor.h>
// �з� : 
// �뵵 : 
// ���� : 
class UziBullet;
class Uzi : public GameEngineActor
{
private:	// member Var
	UziBullet* curBullet_;
	const int CAPACITY = 25;
	int curShot_;

public:
	Uzi(); // default constructer ����Ʈ ������
	~Uzi(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	Uzi(const Uzi& _other) = delete; // default Copy constructer ����Ʈ ���������
	Uzi(Uzi&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	Uzi& operator=(const Uzi& _other) = delete; // default Copy operator ����Ʈ ���� ������
	Uzi& operator=(const Uzi&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:

};

