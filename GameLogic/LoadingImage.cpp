#include "LoadingImage.h"
#include <GameEngineWindow.h>
#include <GameEngineRenderer.h>
#include <GameEngineLevelManager.h>

LoadingImage::LoadingImage() // default constructer ����Ʈ ������
	:mainSpriteRender_(nullptr)
{
	this->SetPos(GameEngineWindow::GetInst().GetSize().halffloat4());
	SetRenderOrder(1);
}

LoadingImage::~LoadingImage() // default destructer ����Ʈ �Ҹ���
{

}

LoadingImage::LoadingImage(LoadingImage&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
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
	// �ε� �ִϸ��̼� �������������̶�� �� �ڵ���ȯ
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
