#include "Petroleum.h"
#include <GameEngineWindow.h>
#include <GameEngineRenderer.h>
#include <GameEngineCollision.h>
#include <GameEngineTime.h>
#include "PlayLevel.h"

#include "eCollisionGroup.h"
#include "eCollisionCheckColor.h"


Petroleum::Petroleum() :
	LifeTime_(0.f),
	mainSpriteRender_(nullptr),
	groundCollision_(nullptr),
	BodyCollision_(nullptr)
	// default constructer 디폴트 생성자
{

}

Petroleum::~Petroleum() // default destructer 디폴트 소멸자
{

}

Petroleum::Petroleum(Petroleum&& _other) noexcept :
	LifeTime_(0.f),
	mainSpriteRender_(nullptr), // default RValue Copy constructer 디폴트 RValue 복사생성자
	groundCollision_(nullptr),
	BodyCollision_(nullptr)
{

}

void Petroleum::Start()
{
	mainSpriteRender_ = CreateRenderer("petrol60");
	mainSpriteRender_->CreateAnimation("petrol60", "petrol60", 0, 19, true, 0.1f);
	mainSpriteRender_->CreateAnimation("petrol50", "petrol60", 0, 19, true, 0.1f);
	mainSpriteRender_->CreateAnimation("petrol40", "petrol60", 0, 19, true, 0.1f);
	mainSpriteRender_->CreateAnimation("petrol30", "petrol60", 0, 19, true, 0.1f);
	mainSpriteRender_->CreateAnimation("petrol20", "petrol60", 0, 19, true, 0.1f);

	mainSpriteRender_->CreateAnimation("petrol-1", "petrol-1", 0, 63, true, 0.1f);
	mainSpriteRender_->CreateAnimation("petrol-2", "petrol-2", 0, 63, true, 0.1f);
	mainSpriteRender_->CreateAnimation("petrol-3", "petrol-3", 0, 63, true, 0.1f);
	mainSpriteRender_->CreateAnimation("petrol-4", "petrol-4", 0, 63, true, 0.1f);

	mainSpriteRender_->ChangeAnimation("petrol60");

	initCollision();
}

void Petroleum::UpdateBefore()
{

}

void Petroleum::Update()
{
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
	groundCollision_ = CreateCollision(static_cast<int>(eCollisionGroup::PETROLEUM), CollisionCheckType::POINT);
	//groundCollision_->SetColorCheck(static_cast<DWORD>(eCollisionCheckColor::MAP));

	BodyCollision_ = CreateCollision(static_cast<int>(eCollisionGroup::PETROLEUM), CollisionCheckType::POINT);
	//BodyCollision_->SetColorCheck(static_cast<DWORD>(eCollisionCheckColor::MAP));
}



