#include "Worm.h"

#include <GameEngineRenderer.h>
#include <GameEngineInput.h>
#include <GameEngineTime.h>
#include <GameEngineLevelManager.h>
#include <GameEngineLevel.h>

Worm::Worm()
	: mainRender_(nullptr)
{

}

Worm::~Worm() // default destructer 디폴트 소멸자
{

}

Worm::Worm(Worm&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
{

}

void Worm::Start()
{
	SetRenderOrder(100);
	mainRender_ = CreateRenderer("wairlnk");
	mainRender_->CreateAnimation("WalkRight", "wairlnk", 0, 3, true, 0.1f);
	mainRender_->ChangeAnimation("WalkRight");

	if (false == GameEngineInput::GetInst().IsKey("Up"))
	{
		GameEngineInput::GetInst().CreateKey("Up", VK_UP);
	}
	if (false == GameEngineInput::GetInst().IsKey("Down"))
	{
		GameEngineInput::GetInst().CreateKey("Down", VK_DOWN);
	}
	if (false == GameEngineInput::GetInst().IsKey("Left"))
	{
		GameEngineInput::GetInst().CreateKey("Left", VK_LEFT);
	}
	if (false == GameEngineInput::GetInst().IsKey("Right"))
	{
		GameEngineInput::GetInst().CreateKey("Right", VK_RIGHT);
	}

	if (false == GameEngineInput::GetInst().IsKey("WeaponSheet"))
	{
		GameEngineInput::GetInst().CreateKey("WeaponSheet", VK_RBUTTON);
	}
}

void Worm::UpdateBefore()
{
	mainRender_->AnimationUpdate();
}

void Worm::Update()
{
	const float MOVE_SPEED = 300.f;
	float deltaTime = GameEngineTime::GetInst().GetDeltaTime();

	if (true == GameEngineInput::GetInst().IsPress("Left"))
	{
		SetMove(float4::LEFT * MOVE_SPEED * deltaTime);
	}
	else if (true == GameEngineInput::GetInst().IsPress("Right"))
	{
		SetMove(float4::RIGHT * MOVE_SPEED * deltaTime);
	}

	if (true == GameEngineInput::GetInst().IsPress("Up"))
	{
		SetMove(float4::UP * MOVE_SPEED * deltaTime);
	}
	else if (true == GameEngineInput::GetInst().IsPress("Down"))
	{
		SetMove(float4::DOWN * MOVE_SPEED * deltaTime);
	}


	// 아이템창 활성화/비활성화
	if (true == GameEngineInput::GetInst().IsDown("WeaponSheet"))
	{

	}
}

void Worm::UpdateAfter()
{
}

void Worm::Render()
{
	mainRender_->Render();
}

