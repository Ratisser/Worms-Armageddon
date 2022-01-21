#include "TitleImage.h"

#include <EngineEnum.h>
#include <GameEngineWindow.h>
#include <GameEngineRenderer.h>
#include <GameEngineInput.h>
#include <GameEngineLevelManager.h>

TitleImage::TitleImage() :
	fadeStart_(false),
	fadeEnd_(false),
	introEnd_(false),
	introCnt_(0),
	fadeInOutSpriteRender_(nullptr),
	intrologoSpriteRender_(nullptr),
	titlelogoSpriteRender_(nullptr),
	mainSpriteRender_(nullptr)
{
	SetRenderOrder(static_cast<int>(RenderOrder::BackGround));
}

TitleImage::~TitleImage() // default destructer 디폴트 소멸자
{

}

TitleImage::TitleImage(TitleImage&& _other) noexcept :
	fadeStart_(_other.fadeStart_),
	fadeEnd_(_other.fadeEnd_),
	introEnd_(_other.introEnd_),
	introCnt_(_other.introCnt_),
	fadeInOutSpriteRender_(_other.fadeInOutSpriteRender_),
	intrologoSpriteRender_(_other.intrologoSpriteRender_),
	titlelogoSpriteRender_(_other.titlelogoSpriteRender_),
	mainSpriteRender_(_other.mainSpriteRender_)
{
}

void TitleImage::UpdateBefore()
{

}

void TitleImage::Start()
{
	float4 WindowSize = GameEngineWindow::GetInst().GetSize();
	float4 ImageHarf = float4::ZERO;

	// Fade In/Out 렌더러 생성
	fadeInOutSpriteRender_ = CreateRenderer("Fade_Image");
	ImageHarf = fadeInOutSpriteRender_->GetImageSize().halffloat4();
	fadeInOutSpriteRender_->SetPivotPos(ImageHarf);
	fadeInOutSpriteRender_->Off();

	// 인트로 로고
	intrologoSpriteRender_ = CreateRenderer("Introl_Logo");

	ImageHarf = intrologoSpriteRender_->GetImageSize().halffloat4();

	intrologoSpriteRender_->SetPivotPos(float4(ImageHarf.x, ImageHarf.y + 250.f));
	intrologoSpriteRender_->SetRenderSize(float4(1280.f, 256.f));
	intrologoSpriteRender_->SetCameraEffectOff();

	// 타이틀 로고
	titlelogoSpriteRender_ = CreateRenderer("Title_Logo");
	ImageHarf = titlelogoSpriteRender_->GetImageSize().halffloat4();

	titlelogoSpriteRender_->SetPivotPos(float4(ImageHarf.x + 360.f, ImageHarf.y + 30.f));
	titlelogoSpriteRender_->SetRenderSize(float4(640.f, 128.f));
	titlelogoSpriteRender_->SetCameraEffectOff();
	titlelogoSpriteRender_->Off();

	// 아마겟돈 TEXT
	// AMARGEDDON




	// 타이틀 로고 액터



	// 백그라운드
	mainSpriteRender_ = CreateRenderer("TitleImage");
	ImageHarf = mainSpriteRender_->GetImageSize().halffloat4();
	mainSpriteRender_->SetPivotPos(ImageHarf);
	mainSpriteRender_->SetRenderSize(WindowSize);
	mainSpriteRender_->SetCameraEffectOff();
	mainSpriteRender_->Off();
	
	// 키생성
	if (false == GameEngineInput::GetInst().IsKey("Intro_Skip"))
	{
		GameEngineInput::GetInst().CreateKey("Intro_Skip", VK_SPACE);
	}

	if (false == GameEngineInput::GetInst().IsKey("NextLevel"))
	{
		GameEngineInput::GetInst().CreateKey("NextLevel", 'p');
	}
}

void TitleImage::Update()
{
	if (introCnt_ < 2 && false == fadeStart_)
	{
		if (true == GameEngineInput::GetInst().IsDown("Intro_Skip"))
		{
			++introCnt_;

			// Fade In/Out 실행
			fadeStart_ = true;
		}
	}

	if (true == GameEngineInput::GetInst().IsDown("NextLevel"))
	{
		GameEngineLevelManager::GetInst().ChangeLevel("LobbyLevel");
	}

	if (true == fadeStart_)
	{
		// Fade In/Out Alpha Value Update


		// Fade In/Out End : Value Reset & fadeEnd_ Flag On

	}

	if (true == fadeEnd_)
	{
		// Fade In/Out 종료시 현재 렌더러 OFF상태 다음렌더러 On전환
		if (true == intrologoSpriteRender_->IsOn())
		{
			intrologoSpriteRender_->Off();
			titlelogoSpriteRender_->On();
		}
		else if (true == titlelogoSpriteRender_->IsOn())
		{
			mainSpriteRender_->Off();
		}
	}
}

void TitleImage::UpdateAfter()
{
}


void TitleImage::Render()
{
	// 백그라운드
	if (true == mainSpriteRender_->IsOn())
	{
		mainSpriteRender_->Render();
	}

	// 인트로로고
	if (true == intrologoSpriteRender_->IsOn())
	{
		intrologoSpriteRender_->Render();
	}

	// 타이틀로고
	if (true == titlelogoSpriteRender_->IsOn())
	{
		titlelogoSpriteRender_->Render();
	}

	// 타이틀액터


	// Fade In/Out
	if (true == fadeInOutSpriteRender_->IsOn())
	{
		fadeInOutSpriteRender_->Render();
	}
}
