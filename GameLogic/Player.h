#pragma once
#include <GameEngineActor.h>
#include <GameEngineFSM.h>
#include <GameEngineTime.h>
#include <GameEngineFSM.h>





// 코드를 덜치기 위해서 상태머신구조를 만드는게 아닙니다.
// 상태를 꼬이게 하지 않기 위해서 만드는 겁니다.
//enum class PlayerState 
//{
//	IDLE,
//	WALKMOVE,
//	BOOSTMOVE,
//	WAITSTOP,
//	JUMP,
//	ROLLMOVE,
//};

// 분류 :
// 용도 :
// 설명 :
class GameEngineSoundPlayer;
class Player : public GameEngineActor
{
private:	// member Var
	float Speed;

public:
	// 여기에 bool값이 수십개가 만들어지기 시작한다.
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
	Player(); // default constructer 디폴트 생성자
	~Player() override; // default destructer 디폴트 소멸자

public:		// delete constructer
	Player(const Player& _other) = delete; // default Copy constructer 디폴트 복사생성자
	Player(Player&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

public:		//delete operator
	Player& operator=(const Player& _other) = delete; // default Copy operator 디폴트 대입 연산자
	Player& operator=(const Player&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

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

