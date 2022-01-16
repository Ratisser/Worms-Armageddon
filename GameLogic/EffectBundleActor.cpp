#include "EffectBundleActor.h"
#include "GameEngineLevel.h"

EffectBundleActor::EffectBundleActor() :
	GameLevel_(nullptr)
{
}

EffectBundleActor::~EffectBundleActor()
{
}

EffectBundleActor::EffectBundleActor(EffectBundleActor&& _other) noexcept :
	GameLevel_(nullptr)
{
}

void EffectBundleActor::Start()
{
}

void EffectBundleActor::UpdateBefore()
{
}

void EffectBundleActor::Update()
{
}

void EffectBundleActor::UpdateAfter()
{
}

void EffectBundleActor::Render()
{
}

void EffectBundleActor::SetGameLevel(GameEngineLevel* GameLevel)
{
	GameLevel_ = GameLevel;
}
