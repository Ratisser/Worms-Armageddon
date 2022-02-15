#include "EndingImage.h"

#include <EngineEnum.h>
#include <GameEngineWindow.h>
#include <GameEngineRenderer.h>
#include <GameEngineInput.h>
#include <GameEngineLevelManager.h>
#include <GameEngineTime.h>

EndingImage::EndingImage() :
	alpha_(0.0f),
	castalpha_(0),
	fadestop_(false),
	fadeBlackSpriteRender_(nullptr),
	EndingImageRender_(nullptr),
	EndingTimer_{}
{
	SetRenderOrder(static_cast<int>(RenderOrder::BackGround));
}

EndingImage::~EndingImage()
{
}

EndingImage::EndingImage(EndingImage&& _other) noexcept :
	alpha_(0.0f),
	castalpha_(0),
	fadestop_(false),
	fadeBlackSpriteRender_(nullptr),
	EndingImageRender_(nullptr),
	EndingTimer_{}
{
}

void EndingImage::Start()
{
	float4 WindowSize = GameEngineWindow::GetInst().GetSize();
	float4 ImageHarf = float4::ZERO;

	// Fade In/Out 렌더러 생성
	fadeBlackSpriteRender_ = CreateRenderer("Fade_Black");
	ImageHarf = fadeBlackSpriteRender_->GetImageSize().halffloat4();
	fadeBlackSpriteRender_->SetPivotPos(ImageHarf);
	fadeBlackSpriteRender_->Off();

	// 엔딩 FadeInOut
	EndingTimer_.CreateTimeEvent(4.0f, this, nullptr, &EndingImage::EndingFadeStart, &EndingImage::EndingFadeStay, &EndingImage::EndingFadeEnd);

	// 엔딩 이미지 생성 및 Off
	EndingImageRender_ = CreateRenderer("Ending_BackDrop");
	ImageHarf = EndingImageRender_->GetImageSize().halffloat4();
	EndingImageRender_->SetPivotPos(ImageHarf);
	EndingImageRender_->SetRenderSize(WindowSize);
	EndingImageRender_->SetCameraEffectOff();
	EndingImageRender_->Off();
}

void EndingImage::UpdateBefore()
{
}

void EndingImage::Update()
{
	EndingTimer_.Update();
}

void EndingImage::UpdateAfter()
{
}

void EndingImage::Render()
{
	if (true == EndingImageRender_->IsOn())
	{
		EndingImageRender_->Render();
	}

	if (true == fadeBlackSpriteRender_->IsOn())
	{
		fadeBlackSpriteRender_->Render();
	}
}

void EndingImage::EndingFadeStart()
{
	fadeBlackSpriteRender_->On();
	EndingImageRender_->On();

	alpha_ = 2.55f;
	castalpha_ = 255;
	fadestop_ = false;

	fadeBlackSpriteRender_->SetAlpha(castalpha_);
}

void EndingImage::EndingFadeStay()
{
	alpha_ -= GameEngineTime::GetInst().GetDeltaTime();

	if (0.0f >= alpha_)
	{
		alpha_ = 0.0f;
		castalpha_ = 0;
		fadestop_ = true;
		fadeBlackSpriteRender_->Off();
	}
	else
	{
		castalpha_ = static_cast<unsigned char>(alpha_ * 100.f);
	}

	fadeBlackSpriteRender_->SetAlpha(castalpha_);
}

bool EndingImage::EndingFadeEnd()
{
	return fadestop_;
}

