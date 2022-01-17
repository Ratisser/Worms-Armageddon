#include "EffectBundleActor.h"
#include "GameEngineLevel.h"

EffectBundleActor::EffectBundleActor()
{
}

EffectBundleActor::~EffectBundleActor()
{
}

EffectBundleActor::EffectBundleActor(EffectBundleActor&& _other) noexcept
{
}

void EffectBundleActor::Start()
{
	auto iter0 = EffectActorList.begin();
	auto iter1 = EffectActorList.end();

	for (; iter0 != iter1; )
	{
		(*iter0)->SetRenderOrder(GetRenderOrder());
		++iter0;
	}
	
}

void EffectBundleActor::UpdateBefore()
{
}

void EffectBundleActor::Update()
{
	auto iter0 = EffectActorList.begin();
	auto iter1 = EffectActorList.end();
		
	for (; iter0 != iter1; )
	{
		if((*iter0)->IsEffectDestroy())
		{
			(*iter0)->Death();

			iter0 = EffectActorList.erase(iter0);
			iter1 = EffectActorList.end();
			continue;
		}
		++iter0;
	}

	if (EffectActorList.empty())
	{
		Death();
	}
}

void EffectBundleActor::UpdateAfter()
{
}

void EffectBundleActor::Render()
{
}

