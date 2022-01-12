#pragma once
#include <GameEngineActor.h>



class GameEngineRenderer;
class GameEngineCollision;
class WeaponSheet : public GameEngineActor
{
private:
	static bool Active_;

public:
	static bool IsActive()
	{
		if (Active_ == true)
		{
			return true;
		}

		return false;
	}

	static void WeaponSheetActive()
	{
		if (false == Active_)
		{
			Active_ = true;
		}
		else
		{
			Active_ = false;
		}
	}

private:	// member Var
	GameEngineRenderer* MainRenderer_;		// WeaponSheet(Temp) ������
	GameEngineCollision* MainCollision_;	// WeaponSheet(Temp) �浹ü
	
private: // ���콺�浹 ����
	float4 MousePos_;

private:
	float4 ActiveTargetPos_;
	float4 DisableTargetPos_;

private:
	bool Moving_;
	float MovingSpeed;
	float4 MovePos_;

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
};

