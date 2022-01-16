#include "EffectSmkdrk.h"
#include <GameEngineWindow.h>
#include <GameEngineRenderer.h>



Effect::Smkdrk20::Smkdrk20()
{
}
Effect::Smkdrk20::~Smkdrk20() 
{
}
Effect::Smkdrk20::Smkdrk20(Smkdrk20&& _other) noexcept
{
}

void Effect::Smkdrk20::Start()
{
	mainSpriteRender_ = CreateRenderer("Smkdrk20");
	mainSpriteRender_->CreateAnimation("Smkdrk20", "Smkdrk20", 0, 7, true, 0.1f);
	mainSpriteRender_->ChangeAnimation("Smkdrk20");

	mainSpriteRender_->SetAnimationEndFunction<GameEngineObjectBase>
		("Smkdrk20", this, &GameEngineObjectBase::Death);
}

void Effect::Smkdrk20::UpdateBefore()
{
}

void Effect::Smkdrk20::Update()
{
}

void Effect::Smkdrk20::UpdateAfter()
{
}

void Effect::Smkdrk20::Render()
{
	EffectActor::Render();
}

Effect::Smkdrk30::Smkdrk30()
{
}
Effect::Smkdrk30::~Smkdrk30() 
{
}
Effect::Smkdrk30::Smkdrk30(Smkdrk30&& _other) noexcept
{
}

void Effect::Smkdrk30::Start()
{
	mainSpriteRender_ = CreateRenderer("Smkdrk30");
	mainSpriteRender_->CreateAnimation("Smkdrk30", "Smkdrk30", 0, 7, true, 0.1f);
	mainSpriteRender_->ChangeAnimation("Smkdrk30");

	mainSpriteRender_->SetAnimationEndFunction<GameEngineObjectBase>
		("Smkdrk30",this, &GameEngineObjectBase::Death);
}

void Effect::Smkdrk30::UpdateBefore()
{
}

void Effect::Smkdrk30::Update()
{
}

void Effect::Smkdrk30::UpdateAfter()
{
}

void Effect::Smkdrk30::Render()
{
	EffectActor::Render();
}

Effect::Smkdrk40::Smkdrk40() 
{
}
Effect::Smkdrk40::~Smkdrk40() 
{
}
Effect::Smkdrk40::Smkdrk40(Smkdrk40&& _other) noexcept
{
}

void Effect::Smkdrk40::Start()
{
	mainSpriteRender_ = CreateRenderer("Smkdrk40");
	mainSpriteRender_->CreateAnimation("Smkdrk40", "Smkdrk40", 0, 3, true, 0.1f);
	mainSpriteRender_->ChangeAnimation("Smkdrk40");

	mainSpriteRender_->SetAnimationEndFunction<GameEngineObjectBase>
		("Smkdrk40", this, &GameEngineObjectBase::Death);
}

void Effect::Smkdrk40::UpdateBefore()
{
}

void Effect::Smkdrk40::Update()
{
}

void Effect::Smkdrk40::UpdateAfter()
{
}

void Effect::Smkdrk40::Render()
{
	EffectActor::Render();
}