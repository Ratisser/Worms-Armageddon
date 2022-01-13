#include "DrumActor.h"
#include <GameEngineWindow.h>
#include <GameEngineRenderer.h>
#include <GameEngineCollision.h>
#include "eCollisionGroup.h"

DrumActor::DrumActor():
	Phase_(0.f),
	mainSpriteRender_(nullptr),
	groundCollision_(nullptr)
	// default constructer 디폴트 생성자
{

}

DrumActor::~DrumActor() // default destructer 디폴트 소멸자
{

}

DrumActor::DrumActor(DrumActor&& _other) noexcept :
	Phase_(0.f),
	mainSpriteRender_(nullptr) , // default RValue Copy constructer 디폴트 RValue 복사생성자
	groundCollision_(nullptr)  // default RValue Copy constructer 디폴트 RValue 복사생성자
{

}

void DrumActor::Start()
{
	mainSpriteRender_ = CreateRenderer("oildrum1");

	mainSpriteRender_->CreateAnimation("Phase0", "oildrum1", 0, 19, false, 0.1f);
	mainSpriteRender_->CreateAnimation("Phase1", "oildrum2", 0, 19, false, 0.1f);
	mainSpriteRender_->CreateAnimation("Phase2", "oildrum3", 0, 19, false, 0.1f);
	mainSpriteRender_->CreateAnimation("Phase3", "oildrum4", 0, 19, false, 0.1f);

	mainSpriteRender_->ChangeAnimation("Phase0");
}

void DrumActor::UpdateBefore()
{

}

void DrumActor::Update()
{
}

void DrumActor::UpdateAfter()
{
}


void DrumActor::Render()
{
	mainSpriteRender_->AnimationUpdate();
}

void DrumActor::initCollision()
{
	groundCollision_ = CreateCollision(static_cast<int>(eCollisionGroup::GIMMICK_OBJECT), CollisionCheckType::POINT);
}