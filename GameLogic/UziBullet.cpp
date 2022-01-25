#include "UziBullet.h"

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


UziBullet::UziBullet() // default constructer 디폴트 생성자
	: mainRender_(nullptr)
	, fireCollision_(nullptr)
	, bGround_(false)
	, bLeft_(false)
	, bBackJump_(false)
	, deltaTime_(0.0f)
	, degree_(0.f)
	, curShot_(0)
{

}

UziBullet::~UziBullet() // default destructer 디폴트 소멸자
{

}

UziBullet::UziBullet(UziBullet&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
	: mainRender_(nullptr)
	, fireCollision_(nullptr)
	, bGround_(false)
	, bLeft_(false)
	, bBackJump_(false)
	, deltaTime_(0.0f)
	, degree_(0.f)
	, curShot_(0)
{

}


void UziBullet::Start()
{
	SetRenderOrder((int)RenderOrder::Weapon);
	fireCollision_ = CreateCollision(static_cast<int>(eCollisionGroup::PLAYER), CollisionCheckType::POINT);
	fireCollision_->SetColorCheck(static_cast<DWORD>(eCollisionCheckColor::MAP));

}

void UziBullet::UpdateBefore()
{

}

void UziBullet::Update()
{
	deltaTime_ = 0.2f;
	parentForward_ = parentWorm_->GetForward();


		if (0.2f <= deltaTime_)
		{
			if (nullptr == fireCollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MAP)))
			{ // 만약 히트레이가 지형을 만나지 않는다면...
				PlayLevel* level = (PlayLevel*)GetLevel();
				bGround_ = false;
				SetMove(direction_);
			}

			if (nullptr != fireCollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MAP)))
			{
				PlayLevel* level = (PlayLevel*)GetLevel();
				level->CreateExplosion25({ pos_.x, pos_.y });//GroundExplosion(float4(pos_.x - 50.f, pos_.y - 50.f));
				curShot_ += 1;
				deltaTime_ = 0.0f;
				Death();
			}
		}
	



}

void UziBullet::UpdateAfter()
{
}

void UziBullet::Render()
{
}


