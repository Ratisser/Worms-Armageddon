#include "LobbySelectablePlayer.h"
#include "LobbyCreateTeam.h"
#include "eCollisionGroup.h"

#include <EngineEnum.h>
#include <GameEngineWindow.h>
#include <GameEngineImage.h>
#include <GameEngineImageFile.h>
#include <GameEngineInput.h>
#include <GameEngineRenderer.h>
#include <GameEngineCollision.h>

LobbySelectablePlayer::LobbySelectablePlayer() :
	ShowPlayer_(false),
	Index_(-1),
	NamePos_(float4::ZERO),
	mainrenderer_(nullptr),
	maincollision_(nullptr)
{
	SetRenderOrder(static_cast<int>(RenderOrder::UI1));
}

LobbySelectablePlayer::~LobbySelectablePlayer()
{
}

LobbySelectablePlayer::LobbySelectablePlayer(LobbySelectablePlayer&& _other) noexcept :
	ShowPlayer_(_other.ShowPlayer_),
	Index_(_other.Index_), 
	NamePos_(_other.NamePos_),
	mainrenderer_(_other.mainrenderer_),
	maincollision_(_other.maincollision_)
{
}

void LobbySelectablePlayer::Start()
{
}

void LobbySelectablePlayer::UpdateBefore()
{
	// 마우스와 충돌체크
	GameEngineCollision* ColUI = maincollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MOUSE));
	if (nullptr != ColUI)
	{
		if (true == GameEngineInput::GetInst().IsDown("LobbyLevel_MouseLButton"))
		{
			// 선택된 플레이어 off 상태가되며 LobbyCreateTeam에 현재 선택된 플레이어 이름을 전달
			//ShowPlayer_ = false; // 임시주석

			LobbyCreateTeam::SelectPlayer(Name_, Index_);
		}
	}
}

void LobbySelectablePlayer::Update()
{
}

void LobbySelectablePlayer::UpdateAfter()
{
}

void LobbySelectablePlayer::Render()
{
	// 화면상에 표시하는 것만 표시
	if (true == ShowPlayer_)
	{
		// 플레이어 이미지 표시
		if (nullptr != mainrenderer_)
		{
			mainrenderer_->Render();
		}

		// 플레이어 명칭 표시
		if (!Name_.empty())
		{
			TextOut(GameEngineImage::GetInst().GetBackBufferImage()->GetDC(), NamePos_.ix(), NamePos_.iy(), Name_.c_str(), lstrlen(Name_.c_str()));
		}
	}
}

std::string LobbySelectablePlayer::GetPlayerName() const
{
	return Name_;
}

int LobbySelectablePlayer::GetIndex() const
{
	return Index_;
}

void LobbySelectablePlayer::SetPlayerInfo(const float4& _NamePos, const float4& _RenderPos, const float4& _RenderSize)
{
	// 렌더러 위치 지정
	if (nullptr == mainrenderer_)
	{
		return;
	}

	float4 ImageSize = mainrenderer_->GetImageSize();
	float4 HarfSize = ImageSize.halffloat4();
	float4 RenderSize = _RenderSize;

	mainrenderer_->SetPivotPos(float4(HarfSize.x + _RenderPos.x, HarfSize.y + _RenderPos.y));

	// 렌더크기가 정해지지않았다면 렌더러의 이미지 크기로 설정된다.
	if (RenderSize == float4::ZERO)
	{
		mainrenderer_->SetRenderSize(ImageSize);
	}
	else
	{
		mainrenderer_->SetRenderSize(_RenderSize);
	}

	// 충돌체 위치 지정 및 충돌체 On
	if (nullptr == maincollision_)
	{
		return;
	}

	maincollision_->SetSize(_RenderSize);
	maincollision_->SetPivot(float4((_RenderSize.x * 0.5f) + _RenderPos.x, (_RenderSize.y * 0.5f) + _RenderPos.y));
	maincollision_->On();

	// Index정보 변경
	NamePos_ = _NamePos;
}

void LobbySelectablePlayer::SetPlayerOn()
{
	// 현재 ShowPlayer_상태 On
	ShowPlayer_ = true;

	// 충돌체 On
	if (nullptr == maincollision_)
	{
		return;
	}
	maincollision_->On();
}

void LobbySelectablePlayer::SetPlayerOff()
{
	// 현재 ShowPlayer_상태 Off
	ShowPlayer_ = false;

	// 충돌체 Off
	if (nullptr == maincollision_)
	{
		return;
	}
	maincollision_->Off();
}

void LobbySelectablePlayer::CreatePlayer(const std::string& _PlayerName, int _Index, int _CPUIndex, bool _PlayerAndCPU)
{
	// 기본정보 셋팅
	Index_ = _Index;
	Name_ = _PlayerName;
	ShowPlayer_ = false;

	// 렌더러 생성
	if (true == _PlayerAndCPU) // 플레이어
	{
		mainrenderer_ = CreateRenderer("Lobby_Player");
	}
	else // CPU
	{
		std::string CPUName = "Lobby_CPU";
		CPUName += std::to_string(_CPUIndex + 1);
		mainrenderer_ = CreateRenderer(CPUName);
	}
	mainrenderer_->SetCameraEffectOff();

	// 충돌체 생성 및 OFF
	maincollision_ = CreateCollision(static_cast<int>(eCollisionGroup::UI), CollisionCheckType::RECT);
	maincollision_->Off();
}

