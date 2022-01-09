#include "Player.h"
#include <sstream>
#include <GameEngineInput.h>
#include <GameEngineLevel.h>
#include <GameEngineImageFile.h>
#include <GameEngineImage.h>
#include <GameEngineWindow.h>
#include <GameEngineTime.h>
#include <GameEngineRenderer.h>
#include <GameEngineTime.h>
#include "LogicEnum.h"
#include <GameEngineCollision.h>
#include "PlayBack.h"
#include "Monster.h"
#include <GameEngineSound.h>
#include <GameEngineSoundPlayer.h>
#include <GameEngineDebugExtension.h>

// Static Var
// Static Func

// constructer destructer
Player::Player()
	: Speed(400.0f)
	, PlayerState(this)
	, RotCollisionDegree(0.0f)
{
	SetRenderOrder(1000);
	SetPos(GameEngineWindow::GetInst().GetSize().halffloat4());
}

Player::~Player()
{
}

Player::Player(Player&& _other) noexcept
	: PlayerState(this)
{
}

//member Func
void Player::Start() 
{
	// 씬도 다 세팅됬고 이름도 세팅됐고. 
	// => 세팅이 안되어 있거나 값이 비어있을가능성 zero
	// 엔진에서 그걸 지원해준다.
	// 앞으로 기본적인 세팅은 
	if (false == GameEngineInput::GetInst().IsKey("L"))
	{
		// 대문자만 인식이 가능
		GameEngineInput::GetInst().CreateKey("L", VK_LEFT);
		GameEngineInput::GetInst().CreateKey("R", VK_RIGHT);
		GameEngineInput::GetInst().CreateKey("U", VK_UP);
		GameEngineInput::GetInst().CreateKey("D", VK_DOWN);
		GameEngineInput::GetInst().CreateKey("Att", 'Q');
		GameEngineInput::GetInst().CreateKey("Roll", 'E');
	}


	mainRender_ = CreateRenderer("knuckles.bmp");
	mainRender_->SetMaskImage("knucklesMask.bmp");

	mainRender_->CreateAnimation("Right_Idle", "knuckles.bmp", 0, 0, true, 0.3f, RENDERPIVOT::BOT);
	mainRender_->CreateAnimation("Right_Move", "knuckles.bmp", 16, 16 + 8, true, 0.1f, RENDERPIVOT::BOT);
	// mainRender_->SetChangeFrame("Right_Move", 5, 0.5f);
	//mainRender_->CreateAnimation("Boring", "knuckles.bmp", 1, 3, true, 0.3f);
	mainRender_->CreateAnimation("Att", "knuckles.bmp", 4, 11, false, 0.1f, RENDERPIVOT::BOT);
	// mainRender_->SetImagePivot();

	hpbarRender_ = CreateRenderer("hpbar.bmp");
	hpbarRender_->SetPivotPos({ 0, -160 });

	PlayerState.CreateState("Idle", &Player::StartIdle, &Player::Idle);
	PlayerState.CreateState("Move", &Player::StartMove, &Player::Move);
	PlayerState.ChangeState("Idle");

	BotGroundCheckCollision = CreateCollision(ST2GROUP::PLAYER, CollisionCheckType::POINT);
	RightGroundCheckCollision = CreateCollision(ST2GROUP::PLAYER, CollisionCheckType::POINT);
	RightGroundCheckCollision->SetPivot({ 50, -50 });
	LeftGroundCheckCollision = CreateCollision(ST2GROUP::PLAYER, CollisionCheckType::POINT);
	LeftGroundCheckCollision->SetPivot({ -50, -50 });

	BodyCollision = CreateCollision(ST2GROUP::PLAYER, CollisionCheckType::RECT);
	BodyCollision->SetPivot({ 0, -50 });
	BodyCollision->SetSize({100, 100});

	RotCollision = CreateCollision(ST2GROUP::PLAYER, CollisionCheckType::POINT);
	RotCollision->SetSize({ 100, 100 });

	// 200, 0

	RotCollisionDegree = 0;
	// e
	RotPivot = float4::RIGHT * 50.0f;

	RotCollision->SetPivot(RotPivot);

	EffectSoundPlayer = GameEngineSound::GetInst().CreateSoundPlayer();
	// 즉 이 sin값은 길이가 1일때의 

	if (nullptr == EffectSoundPlayer)
	{
		GameEngineDebug::AssertFalse();
	}

	EffectSoundPlayer->PlayCountReset(1);
}

StateInfo Player::StartIdle(StateInfo _State)
{
	mainRender_->ChangeAnimation("Right_Idle");
	return "";
}

StateInfo Player::StartMove(StateInfo _State)
{
	mainRender_->ChangeAnimation("Right_Move");
	return "";
}

void Player::Update()
{
	mainRender_->SetAddRotate(10.0f * GameEngineTime::GetInst().GetDeltaTime());

	PlayerState.Update();
}

