#pragma once

#include <GameEngineActor.h>
#include <GameEngineFSM.h>

class GameEngineCollision;
class GameEngineRenderer;
class Worm;
class Sheep : public GameEngineActor
{
public:
	Sheep();
	~Sheep();

	Sheep(const Sheep& _other) = delete;
	Sheep(Sheep&& _other) = delete;

	Sheep& operator=(const Sheep& _other) = delete;
	Sheep& operator=(const Sheep&& _other) = delete;

public:
	// GameEngineActor��(��) ���� ��ӵ�
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
	const float GRAVITY_POWER = 500.f;
	const float BOTTOM_PIVOT = 14.f;
	const float JUMP_DELAY = 3.f;

private:
	StateInfo startWalk(StateInfo _state);
	StateInfo updateWalk(StateInfo _state);

	StateInfo startExplosion(StateInfo _state);
	StateInfo updateExplosion(StateInfo _state);

private:
	Worm* parentWorm_;
	GameEngineFSM<Sheep> state_;
	GameEngineRenderer* mainRender_;

	float4 speed_;

	GameEngineCollision* headCollision_;
	GameEngineCollision* bottomCenterCollision_;
	GameEngineCollision* groundCheckCollision_;

	float deltaTime_;
	float jumpDelay_;
	bool bLeft_;
	bool bGround_;
};

