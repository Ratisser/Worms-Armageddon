#include "Explosion.h"
#include "GameEngineLevel.h"

#include "eCollisionGroup.h"

#include <GameEngineCollision.h>
#include <GameEngineTime.h>
#include <typeinfo>

#include "Worm.h"

Explosion::Explosion():
#ifdef _DEBUG
	LifeTime_(0.f),
#endif // DEBUG
	Damage_(0),
	DamageAll_(false),
	ExplosionCollision_(nullptr)

{
}

Explosion::~Explosion()
{
}

Explosion::Explosion(Explosion&& _other) noexcept :
#ifdef _DEBUG
	LifeTime_(0.f),
#endif // DEBUG
	Damage_(0),
	DamageAll_(false),
	ExplosionCollision_(nullptr)
{
}

void Explosion::Start()
{
	ExplosionCollision_ = CreateCollision
	(static_cast<int>(eCollisionGroup::WEAPON), CollisionCheckType::RECT);
}

void Explosion::UpdateBefore()
{
}

void Explosion::Update()
{
#ifdef _DEBUG
	{//����� �ڵ�
		float deltaTime = GameEngineTime::GetInst().GetDeltaTime();

		LifeTime_ += deltaTime;

		if (LifeTime_ > 3.f)
		{
			Death();
		}
	}
#endif // DEBUG

	std::list<GameEngineCollision*> ColList =
		ExplosionCollision_->CollisionGroupCheck((int)eCollisionGroup::PLAYER);

	if (false == ColList.empty())
	{
		auto iter0 = ColList.begin();
		auto iter1 = ColList.end();

		for (; iter0 != iter1;)
		{		
#ifdef _DEBUG
			std::string name = (*iter0)->GetActor()->GetName();
			name = name.substr(0, 4);

			if (name != "Worm")
			{
				GameEngineDebug::MsgBoxError("Worm�� �ƴ� �浹ü");
			}
			else
			{
				reinterpret_cast<Worm*>(*iter0)->Damage(Damage_);
				//Worm* wrom = (Worm*)((*iter0)->GetActor());
				//wrom->Damage(Damage_);
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
	ExplosionCollision_->DebugRender();
#endif // DEBUG
}

