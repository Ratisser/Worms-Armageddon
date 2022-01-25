#pragma once
#include <GameEngineActor.h>
// 분류 : 
// 용도 : 
// 설명 : 
class UziBullet;
class Uzi : public GameEngineActor
{
private:	// member Var
	UziBullet* curBullet_;
	const int CAPACITY = 25;
	int curShot_;

public:
	Uzi(); // default constructer 디폴트 생성자
	~Uzi(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	Uzi(const Uzi& _other) = delete; // default Copy constructer 디폴트 복사생성자
	Uzi(Uzi&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	Uzi& operator=(const Uzi& _other) = delete; // default Copy operator 디폴트 대입 연산자
	Uzi& operator=(const Uzi&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:

};

