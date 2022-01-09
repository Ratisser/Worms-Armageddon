#include "Monster.h"
#include "LogicEnum.h"
#include <GameEngineCollision.h>


// Static Var
// Static Func

// constructer destructer
Monster::Monster()
{
}

Monster::~Monster()
{
}

Monster::Monster(Monster&& _other) noexcept
{
}


//member Func

void Monster::Start()
{
	SetRenderOrder(1000);
	SetPos({1000, 500});

	MonsterBodyCollision = CreateCollision(ST2GROUP::MONSTER, CollisionCheckType::RECT);
	MonsterBodyCollision->SetSize({50, 100});
}

void Monster::Collision() 
{

}

void Monster::Render()
{
	MonsterBodyCollision->DebugRender();
}