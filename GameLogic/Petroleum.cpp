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
	// default constructer ����Ʈ ������
{

}

Petroleum::~Petroleum() // default destructer ����Ʈ �Ҹ���
{

}

Petroleum::Petroleum(Petroleum&& _other) noexcept :
	LifeTime_(0.f),
	mainSpriteRender_(nullptr), // default RValue Copy constructer ����Ʈ RValue ���������
	groundCollision_(nullptr),
	BodyCollision_(nullptr)
{

}

void Petroleum::Start()
{
	mainSpriteRender_ = CreateRenderer("");

	mainSpriteRender_->CreateAnimation("", "", 0, 19, true, 0.1f);

	mainSpriteRender_->ChangeAnimation("");

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



