#include "Explosion.h"
#include "EffectCircle.h"
#include "EffectElipse.h"
#include "EffectSmklt.h"
#include "EffectSmkdrk.h"
#include "EffectFlame.h"
#include "GameEngineLevel.h"

// Size25

EffectBundle::Explosion::Size25::Size25()
{
}

EffectBundle::Explosion::Size25::~Size25()
{
}

EffectBundle::Explosion::Size25::Size25(Size25&& _other) noexcept 
{
}

void EffectBundle::Explosion::Size25::Start()
{
}

void EffectBundle::Explosion::Size25::UpdateBefore()
{
}

void EffectBundle::Explosion::Size25::Update()
{
	if (EffectActorList.empty())
	{
		Death();
	}
}

void EffectBundle::Explosion::Size25::UpdateAfter()
{
}

void EffectBundle::Explosion::Size25::Render()
{
}

// Size50

EffectBundle::Explosion::Size50::Size50()
{
}

EffectBundle::Explosion::Size50::~Size50()
{
}

EffectBundle::Explosion::Size50::Size50(Size50&& _other) noexcept
{
}

void EffectBundle::Explosion::Size50::Start()
{
}

void EffectBundle::Explosion::Size50::UpdateBefore()
{
}

void EffectBundle::Explosion::Size50::Update()
{
}

void EffectBundle::Explosion::Size50::UpdateAfter()
{
}

void EffectBundle::Explosion::Size50::Render()
{
}

// Size75

EffectBundle::Explosion::Size75::Size75()
{
}

EffectBundle::Explosion::Size75::~Size75()
{
}

EffectBundle::Explosion::Size75::Size75(Size75&& _other) noexcept
{
}

void EffectBundle::Explosion::Size75::Start()
{
}

void EffectBundle::Explosion::Size75::UpdateBefore()
{
}

void EffectBundle::Explosion::Size75::Update()
{
}

void EffectBundle::Explosion::Size75::UpdateAfter()
{
}

void EffectBundle::Explosion::Size75::Render()
{
}

// Size100

EffectBundle::Explosion::Size100::Size100() 
{
}

EffectBundle::Explosion::Size100::~Size100()
{
}

EffectBundle::Explosion::Size100::Size100(Size100&& _other) noexcept
{
}

void EffectBundle::Explosion::Size100::Start()
{
	EffectActorList.push_back(GameLevel_->CreateActor<Effect::Circle100>());
	EffectActorList.push_back(GameLevel_->CreateActor<Effect::Elipse100>());
}

void EffectBundle::Explosion::Size100::UpdateBefore()
{
}

void EffectBundle::Explosion::Size100::Update()
{
}

void EffectBundle::Explosion::Size100::UpdateAfter()
{
}

void EffectBundle::Explosion::Size100::Render()
{
}
