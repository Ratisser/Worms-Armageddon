#include "MapGround.h"

#include <GameEngineRenderer.h>
#include <GameEngineCollision.h>
#include <GameEngineSound.h>
#include <GameEngineSoundPlayer.h>

#include "eCollisionGroup.h"

MapGround::MapGround()
	: mainRenderer_(nullptr)
	, bodyCollision_(nullptr)
{

}

MapGround::~MapGround()
{

}

void MapGround::Start()
{
	mainRenderer_ = CreateRenderer("MapGround");

	bodyCollision_ = CreateCollision(eCollisionGroup::MAP, CollisionCheckType::IMAGE);
	//bodyCollision_->SetColorCheck(RGB(0, 0, 0));
}

void MapGround::UpdateBefore()
{
}

void MapGround::Update()
{
}

void MapGround::UpdateAfter()
{
}

void MapGround::Render()
{
	//mainRenderer_->Render();
}