#include "LobbyImage.h"
#include "eCollisionGroup.h"
#include "LobbyHost.h"

#include <GameEngineWindow.h>
#include <GameEngineInput.h>
#include <GameEngineRenderer.h>
#include <GameEngineCollision.h>

LobbyImage::LobbyImage() :
	hostready_(false),
	backdropSpriteRender_(nullptr),
	hostboxSpriteRender_(nullptr),
	playerselInputSpriteRender_(nullptr),
	playerboxSpriteRender_(nullptr),
	hostreadySpriteRender_(nullptr),
	playerselboxSpriteRender_(nullptr),
	hostreadyCollision_(nullptr)
{
	SetRenderOrder(static_cast<int>(RenderOrder::BackGround));
}

LobbyImage::~LobbyImage() // default destructer 디폴트 소멸자
{

}

LobbyImage::LobbyImage(LobbyImage&& _other) noexcept :
	hostready_(_other.hostready_),
	backdropSpriteRender_(_other.backdropSpriteRender_),
	hostboxSpriteRender_(_other.hostboxSpriteRender_),
	playerboxSpriteRender_(_other.playerboxSpriteRender_),
	hostreadySpriteRender_(_other.hostreadySpriteRender_),
	playerselInputSpriteRender_(_other.playerselInputSpriteRender_),
	playerselboxSpriteRender_(_other.playerselboxSpriteRender_),
	hostreadyCollision_(_other.hostreadyCollision_)
{
}

void LobbyImage::Start()
{
	float4 Resoultion = GameEngineWindow::GetInst().GetSize();

	// 배경
	backdropSpriteRender_ = CreateRenderer("Lobby_Backdrop");
	backdropSpriteRender_->SetRenderSize(Resoultion);
	backdropSpriteRender_->SetPivotPos({ 16.f, 250.f });
	backdropSpriteRender_->SetCameraEffectOff();

	// Host Display Box
	hostboxSpriteRender_ = CreateRenderer("Lobby_HostBox");
	float4 ImageHarfSize = hostboxSpriteRender_->GetImageSize().halffloat4();
	hostboxSpriteRender_->SetPivotPos(float4(ImageHarfSize.x + 10.f, ImageHarfSize.y + 10.f));
	hostboxSpriteRender_->SetRenderSize(float4(200.f, 210.f));
	hostboxSpriteRender_->SetCameraEffectOff();

	// Player Display Box
	playerboxSpriteRender_ = CreateRenderer("Lobby_PlayerBox");
	ImageHarfSize = playerboxSpriteRender_->GetImageSize().halffloat4();
	playerboxSpriteRender_->SetPivotPos(float4(ImageHarfSize.x + 220.f, ImageHarfSize.y + 10.f));
	playerboxSpriteRender_->SetRenderSize(float4(250.f, 180.f));
	playerboxSpriteRender_->SetCameraEffectOff();

	// Host Ready Button Image
	hostreadySpriteRender_ = CreateRenderer("Lobby_HostReadyOff");
	ImageHarfSize = hostreadySpriteRender_->GetImageSize().halffloat4();
	hostreadySpriteRender_->SetPivotPos(float4(ImageHarfSize.x + 10.f, ImageHarfSize.y + 230.f));
	hostreadySpriteRender_->SetRenderSize(float4(200.f, 150.f));
	hostreadySpriteRender_->SetCameraEffectOff();

	hostreadyCollision_ = CreateCollision(static_cast<int>(eCollisionGroup::UI), CollisionCheckType::RECT);
	hostreadyCollision_->SetSize(float4(200.f, 150.f));
	hostreadyCollision_->SetPivot(float4(100.f + 10.f, 75.f + 250.f));

	// Player Select Box
	playerselInputSpriteRender_ = CreateRenderer("Lobby_SelPlayerInput");
	ImageHarfSize = playerselInputSpriteRender_->GetImageSize().halffloat4();
	playerselInputSpriteRender_->SetPivotPos(float4(ImageHarfSize.x + 220.f, ImageHarfSize.y + 200.f));
	playerselInputSpriteRender_->SetRenderSize(float4(250.f, 32.f));
	playerselInputSpriteRender_->SetCameraEffectOff();

	playerselboxSpriteRender_ = CreateRenderer("Lobby_SelPlayerBox");
	ImageHarfSize = playerselboxSpriteRender_->GetImageSize().halffloat4();
	playerselboxSpriteRender_->SetPivotPos(float4(ImageHarfSize.x + 220.f, ImageHarfSize.y + 232.f));
	playerselboxSpriteRender_->SetRenderSize(float4(250.f, 150.f));
	playerselboxSpriteRender_->SetCameraEffectOff();

	// 키생성
	if (false == GameEngineInput::GetInst().IsKey("Host_Ready"))
	{
		GameEngineInput::GetInst().CreateKey("Host_Ready", VK_LBUTTON);
	}
}

void LobbyImage::UpdateBefore()
{
	// Host Ready
	GameEngineCollision* ColUI = hostreadyCollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MOUSE));
	if (nullptr != ColUI)
	{
		if (true == GameEngineInput::GetInst().IsDown("Host_Ready"))
		{
			if (true == hostready_)
			{
				hostreadySpriteRender_->SetImage("Lobby_HostReadyOff");
				float4 ImageHarfSize = hostreadySpriteRender_->GetImageSize().halffloat4();
				hostreadySpriteRender_->SetPivotPos(float4(ImageHarfSize.x + 10.f, ImageHarfSize.y + 230.f));
				hostreadySpriteRender_->SetRenderSize(float4(200.f, 150.f));
				hostready_ = false;

				// 현재 호스트에게 전달
				LobbyHost::SetCurHostReady(hostready_);
			}
			else
			{
				hostreadySpriteRender_->SetImage("Lobby_HostReadyOn");
				float4 ImageHarfSize = hostreadySpriteRender_->GetImageSize().halffloat4();
				hostreadySpriteRender_->SetPivotPos(float4(ImageHarfSize.x + 10.f, ImageHarfSize.y + 230.f));
				hostreadySpriteRender_->SetRenderSize(float4(200.f, 150.f));
				hostready_ = true;

				// 현재 호스트에게 전달
				LobbyHost::SetCurHostReady(hostready_);
			}
		}
	}

	// Player Select

	// Game Option Select

}

void LobbyImage::Update()
{
}

void LobbyImage::UpdateAfter()
{
}


void LobbyImage::Render()
{
	// 배경
	backdropSpriteRender_->Render();

	// 그밖 박스
	hostboxSpriteRender_->Render();
	playerboxSpriteRender_->Render();
	playerselboxSpriteRender_->Render();
	playerselInputSpriteRender_->Render();

	// Host Ready Button
	hostreadySpriteRender_->Render();
}
