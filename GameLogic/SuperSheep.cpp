#include "SuperSheep.h"

#include <GameEngineCollision.h>
#include <GameEngineRenderer.h>
#include <GameEngineInput.h>

#include "PlayLevel.h"
#include "Worm.h"

#include "eCollisionGroup.h"
#include "eCollisionCheckColor.h"

SuperSheep::SuperSheep()
	: state_(this)
	, speed_(float4::ZERO)
	, mainRender_(nullptr)
	, headCollision_(nullptr)
	, bottomCenterCollision_(nullptr)
	, groundCheckCollision_(nullptr)
	, topCenterCollision_(nullptr)
	, bLeft_(false)
	, bGround_(false)
	, jumpDelay_(JUMP_DELAY)
	, deltaTime_(0.0f)
	, parentWorm_(nullptr)
	, explosionDelay_(0.0f)
{

}

SuperSheep::~SuperSheep()
{

}

void SuperSheep::Start()
{
	SetRenderOrder(static_cast<int>(RenderOrder::Weapon));

	// 렌더러
	mainRender_ = CreateRenderer("sheepWalkLeft.bmp");
	mainRender_->CreateAnimation("WalkLeft", "sheepWalkLeft.bmp", 0, 6, true, 0.1f);
	mainRender_->CreateAnimation("WalkRight", "sheepWalkRight.bmp", 0, 6, true, 0.1f);

	mainRender_->ChangeAnimation("WalkRight", std::string("sheepWalkRight.bmp"));

	// 충돌체
	topCenterCollision_ = CreateCollision(eCollisionGroup::WEAPON, CollisionCheckType::POINT);
	topCenterCollision_->SetColorCheck(static_cast<DWORD>(eCollisionCheckColor::MAP));
	topCenterCollision_->SetPivot({ 0.0f, -BOTTOM_PIVOT });

	headCollision_ = CreateCollision(eCollisionGroup::WEAPON, CollisionCheckType::POINT);
	headCollision_->SetColorCheck(static_cast<DWORD>(eCollisionCheckColor::MAP));

	bottomCenterCollision_ = CreateCollision(eCollisionGroup::WEAPON, CollisionCheckType::POINT);
	bottomCenterCollision_->SetColorCheck(static_cast<DWORD>(eCollisionCheckColor::MAP));
	bottomCenterCollision_->SetPivot({ 0.0f, BOTTOM_PIVOT });

	groundCheckCollision_ = CreateCollision(eCollisionGroup::WEAPON, CollisionCheckType::POINT);
	groundCheckCollision_->SetColorCheck(static_cast<DWORD>(eCollisionCheckColor::MAP));
	groundCheckCollision_->SetPivot({ 0.0f, BOTTOM_PIVOT + 1 });

	// 키
	if (false == GameEngineInput::GetInst().IsKey("Explosion"))
	{
		GameEngineInput::GetInst().CreateKey("Explosion", VK_SPACE);
	}

	// 상태
	state_.CreateState("Idle", &SuperSheep::startIdle, &SuperSheep::updateIdle);
	state_.CreateState("Walk", &SuperSheep::startWalk, &SuperSheep::updateWalk);
	state_.CreateState("Explosion", &SuperSheep::startExplosion, &SuperSheep::updateExplosion);
	state_.ChangeState("Walk");
}

void SuperSheep::UpdateBefore()
{
	mainRender_->AnimationUpdate();
}

void SuperSheep::Update()
{
	deltaTime_ = GameEngineTime::GetInst().GetDeltaTime();
	state_.Update();
}

void SuperSheep::UpdateAfter()
{
}

void SuperSheep::Render()
{
	if (mainRender_->IsOn())
	{
		mainRender_->Render();
	}
}

void SuperSheep::Initialize(Worm* _parentWorm, bool _bLeft)
{
	parentWorm_ = _parentWorm;
	bLeft_ = _bLeft;
}

