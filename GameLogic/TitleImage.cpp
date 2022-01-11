#include "TitleImage.h"
#include <GameEngineWindow.h>
#include <GameEngineRenderer.h>
TitleImage::TitleImage() // default constructer 디폴트 생성자
: mainSpriteRender_(nullptr)
{
	this->SetPos(GameEngineWindow::GetInst().GetSize().halffloat4());
	SetRenderOrder(1);
}

TitleImage::~TitleImage() // default destructer 디폴트 소멸자
{

}

TitleImage::TitleImage(TitleImage&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
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
