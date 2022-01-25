#pragma once
#include <GameEngineActor.h>
#include <GameEngineFSM.h>
#include <GameEngineMath.h>
#include "WeaponBase.h"

class GameEngineRenderer;
class Worm;
class UziBullet : public WeaponBase
{
public:


public:
	UziBullet(); // default constructer ����Ʈ ������
	~UziBullet(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	UziBullet(const UziBullet& _other) = delete; // default Copy constructer ����Ʈ ���������
	UziBullet(UziBullet&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	UziBullet& operator=(const UziBullet& _other) = delete; // default Copy operator ����Ʈ ���� ������
	UziBullet& operator=(const UziBullet&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

private:
	const int CAPACITY = 25;
	int curShot_;
	GameEngineMath::Random randomGenerator_;

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

private:
	GameEngineRenderer* mainRender_;
	GameEngineCollision* fireCollision_;
	Worm* parent_;
	float4 direction_;
	float4 scanPos_;
	float4 parentForward_;

	bool bLeft_;
	bool bGround_;
	bool bBackJump_;
	
	float degree_;
	float deltaTime_;

public:
	void SetUziBulletShotBox(float4 _direction)
	{
		direction_ = _direction;
	}

	void SetParentWorm(Worm* _worm)
	{
		parentWorm_ = _worm;
	}

};

