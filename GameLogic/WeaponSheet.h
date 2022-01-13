#pragma once
#include <map>
#include <GameEngineActor.h>

class GameEngineRenderer;
class GameEngineCollision;
class MouseObject;
class WeaponIcon;
class Weapon;
class WeaponSheet : public GameEngineActor
{
private:
	bool active_;
	bool prevstate_;

private:	// member Var
	GameEngineRenderer* mainrenderer;		// WeaponSheet(Temp) ������
	GameEngineCollision* maincollision_;	// WeaponSheet(Temp) �浹ü
	
private: // ���콺�浹 ����
	MouseObject* mouseobject_;

private: // ������ ���
	std::vector<WeaponIcon*> WeaponList_;

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
	virtual void Collision() override;
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

	void WeaponSheetActive()
	{
		if (false == active_)
		{
			active_ = true;
		}
		else
		{
			active_ = false;
		}
	}

public: // �÷��̾ ����ִ� ������������ �޾ƿͼ� ��������ܸ�ϻ���
	void CreateWeaponIconList(const std::map<std::string, Weapon*>& _WeaponList);

};

