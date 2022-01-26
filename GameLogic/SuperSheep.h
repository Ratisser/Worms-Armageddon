#pragma once

#include <GameEngineActor.h>
#include <GameEngineFSM.h>

class GameEngineCollision;
class GameEngineRenderer;
class Worm;
class SuperSheep : public GameEngineActor
{
public:
	SuperSheep();
	~SuperSheep();

	SuperSheep(const SuperSheep& _other) = delete;
	SuperSheep(SuperSheep&& _other) = delete;

	SuperSheep& operator=(const SuperSheep& _other) = delete;
	SuperSheep& operator=(const SuperSheep&& _other) = delete;

public:
	// GameEngineActor을(를) 통해 상속됨
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

public:
	void Initialize(Worm* _parentWorm, bool _bLeft);

private:
	void addGravity();
	void normalMove();

private:
	const float GRAVITY_POWER = 800.f;
	const float BOTTOM_PIVOT = 12.f;
	const float JUMP_DELAY = 1.5f;

private:
	StateInfo startIdle(StateInfo _state);
	StateInfo updateIdle(StateInfo _state);

	StateInfo startWalk(StateInfo _state);
	StateInfo updateWalk(StateInfo _state);

	StateInfo startExplosion(StateInfo _state);
	StateInfo updateExplosion(StateInfo _state);

private:
	Worm* parentWorm_;
	GameEngineFSM<SuperSheep> state_;
	GameEngineRenderer* mainRender_;

	float4 speed_;

	GameEngineCollision* topCenterCollision_;
	GameEngineCollision* headCollision_;
	GameEngineCollision* bottomCenterCollision_;
	GameEngineCollision* groundCheckCollision_;

	float deltaTime_;
	float jumpDelay_;
	float explosionDelay_;
	bool bLeft_;
	bool bGround_;
};