#include "MapGround.h"

#include <GameEngineWindow.h>
#include <GameEngineRenderer.h>
#include <GameEngineCollision.h>
#include <GameEngineSound.h>
#include <GameEngineSoundPlayer.h>
#include "GameEngineImageFile.h"

#include "eCollisionGroup.h"

MapGround::MapGround()
	: mainRenderer_(nullptr)
	, bodyCollision_(nullptr),
	boomSpriteRender_(nullptr)
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
	boomSpriteRender_ = CreateRenderer("Boom");

	bodyCollision_ = CreateCollision(eCollisionGroup::MAP, CollisionCheckType::IMAGE);
	bodyCollision_->SetImage("MapGround");
	//bodyCollision_->SetColorCheck(RGB(0, 0, 0));

	SetRenderOrder((int)RenderOrder::Map);
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
	boomSpriteRender_->Render();
}

void MapGround::GroundUpdate(float4 pos)
{
	//float4 mousepos = GameEngineWindow::GetInst().GetMousePos() + pos;
	GameEngineImageFile* WindowImage = mainRenderer_->GetImage();
	WindowImage->TransCopy(boomSpriteRender_->GetImage(),
		pos,
		{ 100.f, 100.f },
		{ 0.f, 0.f },
		{ 100.f, 100.f },
		RGB(0, 255, 0));
}
