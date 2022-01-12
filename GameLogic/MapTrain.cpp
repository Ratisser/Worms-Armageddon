#include "MapTrain.h"
#include <GameEngineWindow.h>
#include <GameEngineRenderer.h>
MapTrain::MapTrain() // default constructer ����Ʈ ������
	:mainSpriteRender_(nullptr)
{
	this->SetPos(GameEngineWindow::GetInst().GetSize().halffloat4());
	SetRenderOrder(2);
}

MapTrain::~MapTrain() // default destructer ����Ʈ �Ҹ���
{

}

MapTrain::MapTrain(MapTrain&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
	:mainSpriteRender_(nullptr)
{

}

void MapTrain::Start()
{
	mainSpriteRender_ = CreateRenderer("MapTrain");
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
	mainSpriteRender_->Render();
}

