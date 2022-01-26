#include "LobbyCreateTeam.h"
#include "LobbySelectablePlayer.h"

#include <EngineEnum.h>
#include <GameEngineWindow.h>
#include <GameEngineInput.h>
#include <GameEngineRenderer.h>
#include <GameEngineCollision.h>
#include <GameEngineLevel.h>

void LobbyCreateTeam::SelectPlayer(const std::string& _PlayerName, int _CurSelPlayerIndex)
{
	// 넘겨받은 플레이어명으로 플레이어인지 CPU인지 판단한다.
	std::string CurSelPlayerName = _PlayerName;

	// CPU(컴퓨터)이라면
	GameEngineRenderer* NewRender = nullptr;
	if (0 == CurSelPlayerName.find("CPU"))
	{
		
	}
	else // 플레이어(사람)이라면
	{

	}
}

LobbyCreateTeam::LobbyCreateTeam() :
	playerselInputSpriteRender_(nullptr),
	playerboxSpriteRender_(nullptr),
	playerselboxSpriteRender_(nullptr)
{
	SetRenderOrder(static_cast<int>(RenderOrder::UI));
}

LobbyCreateTeam::~LobbyCreateTeam() // default destructer 디폴트 소멸자
{

}

LobbyCreateTeam::LobbyCreateTeam(LobbyCreateTeam&& _other) noexcept :
	playerselInputSpriteRender_(_other.playerselInputSpriteRender_),
	playerselboxSpriteRender_(_other.playerselboxSpriteRender_),
	playerboxSpriteRender_(_other.playerboxSpriteRender_)
{
}

void LobbyCreateTeam::Start()
{
	float4 ImageHarfSize = float4::ZERO;

	// 현재 선택된 플레이어 목록박스
	playerboxSpriteRender_ = CreateRenderer("Lobby_PlayerBox");
	ImageHarfSize = playerboxSpriteRender_->GetImageSize().halffloat4();
	playerboxSpriteRender_->SetPivotPos(float4(ImageHarfSize.x + 220.f, ImageHarfSize.y + 10.f));
	playerboxSpriteRender_->SetRenderSize(float4(250.f, 180.f));
	playerboxSpriteRender_->SetCameraEffectOff();

	// 팀이름??? 입력박스
	playerselInputSpriteRender_ = CreateRenderer("Lobby_SelPlayerInput");
	ImageHarfSize = playerselInputSpriteRender_->GetImageSize().halffloat4();
	playerselInputSpriteRender_->SetPivotPos(float4(ImageHarfSize.x + 220.f, ImageHarfSize.y + 200.f));
	playerselInputSpriteRender_->SetRenderSize(float4(250.f, 32.f));
	playerselInputSpriteRender_->SetCameraEffectOff();

	// 선택가능한 플레이어 목록박스
	playerselboxSpriteRender_ = CreateRenderer("Lobby_SelPlayerBox");
	ImageHarfSize = playerselboxSpriteRender_->GetImageSize().halffloat4();
	playerselboxSpriteRender_->SetPivotPos(float4(ImageHarfSize.x + 220.f, ImageHarfSize.y + 232.f));
	playerselboxSpriteRender_->SetRenderSize(float4(250.f, 150.f));
	playerselboxSpriteRender_->SetCameraEffectOff();

	// 선택가능한 플레이어 목록 생성
	int Index = 0;
	for (int i = 0; i < 2; ++i)
	{
		std::string PlayerName = std::to_string(i + 1);
		PlayerName += "-UP";

		LobbySelectablePlayer* NewPlayer = GetLevel()->CreateActor<LobbySelectablePlayer>();
		NewPlayer->CreatePlayer(PlayerName, i, 0);

		SelectablePlayerList.push_back(NewPlayer);

		Index = i;
	}

	// 선택가능한 플레이어 목록에 CPU 추가
	// 무조건 5개 생성한다.
	for (int i = 0; i < 5; ++i)
	{
		std::string CPUName = "CPU";
		CPUName += std::to_string((i + 1));

		LobbySelectablePlayer* NewPlayer = GetLevel()->CreateActor<LobbySelectablePlayer>();
		NewPlayer->CreatePlayer(CPUName, i + Index + 1, i, false);

		SelectablePlayerList.push_back(NewPlayer);
	}

	// 현재 관리중인 플레이어 목록중 최대 플레이어 표시 갯수만큼 플레이어 On
	for (int i = 0; i < 4; ++i)
	{
		// 각 액터 위치 계산 후 플레이어 표시
		SelectablePlayerList[i]->SetPlayerInfo(float4(272.f, (245.f + (i * 36.f))), float4(230.f, (236.f + (i * 34.f))), float4(32.f, 32.f));
		SelectablePlayerList[i]->SetPlayerOn();
	}
}

void LobbyCreateTeam::UpdateBefore()
{
}

void LobbyCreateTeam::Update()
{
}

void LobbyCreateTeam::UpdateAfter()
{
}

void LobbyCreateTeam::Render()
{
	// 현재 선택된 플레이어 박스
	playerboxSpriteRender_->Render();

	// 선택가능한 플레이어 박스
	playerselboxSpriteRender_->Render();

	// 생성하는 팀 이름 입력박스
	playerselInputSpriteRender_->Render();
}

