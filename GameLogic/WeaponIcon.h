#pragma once
#include <GameEngineActor.h>
#include "eItemList.h"

#define WEAPON_MAX 65	// 무기 최대 개수

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineRenderer;
class GameEngineCollision;
class WeaponIcon : public GameEngineActor
{
private:
	int indexX_;
	int indexY_;

private:
	bool active_;

private:	// member Var
	std::string weaponname_;
	eItemList weapontype_;

private:
	float4 activetargetpos_;
	float4 disabletargetpos_;

private:
	bool moving_;
	float movingspeed;
	float4 movepos_;

private:
	GameEngineRenderer* mainrenderer_;
	GameEngineRenderer* selectrenderer_;
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
	void SetWeaponName(const std::string& _Name);
	void SetWeaponType(eItemList _Type);
	void SetWeaponRenderPos(const float4& _DisableRenderPos, const float4& _ActiveRenderPos);
	void SetWeaponIndex(int _X, int _Y);

public:
	GameEngineCollision* GetCurIconCol() const;
	void SetActive(bool _Active);

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;
};

