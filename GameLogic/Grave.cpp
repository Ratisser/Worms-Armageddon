#include <GameEngineTime.h>
#include <GameEngineRenderer.h>
#include <GameEngineCollision.h>

#include "eCollisionCheckColor.h"
#include "eCollisionGroup.h"

#include "Grave.h"

Grave::Grave():
	GravitySpeed_(0.f),
	GravityAcc_(0.f),
	bound_(3),
	state_(this)
	// default constructer 디폴트 생성자
{

}

Grave::~Grave() // default destructer 디폴트 소멸자
{

}

void Grave::Start()
{
	GameEngineMath::Random random;
	int Randomint = random.RandomInt(0, 5);

	SetRenderOrder(static_cast<int>(RenderOrder::Drum));
	mainSpriteRender_ = CreateRenderer("grave1");

	switch (Randomint)
	{
	case 0:	
		mainSpriteRender_->CreateAnimation("grave1", "grave1", 0, 19, true, 0.05f);
		mainSpriteRender_->ChangeAnimation("grave1", std::string("grave1"));
		break;
	case 1:
		mainSpriteRender_->CreateAnimation("grave2", "grave2", 0, 19, true, 0.05f);
		mainSpriteRender_->ChangeAnimation("grave2", std::string("grave2"));
		break;
	case 2:
		mainSpriteRender_->CreateAnimation("grave3", "grave3", 0, 19, true, 0.05f);
		mainSpriteRender_->ChangeAnimation("grave3", std::string("grave3"));
		break;
	case 3:
		mainSpriteRender_->CreateAnimation("grave4", "grave4", 0, 19, true, 0.05f);
		mainSpriteRender_->ChangeAnimation("grave4", std::string("grave4"));
		break;
	case 4:
		mainSpriteRender_->CreateAnimation("grave5", "grave5", 0, 19, true, 0.05f);
		mainSpriteRender_->ChangeAnimation("grave5", std::string("grave5"));
		break;
	case 5:
		mainSpriteRender_->CreateAnimation("grave6", "grave6", 0, 19, true, 0.05f);
		mainSpriteRender_->ChangeAnimation("grave6", std::string("grave6"));
		break;
	}

	state_.CreateState("Air",&Grave::StartAir, &Grave::UpdateAir);
	state_.CreateState("Ground", &Grave::StartGround, &Grave::UpdateGround);

	state_.ChangeState("Air");

	GravityAcc_ = -100.f;

	initCollision();
}

void Grave::UpdateBefore()
{
}

void Grave::Update()
{
	deltaTime_ = GameEngineTime::GetInst().GetDeltaTime();
	state_.Update();
}

void Grave::UpdateAfter()
{
}

void Grave::Render()
{
	mainSpriteRender_->AnimationUpdateReverseLoop();
}

StateInfo Grave::StartAir(StateInfo)
{
	return StateInfo();
}

StateInfo Grave::UpdateAir(StateInfo)
{
	if (nullptr != groundCollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MAP)))
	{
		bound_--;
		GravityAcc_ = 0.f;

		if (bound_ == 0)
		{
			return "Ground";
		}

		else
		{
			if (GravitySpeed_ > 0.f)
			{
				GravitySpeed_ *= -1.f;
			}

			GravitySpeed_ *= 0.5f;

		}
	}

	SetMove(0.f, GravitySpeed_ * deltaTime_);
	//GravitySpeed_ += GravityAcc_;
	//GravityAcc_ += 1.f;
	return StateInfo();
}

StateInfo Grave::StartGround(StateInfo)
{
	bound_ = 3;
	GravitySpeed_ = 200.f;

	return StateInfo();
}

StateInfo Grave::UpdateGround(StateInfo)
{
	if (nullptr == groundCollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MAP)))
	{
		return "Air";
	}

	return StateInfo();
}


void Grave::initCollision()
{
	groundCollision_ = CreateCollision(static_cast<int>(eCollisionGroup::GRAVE), CollisionCheckType::POINT);
	groundCollision_->SetColorCheck(static_cast<DWORD>(eCollisionCheckColor::MAP));
	groundCollision_->SetPivot({ 0.f, 5.f });
}
