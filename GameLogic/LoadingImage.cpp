#include "LoadingImage.h"
#include <GameEngineWindow.h>
#include <GameEngineRenderer.h>
#include <GameEngineLevelManager.h>

LoadingImage::LoadingImage() // default constructer 디폴트 생성자
	:mainSpriteRender_(nullptr)
{
	this->SetPos(GameEngineWindow::GetInst().GetSize().halffloat4());
	SetRenderOrder(1);
}

LoadingImage::~LoadingImage() // default destructer 디폴트 소멸자
{

}

LoadingImage::LoadingImage(LoadingImage&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
	:mainSpriteRender_(nullptr)
{

}

void LoadingImage::Start()
{
	mainSpriteRender_ = CreateRenderer("LoadingSprites");
	mainSpriteRender_->CreateAnimation("Start", "LoadingSprites", 0, 24, false, 0.1f);
	mainSpriteRender_->ChangeAnimation("Start");
}

void LoadingImage::UpdateBefore()
{

}

void LoadingImage::Update()
{
	// 로딩 애니메이션 마지막프레임이라면 씬 자동전환
	if (24 == mainSpriteRender_->GetCurAnimationFrame())
	{
		GameEngineLevelManager::GetInst().ChangeLevel("PlayLevel", true);
	}
}

void LoadingImage::UpdateAfter()
{
}


void LoadingImage::Render()
{
	mainSpriteRender_->AnimationUpdate();
}
