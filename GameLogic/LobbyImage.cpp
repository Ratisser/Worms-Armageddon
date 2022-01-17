#include "LobbyImage.h"
#include <GameEngineWindow.h>
#include <GameEngineRenderer.h>

LobbyImage::LobbyImage() // default constructer ����Ʈ ������
	: mainSpriteRender_(nullptr)
{

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
	float4 Resoultion = GameEngineWindow::GetInst().GetSize();

	SetRenderOrder(static_cast<int>(RenderOrder::BackGround));
	mainSpriteRender_ = CreateRenderer("Lobby_Backdrop");
	mainSpriteRender_->SetRenderSize(Resoultion);
	mainSpriteRender_->SetPivotPos({ 16.f, 240.f });
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
