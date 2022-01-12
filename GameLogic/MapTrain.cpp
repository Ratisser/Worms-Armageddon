#include "MapTrain.h"
#include <GameEngineWindow.h>
#include <GameEngineRenderer.h>
MapTrain::MapTrain() // default constructer 디폴트 생성자
	:mainSpriteRender_(nullptr)
{
	this->SetPos(GameEngineWindow::GetInst().GetSize().halffloat4());
	SetRenderOrder(2);
}

MapTrain::~MapTrain() // default destructer 디폴트 소멸자
{

}

MapTrain::MapTrain(MapTrain&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
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

