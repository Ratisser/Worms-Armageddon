#pragma once
#include <GameEngineActor.h>
#include <GameEngineFSM.h>
#include <GameEngineTime.h>
#include <GameEngineFSM.h>





// �ڵ带 ��ġ�� ���ؼ� ���¸ӽű����� ����°� �ƴմϴ�.
// ���¸� ���̰� ���� �ʱ� ���ؼ� ����� �̴ϴ�.
//enum class PlayerState 
//{
//	IDLE,
//	WALKMOVE,
//	BOOSTMOVE,
//	WAITSTOP,
//	JUMP,
//	ROLLMOVE,
//};

// �з� :
// �뵵 :
// ���� :
class GameEngineSoundPlayer;
class Player : public GameEngineActor
{
private:	// member Var
	float Speed;

public:
	// ���⿡ bool���� ���ʰ��� ��������� �����Ѵ�.
	// bool IsGround;
	// bool IsJump;
	// bool IsIdle;
	// bool IsIdle;

	GameEngineRenderer* mainRender_;
	GameEngineRenderer* hpbarRender_;

	GameEngineSoundPlayer* EffectSoundPlayer;

	GameEngineCollision* BotGroundCheckCollision;
	GameEngineCollision* RightGroundCheckCollision;
	GameEngineCollision* LeftGroundCheckCollision;

	GameEngineCollision* BodyCollision;
	GameEngineCollision* RotCollision;

	float4 RotPivot;
	float RotCollisionDegree;

	GameEngineCollision* PunchCollision;
	// std::list< GameEngineCollision> fireCallisionList;

public:		
	Player(); // default constructer ����Ʈ ������
	~Player() override; // default destructer ����Ʈ �Ҹ���

public:		// delete constructer
	Player(const Player& _other) = delete; // default Copy constructer ����Ʈ ���������
	Player(Player&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

public:		//delete operator
	Player& operator=(const Player& _other) = delete; // default Copy operator ����Ʈ ���� ������
	Player& operator=(const Player&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:		//member Func
	void Start();
	void Update();
	void Collision();
	void Render();

public:
	// PlayerState stateType_;
	GameEngineFSM<Player> PlayerState;

public:
	void ColMonsterCheck();

public:
	StateInfo StartIdle(StateInfo _State);
	StateInfo StartMove(StateInfo _State);

	StateInfo Idle(StateInfo _State);
	StateInfo Move(StateInfo _State);

	StateInfo AttPunch(StateInfo _state);
};

