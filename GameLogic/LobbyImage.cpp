#include "LobbyImage.h"
#include <GameEngineWindow.h>
#include <GameEngineRenderer.h>
LobbyImage::LobbyImage() // default constructer 디폴트 생성자
	: mainSpriteRender_(nullptr)
{
	this->SetPos(GameEngineWindow::GetInst().GetSize().halffloat4());
	SetRenderOrder(1);
}

LobbyImage::~LobbyImage() // default destructer 디폴트 소멸자
{

}

LobbyImage::LobbyImage(LobbyImage&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
	: mainSpriteRender_(nullptr)
{

}

void LobbyImage::Start()
{
	mainSpriteRender_ = CreateRenderer("LobbyImage");
}

void LobbyImage::UpdateBefore()
{

}

void LobbyImage::Update()
{
}

void LobbyImage::UpdateAfter()
{
}


void LobbyImage::Render()
{
	mainSpriteRender_->Render();
}
