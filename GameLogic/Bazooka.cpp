#include "Bazooka.h"

#include <GameEngineRenderer.h>
#include <GameEngineInput.h>
#include <GameEngineTime.h>
#include <GameEngineLevelManager.h>
#include <GameEngineLevel.h>
#include <GameEngineCollision.h>

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
	, power_(300.f)
	, bGround_(false)
	, bLeft_(false)
	, bBackJump_(false)
	, deltaTime_(0.0f)
	, distance_(500.f)
{

}

Bazooka::~Bazooka() // default destructer 디폴트 소멸자
{

}

void Bazooka::Start()
{
	SetRenderOrder((int)RenderOrder::Weapon);
	mainRender_ = CreateRenderer("Bazooka");

	groundCheckCollision_ = CreateCollision(static_cast<int>(eCollisionGroup::PLAYER), CollisionCheckType::POINT);
	groundCheckCollision_->SetColorCheck(static_cast<DWORD>(eCollisionCheckColor::MAP));
	groundCheckCollision_->SetPivot({ 0.0f, BOTTOM_PIVOT + 1.f });
}

void Bazooka::UpdateBefore()
{

}

void Bazooka::Update()
{
	deltaTime_ = GameEngineTime::GetInst().GetDeltaTime();

	if (nullptr == groundCheckCollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MAP)))
	{
		bGround_ = false;
		speed_.y += GRAVITY_POWER * deltaTime_;
		float4 MovePos = (float4((direction_ * power_).x, speed_.y) * deltaTime_);
		SetMove(MovePos);
		distance_ -= sqrtf(MovePos.x * MovePos.x + MovePos.y * MovePos.y);
	}
	else
	{
		PlayLevel* level = (PlayLevel*)GetLevel();
		level->GroundExplosion(float4(pos_.x - 50.f, pos_.y - 50.f));
		SetPos(float4(-100.f, -100.f));
		Death();
	}

	if (0 >= distance_)
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
	mainRender_->Render();
}

