#include "Petroleum.h"
#include <GameEngineWindow.h>
#include <GameEngineRenderer.h>
#include <GameEngineCollision.h>
#include <GameEngineTime.h>

#include "eCollisionGroup.h"
#include "eCollisionCheckColor.h"

#include "PlayLevel.h"


// 메모 : 간혹 폭발 후 소환이 안돼는 문제가 있음
// 원인 파악중

Petroleum::Petroleum() :
	Max_LifeTime_(5.f),
	Cur_LifeTime_(0.f),
	GravitySpeed(0.f),
	GravityAcc(0.f),
	WindAcc_(0.f),
	degree_(0.f),
	deltaTime_(0.f),
	WindSpeed_(0.f),
	mainSpriteRender_(nullptr),
	groundCollision_(nullptr),
	BodyCollision_(nullptr),
	Burn_(false),
	Isground_(false),
	CountSecond_{}
{

}

Petroleum::~Petroleum() // default destructer 디폴트 소멸자
{

}

Petroleum::Petroleum(Petroleum&& _other) noexcept :
	Max_LifeTime_(5.f),
	Cur_LifeTime_(0.f),
	GravitySpeed(0.f),
	GravityAcc(0.f),
	WindAcc_(0.f),
	degree_(0.f),
	deltaTime_(0.f),
	WindSpeed_(0.f),
	mainSpriteRender_(nullptr),
	groundCollision_(nullptr),
	BodyCollision_(nullptr),
	Burn_(false),
	Isground_(false),
	CountSecond_{}
{

}

void Petroleum::Start()
{
	GravityAcc = 6.f;

	mainSpriteRender_ = CreateRenderer("petrol-1");

	mainSpriteRender_->CreateAnimation("petrol60", "petrol60", 0, 19, true, 0.05f);
	mainSpriteRender_->CreateAnimation("petrol50", "petrol50", 0, 19, true, 0.05f);
	mainSpriteRender_->CreateAnimation("petrol40", "petrol40", 0, 19, true, 0.05f);
	mainSpriteRender_->CreateAnimation("petrol30", "petrol30", 0, 19, true, 0.05f);
	mainSpriteRender_->CreateAnimation("petrol20", "petrol20", 0, 19, true, 0.05f);

	mainSpriteRender_->CreateAnimation("petrol-1", "petrol-1", 0, 63, true, 100.f);
	mainSpriteRender_->CreateAnimation("petrol-2", "petrol-2", 0, 63, true, 100.f);
	mainSpriteRender_->CreateAnimation("petrol-3", "petrol-3", 0, 63, true, 100.f);
	mainSpriteRender_->CreateAnimation("petrol-4", "petrol-4", 0, 63, true, 100.f);

	mainSpriteRender_->ChangeAnimation("petrol-1");

	initCollision();
}

void Petroleum::UpdateBefore()
{

}

void Petroleum::Update()
{
	deltaTime_ = GameEngineTime::GetInst().GetDeltaTime();

	if (nullptr == groundCollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MAP)))
	{	
		WindSpeed_ += WindAcc_;
		GravitySpeed += GravityAcc;

		if (true == Burn_)
		{
			SetMove((Dir_.x+ WindSpeed_) * deltaTime_, (Dir_.y+ GravitySpeed) * deltaTime_);
		}
		else
		{
			prevPos_ = pos_;
			SetMove((Dir_.x + WindSpeed_/2) * deltaTime_, (Dir_.y + GravitySpeed/2) * deltaTime_);
			//SetMove(Dir_ * deltaTime_);
		}
	}
	else
	{
		Dir_.y = 0.f;
		Dir_.x = 0.f;
		GravitySpeed = 0.f;
		WindSpeed_ = 0.f;
		Burn_ = true;
		Isground_ = true;
		// x값에 풍향이 적용되게
		// 비탈을 만나면 비탈로 슬금슬금
		// 
	}

	if (false == Burn_)
	{
		Cur_LifeTime_ += deltaTime_;

		float4 moveVector = pos_ - prevPos_;
		moveVector.Normalize2D();

		float theta;

		if (pos_.x < prevPos_.x)
		{
			theta = float4::DOWN.x * moveVector.x + float4::DOWN.y * moveVector.y;
		}
		else
		{
			theta = float4::UP.x * moveVector.x + float4::UP.y * moveVector.y;
		}

		theta = acos(theta);
		degree_ = theta * (180.f / 3.14f);

		if (pos_.x < prevPos_.x)
		{
			degree_ += 180.f;
		}

		degree_ += 2.8125f;

		if (degree_ > 360.f)
		{
			degree_ -= 360.f;
		}

		int frameIndex = (int)(degree_ / 5.625f);

		if (Cur_LifeTime_ < 0.3f)
		{
			mainSpriteRender_->ChangeAnimation("petrol-2", std::string("petrol-2"));
			mainSpriteRender_->SetAnimationCurrentFrame(frameIndex);
		}

		else if (Cur_LifeTime_ < 0.45f)
		{
			mainSpriteRender_->ChangeAnimation("petrol-3", std::string("petrol-3"));
			mainSpriteRender_->SetAnimationCurrentFrame(frameIndex);
		}

		else if (Cur_LifeTime_ < 0.6f)
		{
			mainSpriteRender_->ChangeAnimation("petrol-4", std::string("petrol-4")); 
			mainSpriteRender_->SetAnimationCurrentFrame(frameIndex);
			Burn_ = true;
			Cur_LifeTime_ = 0.f;
		}
	}

	else if (false == Isground_)
	{
		mainSpriteRender_->ChangeAnimation("petrol60", std::string("petrol60"));
	}

	else if(true == Isground_)
	{
		if (Cur_LifeTime_ < 1.f)
		{
			mainSpriteRender_->ChangeAnimation("petrol60", std::string("petrol60"));
		}
		else if (Cur_LifeTime_ < 2.f)
		{
			mainSpriteRender_->ChangeAnimation("petrol50", std::string("petrol50"));
		}
		else if (Cur_LifeTime_ < 3.f)
		{
			mainSpriteRender_->ChangeAnimation("petrol40", std::string("petrol40"));
		}
		else if (Cur_LifeTime_ < 4.f)
		{
			mainSpriteRender_->ChangeAnimation("petrol30", std::string("petrol30"));
		}
		else if (Cur_LifeTime_ < Max_LifeTime_)
		{
			mainSpriteRender_->ChangeAnimation("petrol20", std::string("petrol20"));
		}

		if (false == CountSecond_[static_cast<int>(Cur_LifeTime_)])
		{
			GetLevel<PlayLevel>()->GroundUpdate13(pos_);
			CountSecond_[static_cast<int>(Cur_LifeTime_)] = true;
		}

		Cur_LifeTime_ += deltaTime_;
	}

	if (Cur_LifeTime_ >= Max_LifeTime_)
	{
		Death();
		return;
	}
}

void Petroleum::UpdateAfter()
{
}

void Petroleum::Render()
{
#ifdef _DEBUG	
	if (GetLevel<PlayLevel>()->GetDebug())
	{
		groundCollision_->DebugRender();
	}
#endif // DEBUG
	mainSpriteRender_->AnimationUpdate();

}

void Petroleum::initCollision()
{
	groundCollision_ = CreateCollision(static_cast<int>(eCollisionGroup::PETROLEUM), CollisionCheckType::POINT);
	groundCollision_->SetColorCheck(static_cast<DWORD>(eCollisionCheckColor::MAP));
	//groundCollision_->SetSize({ 10.f, 10.f });
	groundCollision_->SetPivot({ 0.f, 1.f });
}



