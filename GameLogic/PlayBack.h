#pragma once
#include <GameEngineActor.h>
// 분류 :
// 용도 :
// 설명 :
class PlayBack : public GameEngineActor
{
public:	// member Var
	static GameEngineCollision* MapCollision;

public:		
	PlayBack(); // default constructer 디폴트 생성자
	~PlayBack(); // default destructer 디폴트 소멸자

public:		// delete constructer
	PlayBack(const PlayBack& _other) = delete; // default Copy constructer 디폴트 복사생성자
	PlayBack(PlayBack&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

public:		//delete operator
	PlayBack& operator=(const PlayBack& _other) = delete; // default Copy operator 디폴트 대입 연산자
	PlayBack& operator=(const PlayBack&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:		//member Func
	void Start();
	void Render();
};

