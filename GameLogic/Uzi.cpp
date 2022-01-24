#include "Uzi.h"

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
#include "Worm.h"


Uzi::Uzi() // default constructer 디폴트 생성자
	: mainRender_(nullptr)
	, fireCollision_(nullptr)
	, bGround_(false)
	, bLeft_(false)
	, bBackJump_(false)
	, deltaTime_(0.0f)
	, degree_(0.f)
{

}

Uzi::~Uzi() // default destructer 디폴트 소멸자
{

}

Uzi::Uzi(Uzi&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
	: mainRender_(nullptr)
	, fireCollision_(nullptr)
	, bGround_(false)
	, bLeft_(false)
	, bBackJump_(false)
	, deltaTime_(0.0f)
	, degree_(0.f)
{

}


void Uzi::Start()
{
	SetRenderOrder((int)RenderOrder::Weapon);
	fireCollision_ = CreateCollision(static_cast<int>(eCollisionGroup::PLAYER), CollisionCheckType::POINT);
	fireCollision_->SetColorCheck(static_cast<DWORD>(eCollisionCheckColor::MAP));
	parentForward_ = parentWorm_->GetForward();
}

void Uzi::UpdateBefore()
{

}

void Uzi::Update()
{
	deltaTime_ = GameEngineTime::GetInst().GetDeltaTime();

	if (nullptr == fireCollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MAP)))
	{ // 만약 히트레이가 지형을 만나지 않는다면...
		PlayLevel* level = (PlayLevel*)GetLevel();
		bGround_ = false;

		if (pos_.x > parentWorm_->GetForward().x) // 왼쪽 조준
		{
			float4 hitRay = pos_ - parentWorm_->GetForward();
			SetMove(hitRay * GameEngineTime::GetInst().GetDeltaTime());
		}
		if (pos_.x < parentWorm_->GetForward().x) // 오른쪽 조준
		{
			float4 hitRay = parentWorm_->GetForward() - pos_;
			SetMove(hitRay * GameEngineTime::GetInst().GetDeltaTime());
		}
	}
	else
	{
		PlayLevel* level = (PlayLevel*)GetLevel();
		level->CreateExplosion25({ pos_.x, pos_.y });//GroundExplosion(float4(pos_.x - 50.f, pos_.y - 50.f));
		Death();
	}

}

void Uzi::UpdateAfter()
{
}

void Uzi::Render()
{
	mainRender_->AnimationUpdate();
}


