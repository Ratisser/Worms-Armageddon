#pragma once

#include <GameEngineActor.h>
#include <GameEngineFSM.h>

class GameEngineRenderer;
class Worm : public GameEngineActor
{
public:
	Worm();
	~Worm();

	Worm(const Worm& _other) = delete; // default Copy constructer 디폴트 복사생성자
	Worm(Worm&& _other) = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자

	Worm& operator=(const Worm& _other) = delete; // default Copy operator 디폴트 대입 연산자
	Worm& operator=(const Worm&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

private:
	void initRenderer();
	void initInput();
	void initCollision();
	void initState();

	void addGravity(float _deltaTime);

	void normalMove(float _deltaTime);

private:
	StateInfo startIdle(StateInfo _state);
	StateInfo updateIdle(StateInfo _state);

	StateInfo startWalk(StateInfo _state);
	StateInfo updateWalk(StateInfo _state);

	StateInfo startJumpReady(StateInfo _state);
	StateInfo updateJumpReady(StateInfo _state);

	StateInfo startJump(StateInfo _state);
	StateInfo updateJump(StateInfo _state);


private:
	const float MOVE_SPEED = 100.f;
	const float GRAVITY_POWER = 600.f;
	const float BOTTOM_PIVOT = 14.f;
private:
	GameEngineRenderer* mainRender_;
	GameEngineCollision* bottomCenterCollision_;
	GameEngineCollision* groundCheckCollision_;

	GameEngineFSM<Worm> state_;

	float4 accelation_;
	float4 speed_;
	float4 direction_;

	bool bLeft_;
	bool bGround_;

	float deltaTime_;
};

