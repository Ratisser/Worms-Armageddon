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
	GameEngineRenderer* MainRenderer_;		// WeaponSheet(Temp) 렌더러
	GameEngineCollision* MainCollision_;	// WeaponSheet(Temp) 충돌체
	
private: // 마우스충돌 관련
	float4 MousePos_;

private:
	float4 ActiveTargetPos_;
	float4 DisableTargetPos_;

private:
	bool Moving_;
	float MovingSpeed;
	float4 MovePos_;

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
};

