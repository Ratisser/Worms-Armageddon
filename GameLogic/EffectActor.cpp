#include <GameEngineRenderer.h>

#include "EffectActor.h"

EffectActor::EffectActor() :
	mainSpriteRender_(nullptr),
	GameLevel_(nullptr)
{
}

EffectActor::~EffectActor()
{
}

EffectActor::EffectActor(EffectActor&& _other) noexcept :
	mainSpriteRender_(nullptr),
	GameLevel_(nullptr)
{
}

void EffectActor::Start()
{
}

void EffectActor::UpdateBefore()
{
}

void EffectActor::Update()
{
}

void EffectActor::UpdateAfter()
{
}

void EffectActor::Render()
{
	mainSpriteRender_->AnimationUpdate();
}
