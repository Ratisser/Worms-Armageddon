#include "Petroleum.h"
#include <GameEngineWindow.h>
#include <GameEngineRenderer.h>
#include <GameEngineCollision.h>
#include <GameEngineTime.h>
#include "PlayLevel.h"

#include "eCollisionGroup.h"
#include "eCollisionCheckColor.h"

Petroleum::Petroleum() :
	Max_LifeTime_(4.f),
	Cur_LifeTime_(0.f),
	GravitySpeed(0.f),
	GravityAcc(0.f),
	degree_(0.f),
	deltaTime_(0.f),
	mainSpriteRender_(nullptr), 
	groundCollision_(nullptr),
	BodyCollision_(nullptr),
	Burn_(false),
	Isground_(false),
	CountSecond_{}
{

}

Petroleum::~Petroleum() // default destructer µðÆúÆ® ¼Ò¸êÀÚ
{

}

Petroleum::Petroleum(Petroleum&& _other) noexcept :
	Max_LifeTime_(4.f),
	Cur_LifeTime_(0.f),
	GravitySpeed(0.f),
	GravityAcc(0.f),
	degree_(0.f),
	deltaTime_(0.f),
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
	prevPos_ = pos_;

	{
		Dir_.y += GravitySpeed * deltaTime_;
		GravitySpeed += GravityAcc;

		SetMove(Dir_ * deltaTime_);
	}

	if (false == Burn_)
	{
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
		if (frameIndex > 63 || frameIndex < 0)
		{
			GameEngineDebug::AssertFalse();
		}

		if (Cur_LifeTime_ < 0.3f)
		{
			mainSpriteRender_->ChangeAnimation("petrol-2", std::string("petrol-2"));
		}

		else if (Cur_LifeTime_ < 0.6f)
		{
			mainSpriteRender_->ChangeAnimation("petrol-3", std::string("petrol-3"));
		}

		else if (Cur_LifeTime_ < 0.9f)
		{
			mainSpriteRender_->ChangeAnimation("petrol-4", std::string("petrol-4"));
			Burn_ = true;
		}	
		mainSpriteRender_->SetAnimationCurrentFrame(frameIndex);
	}

	else //(true == Burn_)
	{
		if (Cur_LifeTime_ < 1.2f)
		{
			mainSpriteRender_->ChangeAnimation("petrol60", std::string("petrol60"));
		}

		else if (Cur_LifeTime_ < 1.5f)
		{
			mainSpriteRender_->ChangeAnimation("petrol50", std::string("petrol50"));
		}

		else if (Cur_LifeTime_ < 2.5f)
		{
			mainSpriteRender_->ChangeAnimation("petrol40", std::string("petrol40"));
		}
		else if (Cur_LifeTime_ < 3.f)
		{
			mainSpriteRender_->ChangeAnimation("petrol30", std::string("petrol30"));
		}
		else if (Cur_LifeTime_ < 3.5f)
		{
			mainSpriteRender_->ChangeAnimation("petrol20", std::string("petrol20"));
		}
	}

	if (Cur_LifeTime_ > Max_LifeTime_)
	{
		Death();
	}

	Cur_LifeTime_ += deltaTime_;

	if (false == CountSecond_[(int)Cur_LifeTime_])
	{
		//GetLevel<PlayLevel>()->GroundExplosion(pos_);
		// ¶¥ ±ðÀÌ±â, 1ÃÊ¸¶´Ù ¶¥À» ±ð°Ô µÉ°Í
		CountSecond_[(int)Cur_LifeTime_] = true;
	}
}

void Petroleum::UpdateAfter()
{
}


void Petroleum::Render()
{
	mainSpriteRender_->AnimationUpdate();
}

void Petroleum::initCollision()
{
	//groundCollision_ = CreateCollision(static_cast<int>(eCollisionGroup::PETROLEUM), CollisionCheckType::POINT);
	//groundCollision_->SetColorCheck(static_cast<DWORD>(eCollisionCheckColor::MAP));

	//BodyCollision_ = CreateCollision(static_cast<int>(eCollisionGroup::PETROLEUM), CollisionCheckType::POINT);
	//BodyCollision_->SetColorCheck(static_cast<DWORD>(eCollisionCheckColor::MAP));
}



