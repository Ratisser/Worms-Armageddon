#include "Explosion.h"
#include "GameEngineLevel.h"

#include "eCollisionGroup.h"

#include <GameEngineCollision.h>
#include <GameEngineTime.h>
#include <typeinfo>

#include "Worm.h"
#include "PlayLevel.h"

Explosion::Explosion():
	Damage_(0),
	LifeTime_(0.f),
	DamageAll_(false),
	ExplosionCollision_(nullptr)
{
}

Explosion::~Explosion()
{
}

Explosion::Explosion(Explosion&& _other) noexcept :
	Damage_(0),
	LifeTime_(0.f),
	DamageAll_(false),
	ExplosionCollision_(nullptr)
{
}

void Explosion::Start()
{
	ExplosionCollision_ = CreateCollision
	(static_cast<int>(eCollisionGroup::WEAPON), CollisionCheckType::CIRCLE);
}

void Explosion::UpdateBefore()
{
}

void Explosion::Update()
{
	LifeTime_ += GameEngineTime::GetInst().GetDeltaTime();

	if (LifeTime_ > 1.f)
	{
		Death();
		return;
	}

	// eCollisionGroup�� �ϳ��� ����� ������ �Ҵ��ϰ�, Worm�� �浹 ���θ� �˻��ϰ� �ϴ°��� �ξ� ȿ������ ������ ����

	std::list<GameEngineCollision*> ColList_ = ExplosionCollision_->CollisionGroupCheck(static_cast<int>(eCollisionGroup::PLAYER));

	if (false == ColList_.empty())
	{
		auto iter0 = ColList_.begin();
		auto iter1 = ColList_.end();

		for (; iter0 != iter1;)
		{		
#ifdef _DEBUG
			std::string name = (*iter0)->GetActor()->GetName();
			name = name.substr(0, 4);

			if (name != "Worm")
			{
				GameEngineDebug::MsgBoxError("Worm�� �ƴ� �浹ü�� eCollisionGroup::PLAYER�� �����Ǿ����ϴ�.");
			}
			else
			{
				reinterpret_cast<Worm*>(*iter0)->Damage(Damage_);
			}
#endif // _DEBUG

#ifndef _DEBUG
			Worm* wrom = (Worm*)((*iter0)->GetActor());
			wrom->Damage(Damage_);
#endif // !_DEBUG
			++iter0;
		}
	}
}

void Explosion::UpdateAfter()
{
}

void Explosion::Render()
{
#ifdef _DEBUG
	if (GetLevel<PlayLevel>()->GetDebug())
	{
		ExplosionCollision_->DebugRender();
	}
#endif // DEBUG
}

