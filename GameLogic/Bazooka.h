
#pragma once

#include <GameEngineActor.h>
#include <GameEngineFSM.h>

#include "WeaponBase.h"

class GameEngineRenderer;
class Bazooka : public WeaponBase
{
public:
	Bazooka();
	~Bazooka();

	Bazooka(const Bazooka& _other) = delete; // default Copy constructer ����Ʈ ���������
	Bazooka(Bazooka&& _other) = delete; // default RValue Copy constructer ����Ʈ RValue ���������

	Bazooka& operator=(const Bazooka& _other) = delete; // default Copy operator ����Ʈ ���� ������
	Bazooka& operator=(const Bazooka&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

private:
	const float MOVE_SPEED = 100.f;
	const float GRAVITY_POWER = 600.f;
	const float BOTTOM_PIVOT = 14.f;

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

private:
	GameEngineRenderer* mainRender_;
	GameEngineCollision* groundCheckCollision_;

	float4 accelation_;
	float4 direction_;
	float4 speed_;

	bool bLeft_;
	bool bGround_;
	bool bBackJump_;

	float deltaTime_;
	float distance_; // �̵� �Ÿ� : 0�� �Ǹ� �ٷ� ����
	float power_; // ������ ���ϴ� ��

public:
	void SetBazooka(float4 _direction, float4 _speed, float _distance, float _power)
	{
		direction_ = _direction;
		speed_ = _speed;
		distance_ = _distance;
		power_ = _power;
	}
};

