#include "EffectFlame.h"
#include "EffectSmkdrk.h"
#include <GameEngineWindow.h>
#include <GameEngineRenderer.h>

Effect::Flame1::Flame1()
{
}
Effect::Flame1::~Flame1()
{
}
Effect::Flame1::Flame1(Flame1&& _other) noexcept
{
}

void Effect::Flame1::Start()
{
	mainSpriteRender_ = CreateRenderer("flame1");
	mainSpriteRender_->CreateAnimation("flame1", "flame1", 0, 7, true, 0.1f);
	mainSpriteRender_->ChangeAnimation("flame1");

	mainSpriteRender_->SetAnimationEndFunction<EffectActor>
		("flame1", this, &EffectActor::EffectDestroy);
}

void Effect::Flame1::UpdateBefore()
{
}

void Effect::Flame1::Update()
{
	if ((mainSpriteRender_->GetCurAnimationFrame() / 4) == 0)
	{
		GetLevel()->CreateActor<Smkdrk30>();
	}
}

void Effect::Flame1::UpdateAfter()
{
}

void Effect::Flame1::Render()
{
	EffectActor::Render();
}

Effect::Flame2::Flame2()
{
}
Effect::Flame2::~Flame2()
{
}
Effect::Flame2::Flame2(Flame2&& _other) noexcept
{
}

void Effect::Flame2::Start()
{
	mainSpriteRender_ = CreateRenderer("flame2");
	mainSpriteRender_->CreateAnimation("flame2", "flame2", 0, 7, true, 0.1f);
	mainSpriteRender_->ChangeAnimation("flame2");

	mainSpriteRender_->SetAnimationEndFunction<EffectActor>
		("flame2", this, &EffectActor::EffectDestroy);
}

void Effect::Flame2::UpdateBefore()
{
}

void Effect::Flame2::Update()
{
	if ((mainSpriteRender_->GetCurAnimationFrame() / 4) == 0)
	{
		GetLevel()->CreateActor<Smkdrk30>();
	}
}

void Effect::Flame2::UpdateAfter()
{
}

void Effect::Flame2::Render()
{
	EffectActor::Render();
}