StateInfo Player::Idle(StateInfo _State)
{
	float Time = GameEngineTime::GetInst().GetDeltaTime();

	if (true == GameEngineInput::GetInst().IsPress("L")
		|| true == GameEngineInput::GetInst().IsPress("R")
		|| true == GameEngineInput::GetInst().IsPress("U")
		|| true == GameEngineInput::GetInst().IsPress("D"))
	{	
		return "Move";
	}


	BotGroundCheckCollision->SetColorCheck(RGB(0, 0, 0));
	if (nullptr == BotGroundCheckCollision->CollisionGroupCheckOne(ST2GROUP::MAP))
	{
		SetMove(float4::DOWN * GameEngineTime::GetInst().GetDeltaTime() * 100.0f);
	}

	// 만약에 이방법 안쓰면 귀찮아져요 OK?
	GetLevel()->SetCamPos(GetPos() - GameEngineWindow::GetInst().GetSize().halffloat4());

	return "";
}

void Player::ColMonsterCheck() 
{
	// BodyCollision->SetColorCheck(RGB(0, 0, 0));

	{
		//GameEngineCollision* Collision = BodyCollision->CollisionGroupCheckOne(ST2GROUP::MONSTER);
		//if (nullptr != Collision)
		//{
		//	Monster* MonsterPtr = Collision->GetActorConvert<Monster>();
		//	MonsterPtr->Death();

		//}
	}

	{

		RotPivot = float4::DegreeToRotatefloat2(RotPivot, 360.0f * GameEngineTime::GetInst().GetDeltaTime());

		// RotCollisionDegree += 360.0f * GameEngineTime::GetInst().GetDeltaTime();

		RotCollision->SetPivot(RotPivot);

		GameEngineCollision* Collision = RotCollision->CollisionGroupCheckOne(ST2GROUP::MONSTER);

		if (nullptr != Collision)
		{
			Monster* MonsterPtr = Collision->GetActorConvert<Monster>();
			MonsterPtr->Death();
		}
	}
}

StateInfo Player::Move(StateInfo _State)
{
	ColMonsterCheck();



	BotGroundCheckCollision->SetColorCheck(RGB(0, 0, 0));
	if (nullptr == BotGroundCheckCollision->CollisionGroupCheckOne(ST2GROUP::MAP))
	{
		SetMove(float4::DOWN * GameEngineTime::GetInst().GetDeltaTime() * 100.0f);
		GetLevel()->SetCamMove(float4::DOWN * GameEngineTime::GetInst().GetDeltaTime() * 100.0f);
	}

	if (true == GameEngineInput::GetInst().IsPress("L"))
	{
		// 이것도 원한게 아니죠
		EffectSoundPlayer->PlayAlone("vo_shk.mp3");

		// GameEngineSound::GetInst().PlaySoundOneShot("vo_shk.mp3");

		if (nullptr == LeftGroundCheckCollision->CollisionGroupCheckOne(ST2GROUP::MAP))
		{
			SetMove(float4::LEFT * GameEngineTime::GetInst().GetDeltaTime() * Speed);
			GetLevel()->SetCamMove(float4::LEFT * GameEngineTime::GetInst().GetDeltaTime() * Speed);
		}
	}

	if (true == GameEngineInput::GetInst().IsPress("R"))
	{
		SetMove(float4::RIGHT * GameEngineTime::GetInst().GetDeltaTime() * Speed);
		GetLevel()->SetCamMove(float4::RIGHT * GameEngineTime::GetInst().GetDeltaTime() * Speed);
	}

	if (true == GameEngineInput::GetInst().IsPress("U"))
	{
		SetMove(float4::UP * GameEngineTime::GetInst().GetDeltaTime() * Speed);
		GetLevel()->SetCamMove(float4::UP * GameEngineTime::GetInst().GetDeltaTime() * Speed);
	}

	if (false == GameEngineInput::GetInst().IsPress("L")
		&& false == GameEngineInput::GetInst().IsPress("R")
		&& false == GameEngineInput::GetInst().IsPress("U")
		&& false == GameEngineInput::GetInst().IsPress("D"))
	{
		EffectSoundPlayer->PlayCountReset(1);
		return "Idle";
	}

	return "";
}

void Player::Collision() 
{
	//if (무적 상태가 아니라면)
	//{
	// ColMonsterCheck();
	//}
}

void Player::Render()
{
	{
		mainRender_->AnimationUpdate();
		hpbarRender_->Render();

		//BotGroundCheckCollision->DebugRender();
		//RightGroundCheckCollision->DebugRender();
		//LeftGroundCheckCollision->DebugRender();
		//BodyCollision->DebugRender();
		RotCollision->DebugRender();
	}
}

StateInfo Player::AttPunch(StateInfo _state)
{
	// 좌우가 다르죠?

	int PosX = 100;

	return "Test";

	//if (레프트일때는 )
	//{
		//PosX *= -1;
	//}

	//if (mainRender_->GetCurAnimationFrame() == 0)
	//{
	//	PunchCollision->SetPivot({ PosX,200});
	//}
	//else if (mainRender_->GetCurAnimationFrame() == 1)
	//{
	//	PunchCollision->SetPivot({ PosX,200 });
	//}
}
