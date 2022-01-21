#include "Bazooka.h"

#include <GameEngineRenderer.h>
#include <GameEngineInput.h>
#include <GameEngineTime.h>
#include <GameEngineLevelManager.h>
#include <GameEngineLevel.h>
#include <GameEngineCollision.h>

#include "WindController.h"
#include "eCollisionGroup.h"
#include "eCollisionCheckColor.h"
#include "PlayLevel.h"
#include "Explosion.h"

Bazooka::Bazooka()
	: mainRender_(nullptr)
	, groundCheckCollision_(nullptr)
	, accelation_(float4::ZERO)
	, speed_(float4(0.f, - 300.f))
	, direction_(float4::RIGHT)
	, bGround_(false)
	, bLeft_(false)
	, bBackJump_(false)
	, deltaTime_(0.0f)
	, degree_(0.f)
{

}

Bazooka::~Bazooka() // default destructer 디폴트 소멸자
{

}

void Bazooka::Start()
{
	SetRenderOrder((int)RenderOrder::Weapon);
	mainRender_ = CreateRenderer("missile");

	mainRender_->CreateAnimation("missile1", "missile", 0, 31, true, FLT_MAX);
	mainRender_->ChangeAnimation("missile1");

	groundCheckCollision_ = CreateCollision(static_cast<int>(eCollisionGroup::PLAYER), CollisionCheckType::POINT);
	groundCheckCollision_->SetColorCheck(static_cast<DWORD>(eCollisionCheckColor::MAP));
	groundCheckCollision_->SetPivot({ 0.0f, BOTTOM_PIVOT + 1.f });

}

void Bazooka::UpdateBefore()
{

}

void Bazooka::Update()
{
	prevPos_ = pos_;
	deltaTime_ = GameEngineTime::GetInst().GetDeltaTime();

	if (nullptr == groundCheckCollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MAP)))
	{
		PlayLevel* level = (PlayLevel*)GetLevel();
		float windSpeed = level->GetWindController()->GetCurrentWindSpeed();

		bGround_ = false;

		speed_.x += windSpeed * deltaTime_;
		speed_.y += GRAVITY_POWER * deltaTime_;
		float4 MovePos = speed_ * deltaTime_;
		SetMove(MovePos);

		float4 moveVector = pos_ - prevPos_;
		float normalize = sqrtf(moveVector.x * moveVector.x + moveVector.y * moveVector.y);
		moveVector.x /= normalize;
		moveVector.y /= normalize; 
		
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

		degree_ += 5.625f;

		if (degree_ > 360.f)
		{
			degree_ -= 360.f;
		}

		int frameIndex = (int)(degree_ / 11.25);
		mainRender_->SetAnimationCurrentFrame(frameIndex);
	}
	else
	{
		PlayLevel* level = (PlayLevel*)GetLevel();
		level->GroundExplosion(float4(pos_.x - 50.f, pos_.y - 50.f));
		SetPos(float4(-100.f, -100.f));
		Death();
	}

}

void Bazooka::UpdateAfter()
{
}

void Bazooka::Render()
{
	mainRender_->AnimationUpdate();
}

