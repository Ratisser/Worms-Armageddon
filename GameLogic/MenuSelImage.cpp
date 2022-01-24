#include "MenuSelImage.h"
#include "eCollisionGroup.h"
#include <EngineEnum.h>

#include <GameEngineLevelManager.h>
#include <GameEngineRenderer.h>
#include <GameEngineCollision.h>

#include <GameEngineWindow.h>
#include <GameEngineTime.h>
#include <GameEngineInput.h>

MenuSelImage::MenuSelImage() :
	menusel_(false),
	alpha_(2.55f),
	castalpha_(255),
	mainrenderer_(nullptr),
	maincollider_(nullptr),
	faderenderer_(nullptr)
{
	SetRenderOrder(static_cast<int>(RenderOrder::UI));
}

MenuSelImage::~MenuSelImage()
{

}

MenuSelImage::MenuSelImage(MenuSelImage&& _other) noexcept :
	alpha_(_other.alpha_),
	castalpha_(_other.castalpha_),
	menusel_(_other.menusel_),
	mainrenderer_(_other.mainrenderer_),
	maincollider_(_other.maincollider_),
	faderenderer_(_other.faderenderer_)
{

}

void MenuSelImage::Start()
{
	float4 WindowSize = GameEngineWindow::GetInst().GetSize();

	// 로비진입 메뉴 렌더러
	mainrenderer_ = CreateRenderer("MenuSelect_Image");
	float4 ImageSizeHarf = mainrenderer_->GetImageSize().halffloat4();
	mainrenderer_->SetPivotPos(float4(ImageSizeHarf.x + 320.f, ImageSizeHarf.y + 250.f));
	mainrenderer_->SetRenderSize(float4(600.f, 300.f));
	mainrenderer_->SetCameraEffectOff();

	// 로비진입 메뉴 충돌체
	maincollider_ = CreateCollision(static_cast<int>(eCollisionGroup::UI), CollisionCheckType::RECT);
	maincollider_->SetSize(float4(600.f, 300.f));
	maincollider_->SetPivot(float4(300.f + 320.f, 150.f + 250.f));

	// Fade In/Out Black
	faderenderer_ = CreateRenderer("Fade_Black");
	ImageSizeHarf = faderenderer_->GetImageSize().halffloat4();
	faderenderer_->SetPivotPos(ImageSizeHarf);
	faderenderer_->SetCameraEffectOff();
	faderenderer_->Off();
	
	if (false == GameEngineInput::GetInst().IsKey("Move_LobbyLevel"))
	{
		GameEngineInput::GetInst().CreateKey("Move_LobbyLevel", VK_LBUTTON);
	}
}

void MenuSelImage::UpdateBefore()
{
	GameEngineCollision* ColUI = maincollider_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MOUSE));
	if (nullptr != ColUI)
	{
		if (true == GameEngineInput::GetInst().IsDown("Move_LobbyLevel"))
		{
			GameEngineLevelManager::GetInst().ChangeLevel("LobbyLevel", true);

			//if (false == menusel_)
			//{
			//	faderenderer_->On();

			//	alpha_ = 2.55f;
			//	castalpha_ = 255;

			//	faderenderer_->SetAlpha(castalpha_);

			//	menusel_ = true;
			//}
		}
	}

	if (true == menusel_ && true == faderenderer_->IsOn())
	{
		//ChangeLevel();
	}
}

void MenuSelImage::Update()
{
}

void MenuSelImage::UpdateAfter()
{
}

void MenuSelImage::Render()
{
	mainrenderer_->Render();

	if (true == faderenderer_->IsOn())
	{
		faderenderer_->Render();
	}
}

void MenuSelImage::ChangeLevel()
{
	alpha_ -= GameEngineTime::GetInst().GetDeltaTime() * GameEngineTime::GetInst().GetDeltaTime();

	if (0.0f >= alpha_)
	{
		alpha_ = 0.0f;
		castalpha_ = 0;
		faderenderer_->Off();

		menusel_ = false;

		// Fade End Level Change
		GameEngineLevelManager::GetInst().ChangeLevel("LobbyLevel", true);
	}
	else
	{
		castalpha_ = static_cast<unsigned char>(alpha_ * 100.f);
	}

	faderenderer_->SetAlpha(castalpha_);
}
