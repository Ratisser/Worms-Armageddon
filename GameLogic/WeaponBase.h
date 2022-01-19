#pragma once

#include <GameEngineActor.h>

class WeaponBase : public GameEngineActor
{
private:	// member Var

public:
	WeaponBase(); // default constructer 디폴트 생성자
	~WeaponBase(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	WeaponBase(const WeaponBase& _other) = delete; // default Copy constructer 디폴트 복사생성자
	WeaponBase(WeaponBase&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	WeaponBase& operator=(const WeaponBase& _other) = delete; // default Copy operator 디폴트 대입 연산자
	WeaponBase& operator=(const WeaponBase&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:

};

