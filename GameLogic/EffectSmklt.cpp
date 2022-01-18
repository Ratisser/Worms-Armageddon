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
	mainSpriteRender_ = CreateRenderer("smklt25");
	mainSpriteRender_->CreateAnimation("smklt25", "smklt25", 0, 27, false, 0.025f);
	mainSpriteRender_->ChangeAnimation("smklt25");

	mainSpriteRender_->SetAnimationEndFunction<EffectActor>
		("smklt25", this, &EffectActor::Death);

	GameEngineMath::Random random;
	int randint = random.RandomInt(0, 7);

	mainSpriteRender_->SetAnimationCurrentFrame("smklt25", randint);
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
	mainSpriteRender_ = CreateRenderer("smklt50");
	mainSpriteRender_->CreateAnimation("smklt50", "smklt50", 0, 27, false, 0.025f);
	mainSpriteRender_->ChangeAnimation("smklt50");

	mainSpriteRender_->SetAnimationEndFunction<EffectActor>
		("smklt50", this, &EffectActor::Death);

	GameEngineMath::Random random;
	int randint = random.RandomInt(0, 7);

	mainSpriteRender_->SetAnimationCurrentFrame("smklt50", randint);
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
	mainSpriteRender_ = CreateRenderer("smklt75");
	mainSpriteRender_->CreateAnimation("smklt75", "smklt75", 0, 27, false, 0.025f);
	mainSpriteRender_->ChangeAnimation("smklt75");

	mainSpriteRender_->SetAnimationEndFunction<EffectActor>
		("smklt75", this, &EffectActor::Death);

	GameEngineMath::Random random;
	int randint = random.RandomInt(0, 7);

	mainSpriteRender_->SetAnimationCurrentFrame("smklt75", randint);
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
	mainSpriteRender_ = CreateRenderer("smklt100");
	mainSpriteRender_->CreateAnimation("smklt100", "smklt100", 0, 27, false, 0.025f);
	mainSpriteRender_->ChangeAnimation("smklt100");

	mainSpriteRender_->SetAnimationEndFunction<EffectActor>
		("smklt100", this, &EffectActor::Death);

	GameEngineMath::Random random;
	int randint = random.RandomInt(0, 7);

	mainSpriteRender_->SetAnimationCurrentFrame("smklt100", randint);
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