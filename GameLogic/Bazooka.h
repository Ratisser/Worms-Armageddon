
#pragma once

#include <GameEngineActor.h>
#include <GameEngineFSM.h>

class GameEngineRenderer;
class Bazooka : public GameEngineActor
{
public:
	Bazooka();
	~Bazooka();

	Bazooka(const Bazooka& _other) = delete; // default Copy constructer 디폴트 복사생성자
	Bazooka(Bazooka&& _other) = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자

	Bazooka& operator=(const Bazooka& _other) = delete; // default Copy operator 디폴트 대입 연산자
	Bazooka& operator=(const Bazooka&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

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
	float4 speed_;
	float4 direction_;

	bool bLeft_;
	bool bGround_;
	bool bBackJump_;

	float deltaTime_;
};

