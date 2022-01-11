#include "TitleImage.h"
#include <GameEngineWindow.h>
#include <GameEngineRenderer.h>
TitleImage::TitleImage() // default constructer ����Ʈ ������
: mainSpriteRender_(nullptr)
{
	this->SetPos(GameEngineWindow::GetInst().GetSize().halffloat4());
	SetRenderOrder(1);
}

TitleImage::~TitleImage() // default destructer ����Ʈ �Ҹ���
{

}

TitleImage::TitleImage(TitleImage&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
	: mainSpriteRender_(nullptr)
{

}

void TitleImage::UpdateBefore()
{

}

void TitleImage::Start()
{
	mainSpriteRender_ = CreateRenderer("TitleImage");
}

void TitleImage::Update()
{
}

void TitleImage::UpdateAfter()
{
}


void TitleImage::Render()
{
	mainSpriteRender_->Render();
}
