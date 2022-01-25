#include "Sheep.h"

#include <GameEngineCollision.h>
#include <GameEngineRenderer.h>
#include <GameEngineInput.h>

#include "PlayLevel.h"
#include "Worm.h"

#include "eCollisionGroup.h"
#include "eCollisionCheckColor.h"

Sheep::Sheep()
	: state_(this)
	, speed_(float4::ZERO)
	, mainRender_(nullptr)
	, headCollision_(nullptr)
	, bottomCenterCollision_(nullptr)
	, groundCheckCollision_(nullptr)
	, bLeft_(false)
	, bGround_(false)
	, jumpDelay_(JUMP_DELAY)
	, deltaTime_(0.0f)
	, parentWorm_(nullptr)
{

}

Sheep::~Sheep()
{

}

void Sheep::Start()
{
	SetRenderOrder(static_cast<int>(RenderOrder::Weapon));

	// ������
	mainRender_ = CreateRenderer("sheepWalkLeft.bmp");
	mainRender_->CreateAnimation("WalkLeft", "sheepWalkLeft.bmp", 0, 6, true, 0.033f);
	mainRender_->CreateAnimation("WalkRight", "sheepWalkRight.bmp", 0, 6, true, 0.033f);

	mainRender_->ChangeAnimation("WalkRight", std::string("sheepWalkRight.bmp"));

	// �浹ü
	headCollision_ = CreateCollision(eCollisionGroup::WEAPON, CollisionCheckType::POINT);
	headCollision_->SetColorCheck(static_cast<DWORD>(eCollisionCheckColor::MAP));
	
	bottomCenterCollision_ = CreateCollision(eCollisionGroup::WEAPON, CollisionCheckType::POINT);
	bottomCenterCollision_->SetColorCheck(static_cast<DWORD>(eCollisionCheckColor::MAP));
	bottomCenterCollision_->SetPivot({ 0.0f, BOTTOM_PIVOT });

	groundCheckCollision_ = CreateCollision(eCollisionGroup::WEAPON, CollisionCheckType::POINT);
	groundCheckCollision_->SetColorCheck(static_cast<DWORD>(eCollisionCheckColor::MAP));
	groundCheckCollision_->SetPivot({ 0.0f, BOTTOM_PIVOT + 1 });

	// Ű
	if (false == GameEngineInput::GetInst().IsKey("Explosion"))
	{
		GameEngineInput::GetInst().CreateKey("Explosion", VK_SPACE);
	}

	// ����
	state_.CreateState("Walk", &Sheep::startWalk, &Sheep::updateWalk);
	state_.CreateState("Explosion", &Sheep::startExplosion, &Sheep::updateExplosion);
	state_.ChangeState("Walk");
}

void Sheep::UpdateBefore()
{
	mainRender_->AnimationUpdate();
}

void Sheep::Update()
{
	deltaTime_ = GameEngineTime::GetInst().GetDeltaTime();
	state_.Update();
}

void Sheep::UpdateAfter()
{
}

void Sheep::Render()
{
	mainRender_->Render();
}

void Sheep::Initialize(Worm* _parentWorm, bool _bLeft)
{
	parentWorm_ = _parentWorm;
	bLeft_ = _bLeft;
}

void Sheep::addGravity()
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

void Sheep::normalMove()
{
	SetMove(speed_ * deltaTime_);

	// ���� ���� ��
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
			// ���� ���� �� �پ��ִ� ����
			bottomCenterCollision_->SetPivot({ 0, BOTTOM_PIVOT + 0 });
			return;
		}

		// ���������� ����
		bottomCenterCollision_->SetPivot({ 0, BOTTOM_PIVOT + 5 });
		if (nullptr == bottomCenterCollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MAP)))
		{
			bGround_ = false;
			bottomCenterCollision_->SetPivot({ 0, BOTTOM_PIVOT + 0 });
			return;
		}


		bottomCenterCollision_->SetPivot({ 0, BOTTOM_PIVOT + 0 });
		// ���� ������ ����� ����.
		while (nullptr == bottomCenterCollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MAP)))
		{
			SetMove({ 0.0f, 1.0f });
			pos_.y = static_cast<float>(static_cast<int>(pos_.y));
		}

		SetMove({ 0.0f, -1.0f });
	}
}

StateInfo Sheep::startWalk(StateInfo _state)
{
	return StateInfo();
}

StateInfo Sheep::updateWalk(StateInfo _state)
{
	if (bLeft_)
	{
		mainRender_->ChangeAnimation("WalkLeft", "sheepWalkLeft.bmp");
		speed_.x = -200;
		headCollision_->SetPivot({ -15.f, 0.0f });
	}
	else
	{
		mainRender_->ChangeAnimation("WalkRight", "sheepWalkRight.bmp");
		speed_.x = 200;
		headCollision_->SetPivot({ 15.f, 0.0f });
	}

	if (nullptr != headCollision_->CollisionGroupCheckOne(eCollisionGroup::MAP))
	{
		bLeft_ = !bLeft_;
	}

	if (JUMP_DELAY < 0.0f)
	{
		jumpDelay_ = JUMP_DELAY;
		speed_.y = -300.f;
	}
	jumpDelay_ -= deltaTime_;

	if (GameEngineInput::GetInst().IsDown("Explosion"))
	{
		return "Explosion";
	}

	normalMove();
	return StateInfo();
}

StateInfo Sheep::startExplosion(StateInfo _state)
{
	return StateInfo();
}

StateInfo Sheep::updateExplosion(StateInfo _state)
{
	PlayLevel* level = (PlayLevel*)GetLevel();
	level->CreateExplosion100(pos_);
	SetPos(float4(-100.f, -100.f));
	parentWorm_->ChangeState("Idle");
	Death();
	return StateInfo();
}
