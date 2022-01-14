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
	float4 imageSize = mainRenderer_->GetImageSize();
	mainRenderer_->SetPivotPos(imageSize.halffloat4());

	bodyCollision_ = CreateCollision(eCollisionGroup::MAP, CollisionCheckType::IMAGE);
	bodyCollision_->SetImage("MapGround");
	//bodyCollision_->SetColorCheck(RGB(0, 0, 0));

	SetRenderOrder(100);
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
	mainRenderer_->Render();
}