void SuperSheep::addGravity()
{
	if (nullptr == groundCheckCollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MAP)))
	{
		bGround_ = false;
		speed_.y += GRAVITY_POWER * deltaTime_;
	}
	else
	{
		bGround_ = true;
		speed_.y = 0.0f;
		pos_.y = static_cast<float>(static_cast<int>(pos_.y));
	}
}

void SuperSheep::normalMove()
{
	SetMove(speed_ * deltaTime_);

	// 땅에 박힌 것
	if (nullptr != bottomCenterCollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MAP)))
	{
		while (nullptr != bottomCenterCollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MAP)))
		{
			SetMove({ 0.0f, -1.0f });
			pos_.y = static_cast<float>(static_cast<int>(pos_.y));
		}
	}
	else
	{
		bottomCenterCollision_->SetPivot({ 0, BOTTOM_PIVOT + 1 });
		if (nullptr != bottomCenterCollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MAP)))
		{
			// 정상 땅에 딱 붙어있는 상태
			bottomCenterCollision_->SetPivot({ 0, BOTTOM_PIVOT + 0 });
			return;
		}

		// 낭떠러지에 섰다
		bottomCenterCollision_->SetPivot({ 0, BOTTOM_PIVOT + 5 });
		if (nullptr == bottomCenterCollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MAP)))
		{
			bGround_ = false;
			bottomCenterCollision_->SetPivot({ 0, BOTTOM_PIVOT + 0 });
			return;
		}


		bottomCenterCollision_->SetPivot({ 0, BOTTOM_PIVOT + 0 });
		// 여기 왔으면 경사라고 본다.
		while (nullptr == bottomCenterCollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MAP)))
		{
			SetMove({ 0.0f, 1.0f });
			pos_.y = static_cast<float>(static_cast<int>(pos_.y));
		}

		SetMove({ 0.0f, -1.0f });
	}
}

StateInfo SuperSheep::startIdle(StateInfo _state)
{
	return StateInfo();
}

StateInfo SuperSheep::updateIdle(StateInfo _state)
{
	return "Walk";
}

StateInfo SuperSheep::startWalk(StateInfo _state)
{
	return StateInfo();
}

StateInfo SuperSheep::updateWalk(StateInfo _state)
{
	addGravity();
	if (bLeft_)
	{
		mainRender_->ChangeAnimation("WalkLeft", std::string("sheepWalkLeft.bmp"));
		speed_.x = -200;
		headCollision_->SetPivot({ -15.f, -5.0f });
	}
	else
	{
		mainRender_->ChangeAnimation("WalkRight", std::string("sheepWalkRight.bmp"));
		speed_.x = 200;
		headCollision_->SetPivot({ 15.f, -5.0f });
	}
	if (nullptr != headCollision_->CollisionGroupCheckOne(eCollisionGroup::MAP))
	{
		bLeft_ = !bLeft_;
		return "Walk";
	}

	if (jumpDelay_ < 0.0f && bGround_)
	{
		jumpDelay_ = JUMP_DELAY;
		SetMove({ 0.0f, -6.f });
		speed_.y = -300.f;
	}
	jumpDelay_ -= deltaTime_;

	if (nullptr != topCenterCollision_->CollisionGroupCheckOne(eCollisionGroup::MAP))
	{
		SetMove({ 0.0f, 2.f });
		speed_.y = 0.0f;
	}

	if (GameEngineInput::GetInst().IsDown("Explosion"))
	{
		return "Explosion";
	}

	normalMove();
	return StateInfo();
}

StateInfo SuperSheep::startExplosion(StateInfo _state)
{
	PlayLevel* level = (PlayLevel*)GetLevel();
	level->CreateExplosion100(pos_);
	explosionDelay_ = 2.0f;
	mainRender_->Off();
	return StateInfo();
}

StateInfo SuperSheep::updateExplosion(StateInfo _state)
{
	explosionDelay_ -= GameEngineTime::GetInst().GetDeltaTime();

	if (explosionDelay_ <= 0)
	{
		parentWorm_->ChangeState("Idle");
		parentWorm_->BulletFocusOff();
		Death();
	}
	return StateInfo();
}
