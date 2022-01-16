#include "EffectElipse.h"
#include <GameEngineWindow.h>
#include <GameEngineRenderer.h>



Effect::Elipse25::Elipse25()
{
}
Effect::Elipse25::~Elipse25()
{
}
Effect::Elipse25::Elipse25(Elipse25&& _other) noexcept
{
}

void Effect::Elipse25::Start()
{
	mainSpriteRender_ = CreateRenderer("Elipse25");
	mainSpriteRender_->CreateAnimation("Elipse25", "Elipse25", 0, 7, true, 0.1f);
	mainSpriteRender_->ChangeAnimation("Elipse25");

	mainSpriteRender_->SetAnimationEndFunction<GameEngineObjectBase>("Elipse25", this, &GameEngineObjectBase::Death);
}

void Effect::Elipse25::UpdateBefore()
{
}

void Effect::Elipse25::Update()
{
}

void Effect::Elipse25::UpdateAfter()
{
}

void Effect::Elipse25::Render()
{
	EffectActor::Render();
}

Effect::Elipse50::Elipse50() 
{
}
Effect::Elipse50::~Elipse50()
{
}
Effect::Elipse50::Elipse50(Elipse50&& _other) noexcept
{
}

void Effect::Elipse50::Start()
{
	mainSpriteRender_ = CreateRenderer("Elipse50");
	mainSpriteRender_->CreateAnimation("Elipse50", "Elipse50", 0, 7, true, 0.1f);
	mainSpriteRender_->ChangeAnimation("Elipse50");

	mainSpriteRender_->SetAnimationEndFunction<GameEngineObjectBase>("Elipse50", this, &GameEngineObjectBase::Death);
}

void Effect::Elipse50::UpdateBefore()
{
}

void Effect::Elipse50::Update()
{
}

void Effect::Elipse50::UpdateAfter()
{
}

void Effect::Elipse50::Render()
{
	EffectActor::Render();
}

Effect::Elipse75::Elipse75()
{
}
Effect::Elipse75::~Elipse75()
{
}
Effect::Elipse75::Elipse75(Elipse75&& _other) noexcept
{
}

void Effect::Elipse75::Start()
{
	mainSpriteRender_ = CreateRenderer("Elipse75");
	mainSpriteRender_->CreateAnimation("Elipse75", "Elipse75", 0, 3, true, 0.1f);
	mainSpriteRender_->ChangeAnimation("Elipse75");

	mainSpriteRender_->SetAnimationEndFunction<GameEngineObjectBase>("Elipse75", this, &GameEngineObjectBase::Death);
}

void Effect::Elipse75::UpdateBefore()
{
}

void Effect::Elipse75::Update()
{
}

void Effect::Elipse75::UpdateAfter()
{
}

void Effect::Elipse75::Render()
{
	EffectActor::Render();
}

Effect::Elipse100::Elipse100() 
{
}
Effect::Elipse100::~Elipse100() 
{
}
Effect::Elipse100::Elipse100(Elipse100&& _other) noexcept
{
}

void Effect::Elipse100::Start()
{
	mainSpriteRender_ = CreateRenderer("Elipse100");
	mainSpriteRender_->CreateAnimation("Elipse100", "Elipse100", 0, 3, true, 0.1f);
	mainSpriteRender_->ChangeAnimation("Elipse100");

	mainSpriteRender_->SetAnimationEndFunction<GameEngineObjectBase>("Elipse100", this, &GameEngineObjectBase::Death);
}

void Effect::Elipse100::UpdateBefore()
{
}

void Effect::Elipse100::Update()
{
}

void Effect::Elipse100::UpdateAfter()
{
}

void Effect::Elipse100::Render()
{
	EffectActor::Render();
}