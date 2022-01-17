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
	, speed_(float4::ZERO)
	, direction_(float4::RIGHT)
	, bGround_(false)
	, bLeft_(false)
	, bBackJump_(false)
	, deltaTime_(0.0f)
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
		SetMove(float4::DOWN * 200.f * deltaTime_);
	}
	else
	{
		PlayLevel* level = (PlayLevel*)GetLevel();
		level->AJYGround(float4(pos_.x  - 50.f, pos_.y - 50.f));
		SetPos(float4( -100.f, -100.f));
	}
}

void Bazooka::UpdateAfter()
{
}

void Bazooka::Render()
{
	mainRender_->Render();
}

