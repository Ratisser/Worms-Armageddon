#include "LobbyImage.h"
#include <GameEngineWindow.h>
#include <GameEngineRenderer.h>
LobbyImage::LobbyImage() // default constructer ����Ʈ ������
	: mainSpriteRender_(nullptr)
{
	this->SetPos(GameEngineWindow::GetInst().GetSize().halffloat4());
	SetRenderOrder(1);
}

LobbyImage::~LobbyImage() // default destructer ����Ʈ �Ҹ���
{

}

LobbyImage::LobbyImage(LobbyImage&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
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
