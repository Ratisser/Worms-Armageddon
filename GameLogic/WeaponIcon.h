#pragma once
#include <GameEngineActor.h>
#include "eItemList.h"

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineRenderer;
class GameEngineCollision;
class WeaponIcon : public GameEngineActor
{
private:	// member Var
	std::string itemname_;
	eItemList itemtype_;
	int indexX_;
	int indexY_;
	int index_;
	float4 renderpos_;

private:
	GameEngineRenderer* mainrenderer_;
	GameEngineCollision* maincollision_;

public:
	WeaponIcon(); // default constructer 디폴트 생성자
	~WeaponIcon(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	WeaponIcon(const WeaponIcon& _other) = delete; // default Copy constructer 디폴트 복사생성자
	WeaponIcon(WeaponIcon&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	WeaponIcon& operator=(const WeaponIcon& _other) = delete; // default Copy operator 디폴트 대입 연산자
	WeaponIcon& operator=(const WeaponIcon&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;
};

