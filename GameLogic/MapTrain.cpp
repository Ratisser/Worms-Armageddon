#include "MapTrain.h"
#include <GameEngineWindow.h>
#include <GameEngineRenderer.h>
#include "GameEngineImage.h"
#include "GameEngineImageFile.h"

MapTrain::MapTrain() // default constructer ����Ʈ ������
	:mainSpriteRender_(nullptr),
	backGroundSpriteRender_(nullptr),
	boomSpriteRender_(nullptr)
{
	this->SetPos(GameEngineWindow::GetInst().GetSize().halffloat4());
	SetRenderOrder(2);
}

MapTrain::~MapTrain() // default destructer ����Ʈ �Ҹ���
{

}

MapTrain::MapTrain(MapTrain&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
	:mainSpriteRender_(nullptr),
	backGroundSpriteRender_(nullptr),
	boomSpriteRender_(nullptr)
{

}

void MapTrain::Start()
{
	backGroundSpriteRender_ = CreateRenderer("Ground");
	mainSpriteRender_ = CreateRenderer("MapTrain");
	boomSpriteRender_ = CreateRenderer("Boom");
}

void MapTrain::UpdateBefore()
{

}

void MapTrain::Update()
{

}

void MapTrain::UpdateAfter()
{

}

void MapTrain::Render()
{
	backGroundSpriteRender_->Render();
	mainSpriteRender_->Render();
}

void MapTrain::GroundUpdate()
{
	float4 mousepos = GameEngineWindow::GetInst().GetMousePos() + float4(1230.f, 280.f, 0.f, 0.f);
	GameEngineImageFile* WindowImage = mainSpriteRender_->GetImage();
	WindowImage->TransCopy(boomSpriteRender_->GetImage(),
		mousepos,
		{ 100.f, 100.f },
		{ 0.f, 0.f },
		{ 100.f, 100.f },
		RGB(0, 255, 0));
}

