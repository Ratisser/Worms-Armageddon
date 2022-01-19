#pragma once

#include <GameEngineActor.h>

class WeaponBase : public GameEngineActor
{
private:	// member Var

public:
	WeaponBase(); // default constructer ����Ʈ ������
	~WeaponBase(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	WeaponBase(const WeaponBase& _other) = delete; // default Copy constructer ����Ʈ ���������
	WeaponBase(WeaponBase&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	WeaponBase& operator=(const WeaponBase& _other) = delete; // default Copy operator ����Ʈ ���� ������
	WeaponBase& operator=(const WeaponBase&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:

};

