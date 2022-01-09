#pragma once
#include <GameEngineActor.h>

// 분류 :
// 용도 :
// 설명 :
class SonicActor : public GameEngineActor
{
private:	// member Var

public:		
	SonicActor(); // default constructer 디폴트 생성자
	~SonicActor(); // default destructer 디폴트 소멸자

public:		// delete constructer
	SonicActor(const SonicActor& _other) = delete; // default Copy constructer 디폴트 복사생성자
	SonicActor(SonicActor&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

public:		//delete operator
	SonicActor& operator=(const SonicActor& _other) = delete; // default Copy operator 디폴트 대입 연산자
	SonicActor& operator=(const SonicActor&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:		//member Func
};

