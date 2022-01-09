#pragma once
#include <GameEngineActor.h>
#include <GameEngineFSM.h>

// 분류 :
// 용도 :
// 설명 :
class GameEngineCollision;
class Monster : public GameEngineActor
{
public:
	GameEngineCollision* MonsterBodyCollision;


public:		
	Monster(); // default constructer 디폴트 생성자
	~Monster(); // default destructer 디폴트 소멸자

public:		// delete constructer
	Monster(const Monster& _other) = delete; // default Copy constructer 디폴트 복사생성자
	Monster(Monster&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

public:		//delete operator
	Monster& operator=(const Monster& _other) = delete; // default Copy operator 디폴트 대입 연산자
	Monster& operator=(const Monster&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:		//member Func
	void Start() override;
	void Collision() override;
	void Render() override; 
};

