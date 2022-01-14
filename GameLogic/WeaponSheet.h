#pragma once
#include <map>
#include <GameEngineActor.h>

#include "eItemList.h"

class GameEngineRenderer;
class GameEngineCollision;
class MouseObject;
class WeaponIcon;
class Weapon;
class WeaponSheet : public GameEngineActor
{
private:
	static bool weaponsheetactive_;

public:
	static bool isweaponsheet();

private:
	bool active_;
	bool prevstate_;

private:	// member Var
	GameEngineRenderer* mainrenderer;		// WeaponSheet(Temp) 렌더러
	
private: // 마우스충돌 관련
	MouseObject* mouseobject_;

private: // 무기아이콘 목록
	std::map<std::string, WeaponIcon*> weaponiconlist_;
	std::vector<std::string> weaponnamelist_;

private: // 실질적인 무기관리
	std::map<eItemList, Weapon*> weapon_;
	
private:
	float4 activetargetpos_;
	float4 disabletargetpos_;

private:
	bool moving_;
	float movingspeed;
	float4 movepos_;

public:
	WeaponSheet(); // default constructer 디폴트 생성자
	~WeaponSheet(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	WeaponSheet(const WeaponSheet& _other) = delete; // default Copy constructer 디폴트 복사생성자
	WeaponSheet(WeaponSheet&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	WeaponSheet& operator=(const WeaponSheet& _other) = delete; // default Copy operator 디폴트 대입 연산자
	WeaponSheet& operator=(const WeaponSheet&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

public:
	bool IsActive()
	{
		if (active_ == true)
		{
			return true;
		}

		return false;
	}

	void WeaponSheetActive();
	void SetRenderPos(const float4& _Active, const float4& _Disable);

public:
	void SetMouseObject();
	void SetIconName();
	void CreateIconDefaultPos();

public: // 플레이어가 들고있는 무기소유목록을 받아와서 무기아이콘목록생성
	void CreateWeaponIconList(const std::vector<eItemList>& _WeaponList);

public: // 실질적인 무기목록(관리용)관련
	Weapon* GetCruWeapon();
};

