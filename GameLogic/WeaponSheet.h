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
	GameEngineRenderer* mainrenderer;		// WeaponSheet(Temp) ������
	
private: // ���콺�浹 ����
	MouseObject* mouseobject_;

private: // ��������� ���
	std::map<std::string, WeaponIcon*> weaponiconlist_;
	std::vector<std::string> weaponnamelist_;

private: // �������� �������
	std::map<eItemList, Weapon*> weapon_;
	
private:
	float4 activetargetpos_;
	float4 disabletargetpos_;

private:
	bool moving_;
	float movingspeed;
	float4 movepos_;

public:
	WeaponSheet(); // default constructer ����Ʈ ������
	~WeaponSheet(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	WeaponSheet(const WeaponSheet& _other) = delete; // default Copy constructer ����Ʈ ���������
	WeaponSheet(WeaponSheet&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	WeaponSheet& operator=(const WeaponSheet& _other) = delete; // default Copy operator ����Ʈ ���� ������
	WeaponSheet& operator=(const WeaponSheet&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

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

public: // �÷��̾ ����ִ� ������������ �޾ƿͼ� ��������ܸ�ϻ���
	void CreateWeaponIconList(const std::vector<eItemList>& _WeaponList);

public: // �������� ������(������)����
	Weapon* GetCruWeapon();
};

