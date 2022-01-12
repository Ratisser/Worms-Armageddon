#include "Worm.h"

#include <GameEngineRenderer.h>
#include <GameEngineInput.h>
#include <GameEngineTime.h>
#include <GameEngineLevelManager.h>
#include <GameEngineLevel.h>
#include <GameEngineCollision.h>

#include "eCollisionGroup.h"

Worm::Worm()
	: mainRender_(nullptr)
	, groundCollision_(nullptr)
{

}

Worm::~Worm() // default destructer 디폴트 소멸자
{

}

void Worm::Start()
{
	SetRenderOrder(100);
	initRenderer();
	initCollision();
	initInput();
}

void Worm::initRenderer()
{
	mainRender_ = CreateRenderer("walkRight.bmp");

	mainRender_->CreateAnimation("walkRight", "walkRight.bmp", 0, 14, true, 0.1f);
	mainRender_->CreateAnimation("walkLeft", "walkLeft.bmp", 0, 14, true, 0.1f);

	mainRender_->CreateAnimation("jumpReadyLeft", "jumpReadyLeft.bmp", 0, 9, true, 0.03f);
	mainRender_->CreateAnimation("jumpReadyRight", "jumpReadyRight.bmp", 0, 9, true, 0.03f);

	mainRender_->CreateAnimation("flyUpLeft", "flyUpLeft.bmp", 0, 1, true, 0.1f);
	mainRender_->CreateAnimation("flyUpRight", "flyUpRight.bmp", 0, 1, true, 0.1f);

	mainRender_->CreateAnimation("flyDownLeft", "flyDownLeft.bmp", 0, 1, true, 0.1f);
	mainRender_->CreateAnimation("flyDownRight", "flyDownRight.bmp", 0, 1, true, 0.1f);

	mainRender_->CreateAnimation("flyLinkLeft", "flyLinkLeft.bmp", 0, 6, true, 0.1f);
	mainRender_->CreateAnimation("flyLinkRight", "flyLinkRight.bmp", 0, 6, true, 0.1f);

	mainRender_->CreateAnimation("idleLeft", "idleLeft.bmp", 0, 5, true, 0.1f);
	mainRender_->CreateAnimation("idleRight", "idleRight.bmp", 0, 5, true, 0.1f);

	mainRender_->ChangeAnimation("walkRight");
}

void Worm::initInput()
{
	if (false == GameEngineInput::GetInst().IsKey("UpArrow"))
	{
		GameEngineInput::GetInst().CreateKey("UpArrow", VK_UP);
	}
	if (false == GameEngineInput::GetInst().IsKey("DownArrow"))
	{
		GameEngineInput::GetInst().CreateKey("DownArrow", VK_DOWN);
	}
	if (false == GameEngineInput::GetInst().IsKey("LeftArrow"))
	{
		GameEngineInput::GetInst().CreateKey("LeftArrow", VK_LEFT);
	}
	if (false == GameEngineInput::GetInst().IsKey("RightArrow"))
	{
		GameEngineInput::GetInst().CreateKey("RightArrow", VK_RIGHT);
	}
}

void Worm::initCollision()
{
	groundCollision_ = CreateCollision(static_cast<int>(eCollisionGroup::PLAYER), CollisionCheckType::POINT);
	//groundCollision_->SetColorCheck()
}

void Worm::addGravity(float _deltaTime)
{

}

void Worm::UpdateBefore()
{
	mainRender_->AnimationUpdate();
}

void Worm::Update()
{
	const float MOVE_SPEED = 300.f;
	float deltaTime = GameEngineTime::GetInst().GetDeltaTime();

	if (true == GameEngineInput::GetInst().IsPress("LeftArrow"))
	{
		SetMove(float4::LEFT * MOVE_SPEED * deltaTime);
	}
	else if (true == GameEngineInput::GetInst().IsPress("RightArrow"))
	{
		SetMove(float4::RIGHT * MOVE_SPEED * deltaTime);
	}

	if (true == GameEngineInput::GetInst().IsPress("UpArrow"))
	{
		SetMove(float4::UP * MOVE_SPEED * deltaTime);
	}
	else if (true == GameEngineInput::GetInst().IsPress("DownArrow"))
	{
		SetMove(float4::DOWN * MOVE_SPEED * deltaTime);
	}
}

void Worm::UpdateAfter()
{
}

void Worm::Render()
{
	mainRender_->Render();
}

