#pragma once

#include <GameEngineActor.h>
#include <GameEngineFSM.h>

class GameEngineRenderer;
class Worm : public GameEngineActor
{
public:
	Worm();
	~Worm();

	Worm(const Worm& _other) = delete; // default Copy constructer ����Ʈ ���������
	Worm(Worm&& _other) = delete; // default RValue Copy constructer ����Ʈ RValue ���������

	Worm& operator=(const Worm& _other) = delete; // default Copy operator ����Ʈ ���� ������
	Worm& operator=(const Worm&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

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

	void addGravity(float _deltaTime);

private:
	//StateInfo startIdleLeft(StateInfo _state);
	//StateInfo updateIdleLeft(StateInfo _state);
	//
	//StateInfo startIdleRight(StateInfo _state);
	//StateInfo updateIdleRight(StateInfo _state);

	//StateInfo startIdleRight(StateInfo _state);
	//StateInfo updateIdleRight(StateInfo _state);

	//StateInfo startIdleRight(StateInfo _state);
	//StateInfo updateIdleRight(StateInfo _state);

	//StateInfo startIdleRight(StateInfo _state);
	//StateInfo updateIdleRight(StateInfo _state);

	//StateInfo startIdleRight(StateInfo _state);
	//StateInfo updateIdleRight(StateInfo _state);

	//StateInfo startIdleRight(StateInfo _state);
	//StateInfo updateIdleRight(StateInfo _state);

	//StateInfo startIdleRight(StateInfo _state);
	//StateInfo updateIdleRight(StateInfo _state);

	//StateInfo startIdleRight(StateInfo _state);
	//StateInfo updateIdleRight(StateInfo _state);

	//StateInfo startIdleRight(StateInfo _state);
	//StateInfo updateIdleRight(StateInfo _state);

	//StateInfo startIdleRight(StateInfo _state);
	//StateInfo updateIdleRight(StateInfo _state);

	//StateInfo startIdleRight(StateInfo _state);
	//StateInfo updateIdleRight(StateInfo _state);

	//StateInfo startIdleRight(StateInfo _state);
	//StateInfo updateIdleRight(StateInfo _state);

private:
	const float SPEED = 100.f;

private:
	GameEngineRenderer* mainRender_;
	GameEngineCollision* groundCollision_;

	float4 speed_;
	float4 direction_;

};

