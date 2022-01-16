#include "EffectSmklt.h"
#include <GameEngineWindow.h>
#include <GameEngineRenderer.h>
#include "EffectActor.h"

Effect::Smklt25::Smklt25()
{
}
Effect::Smklt25::~Smklt25()
{
}

Effect::Smklt25::Smklt25(Smklt25&& _other) noexcept
{
}


void Effect::Smklt25::Start()
{
	mainSpriteRender_ = CreateRenderer("Smklt25");
	mainSpriteRender_->CreateAnimation("Smklt25", "Smklt25", 0, 7, true, 0.1f);
	mainSpriteRender_->ChangeAnimation("Smklt25");

	mainSpriteRender_->SetAnimationEndFunction<GameEngineObjectBase>
		("Smklt25", this, &GameEngineObjectBase::Death);
}

void Effect::Smklt25::UpdateBefore()
{
}

void Effect::Smklt25::Update()
{
}

void Effect::Smklt25::UpdateAfter()
{
}

void Effect::Smklt25::Render()
{
	EffectActor::Render();
}

Effect::Smklt50::Smklt50()
{
}
Effect::Smklt50::~Smklt50()
{
}
Effect::Smklt50::Smklt50(Smklt50&& _other) noexcept
{
}

void Effect::Smklt50::Start()
{
	mainSpriteRender_ = CreateRenderer("Smklt50");
	mainSpriteRender_->CreateAnimation("Smklt50", "Smklt50", 0, 7, true, 0.1f);
	mainSpriteRender_->ChangeAnimation("Smklt50");

	mainSpriteRender_->SetAnimationEndFunction<GameEngineObjectBase>
		("Smklt50", this, &GameEngineObjectBase::Death);
}

void Effect::Smklt50::UpdateBefore()
{
}

void Effect::Smklt50::Update()
{
}

void Effect::Smklt50::UpdateAfter()
{
}

void Effect::Smklt50::Render()
{
	EffectActor::Render();
}

Effect::Smklt75::Smklt75()
{
}
Effect::Smklt75::~Smklt75()
{
}
Effect::Smklt75::Smklt75(Smklt75&& _other) noexcept
{
}

void Effect::Smklt75::Start()
{
	mainSpriteRender_ = CreateRenderer("Smklt75");
	mainSpriteRender_->CreateAnimation("Smklt75", "Smklt75", 0, 3, true, 0.1f);
	mainSpriteRender_->ChangeAnimation("Smklt75");

	mainSpriteRender_->SetAnimationEndFunction<GameEngineObjectBase>
		("Smklt75", this, &GameEngineObjectBase::Death);
}

void Effect::Smklt75::UpdateBefore()
{
}

void Effect::Smklt75::Update()
{
}

void Effect::Smklt75::UpdateAfter()
{
}

void Effect::Smklt75::Render()
{
	EffectActor::Render();
}

Effect::Smklt100::Smklt100()
{
}
Effect::Smklt100::~Smklt100()
{
}
Effect::Smklt100::Smklt100(Smklt100&& _other) noexcept
{
}

void Effect::Smklt100::Start()
{
	mainSpriteRender_ = CreateRenderer("Smklt100");
	mainSpriteRender_->CreateAnimation("Smklt100", "Smklt100", 0, 3, true, 0.1f);
	mainSpriteRender_->ChangeAnimation("Smklt100");

	mainSpriteRender_->SetAnimationEndFunction<GameEngineObjectBase>
		("Smklt100", this, &GameEngineObjectBase::Death);
}

void Effect::Smklt100::UpdateBefore()
{
}

void Effect::Smklt100::Update()
{
}

void Effect::Smklt100::UpdateAfter()
{
}

void Effect::Smklt100::Render()
{
	EffectActor::Render();
}