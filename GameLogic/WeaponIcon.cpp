#include "WeaponIcon.h"
#include "eCollisionGroup.h"

#include <GameEngineLevel.h>
#include <GameEngineRenderer.h>
#include <GameEngineCollision.h>

#include <GameEngineWindow.h>
#include <GameEngineTime.h>

WeaponIcon::WeaponIcon() :
	itemtype_(eItemList::MAX),
	indexX_(-1),
	indexY_(-1),
	index_(-1),
	renderpos_(float4::ZERO),
	mainrenderer_(nullptr),
	maincollision_(nullptr)
{
}

WeaponIcon::~WeaponIcon() // default destructer 디폴트 소멸자
{

}

WeaponIcon::WeaponIcon(WeaponIcon&& _other) noexcept :
	itemtype_(_other.itemtype_),
	indexX_(_other.indexX_),
	indexY_(_other.indexY_),
	index_(_other.index_),
	renderpos_(_other.renderpos_),
	mainrenderer_(_other.mainrenderer_),
	maincollision_(_other.maincollision_)
{

}

void WeaponIcon::Start()
{

}

void WeaponIcon::UpdateBefore()
{
}

void WeaponIcon::Update()
{
}

void WeaponIcon::UpdateAfter()
{
}

void WeaponIcon::Render()
{
	mainrenderer_->Render();
}

