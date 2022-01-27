#include "LobbyCreateTeam.h"
#include "LobbySelectablePlayer.h"
#include "eCollisionGroup.h"

#include <EngineEnum.h>
#include <GameEngineWindow.h>
#include <GameEngineInput.h>
#include <GameEngineRenderer.h>
#include <GameEngineCollision.h>
#include <GameEngineLevel.h>
#include <GameEngineImage.h>
#include <GameEngineImageFile.h>

LobbyCreateTeam::LobbyCreateTeam() :
	playerselInputSpriteRender_(nullptr),
	playerboxSpriteRender_(nullptr),
	playerselboxSpriteRender_(nullptr),
	ActiveStartIndex_(0),
	ActiveEndIndex_(3)
{
	SetRenderOrder(static_cast<int>(RenderOrder::UI));
}

LobbyCreateTeam::~LobbyCreateTeam() // default destructer 디폴트 소멸자
{

}

LobbyCreateTeam::LobbyCreateTeam(LobbyCreateTeam&& _other) noexcept :
	playerselInputSpriteRender_(_other.playerselInputSpriteRender_),
	playerselboxSpriteRender_(_other.playerselboxSpriteRender_),
	playerboxSpriteRender_(_other.playerboxSpriteRender_),
	ActiveStartIndex_(_other.ActiveStartIndex_),
	ActiveEndIndex_(_other.ActiveEndIndex_)
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

	// 220127 SJH 임시주석 : CPU 기능 없음
	// 선택가능한 플레이어 목록에 CPU 추가
	// 무조건 5개 생성한다.
	//for (int i = 0; i < 5; ++i)
	//{
		//std::string CPUName = "CPU";
		//CPUName += std::to_string((i + 1));

		//LobbySelectablePlayer* NewPlayer = GetLevel()->CreateActor<LobbySelectablePlayer>();
		//NewPlayer->CreatePlayer(CPUName, i + Index + 1, i, false);

		//SelectablePlayerList.push_back(NewPlayer);
	//}

	// 선택가능한 플레이어 목록 생성
	int Index = 0;
	for (int i = 0; i < 8; ++i)
	{
		std::string PlayerName = std::to_string(i + 1);
		PlayerName += "-UP";

		LobbySelectablePlayer* NewPlayer = GetLevel()->CreateActor<LobbySelectablePlayer>();
		NewPlayer->CreatePlayer(PlayerName, i, 0);
		SelectablePlayerList.push_back(NewPlayer);

		//Index = i;
	}

	for (int i = 0; i < static_cast<int>(SelectablePlayerList.size()); ++i)
	{
		SelectablePlayerList[i]->SetPlayerInfo(this, float4(272.f, (245.f + (i * 36.f))), float4(230.f, (236.f + (i * 34.f))), float4(32.f, 32.f));
	}

	// 현재 관리중인 플레이어 목록중 최대 플레이어 표시 갯수만큼 플레이어 On
	for (int i = 0; i < 4; ++i)
	{
		// 각 액터 위치 계산 후 플레이어 표시
		SelectablePlayerList[i]->SetPlayerOn(i);
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

	// 선택된 플레이어목록 렌더링
	if (!SelectPlayerNameList.empty())
	{
		int PlayerListSize = static_cast<int>(SelectPlayerRendererList.size());
		for (int i = 0; i < PlayerListSize; ++i)
		{
			if (true == SelectPlayerRendererList[i]->IsOn())
			{
				SelectPlayerRendererList[i]->Render();

				// 플레이어 이름을 표시
				float4 NamePos = SelectPlayerNamePosList[i];
				TextOut(GameEngineImage::GetInst().GetBackBufferImage()->GetDC(), NamePos.ix(), NamePos.iy(), SelectPlayerNameList[i].c_str(), lstrlen(SelectPlayerNameList[i].c_str()));
			}
		}
	}
}

void LobbyCreateTeam::SetSelectPlayer(const std::string& _Name, int _Index)
{
	// 넘겨받은 플레이어명으로 플레이어인지 CPU인지 판단한다.
	std::string CurSelPlayerName = _Name;
	
	// 플레이어(사람)이라면
	GameEngineRenderer* NewRender = nullptr;
	if (0 != CurSelPlayerName.find("CPU"))
	{
		NewRender = CreateRenderer("Lobby_Player");
	}
	else // CPU(컴퓨터)이라면
	{
		std::string CPURendererName = "Lobby_";
		CPURendererName += CurSelPlayerName;
		NewRender = CreateRenderer(CPURendererName);
	}

	// 최대 표시보다 커지면 렌더러 off
	int RenderListSize = static_cast<int>(SelectPlayerRendererList.size());
	if (4 < RenderListSize)
	{
		NewRender->Off();
	}

	// 렌더러 크기 및 위치 지정
	NewRender->SetRenderSize(float4(32.f, 32.f));
	float4 ImageHarfSize = NewRender->GetImageSize().halffloat4();
	NewRender->SetPivotPos(float4(ImageHarfSize.x + 230.f, ImageHarfSize.y + 20.f + (RenderListSize * 34.f)));

	SelectPlayerRendererList.push_back(NewRender);

	// 플레이어이름 표시 및 선택한 플레이어이름목록에 추가
	int NameListSize = static_cast<int>(SelectPlayerNameList.size());
	SelectPlayerNameList.push_back(CurSelPlayerName);

	// 플레이어이름 표시를 위한 위치목록 추가
	float4 NamePos = float4::ZERO;
	NamePos.x = 272.f;
	NamePos.y = 30.f + (RenderListSize * 36.f);
	SelectPlayerNamePosList.push_back(NamePos);

	// 기존 선택가능플레이어목록에서 현재 선택된 플레이어를 Off시키며,
	// 만약 마지막인덱스에 위치한 플레이어라면 그냥 Off,
	// 처음 or 중간인덱스에 위치한 플레이어라면 현재표시가능한 플레이어 위치 재조정
	int CurPlayerListSize = static_cast<int>(SelectablePlayerList.size());
	if (CurPlayerListSize == _Index) // 마지막 인덱스라면
	{
		SelectablePlayerList[_Index]->SetPlayerOff();
	}
	else // 처음 or 중간 인덱스라면 표시하는 선택가능 플레이어목록 수정
	{
		// 현재 선택된 인덱스 Off
		SelectablePlayerList[_Index]->SetPlayerOff();
		SelectablePlayerList[_Index]->DelActiveIndex();

		// 현재 선택된 플레이어가 활성화되어있었으므로 해당 플레이어의 활성화 인덱스를 가져온다.
		//int CurPlayerActIndex = SelectablePlayerList[_Index]->GetActiveIndex();
		//int CalcIndex = _Index + 1;
		//int EndActiveIndex = 4 - CurPlayerActIndex;
		//for (int i = CurPlayerActIndex; i < EndActiveIndex + 1; ++i)
		//{
		//	SelectablePlayerList[CalcIndex]->ChangePlayerPos(float4(272.f, (245.f + (i * 36.f))), float4(230.f, (236.f + (i * 34.f))), float4(32.f, 32.f));
		//	SelectablePlayerList[CalcIndex]->SetPlayerOn(i);

		//	++CalcIndex;
		//}
	}
}

