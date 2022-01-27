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

LobbyCreateTeam::~LobbyCreateTeam() // default destructer ����Ʈ �Ҹ���
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

	// ���� ���õ� �÷��̾� ��Ϲڽ�
	playerboxSpriteRender_ = CreateRenderer("Lobby_PlayerBox");
	ImageHarfSize = playerboxSpriteRender_->GetImageSize().halffloat4();
	playerboxSpriteRender_->SetPivotPos(float4(ImageHarfSize.x + 220.f, ImageHarfSize.y + 10.f));
	playerboxSpriteRender_->SetRenderSize(float4(250.f, 180.f));
	playerboxSpriteRender_->SetCameraEffectOff();

	// ���̸�??? �Է¹ڽ�
	playerselInputSpriteRender_ = CreateRenderer("Lobby_SelPlayerInput");
	ImageHarfSize = playerselInputSpriteRender_->GetImageSize().halffloat4();
	playerselInputSpriteRender_->SetPivotPos(float4(ImageHarfSize.x + 220.f, ImageHarfSize.y + 200.f));
	playerselInputSpriteRender_->SetRenderSize(float4(250.f, 32.f));
	playerselInputSpriteRender_->SetCameraEffectOff();

	// ���ð����� �÷��̾� ��Ϲڽ�
	playerselboxSpriteRender_ = CreateRenderer("Lobby_SelPlayerBox");
	ImageHarfSize = playerselboxSpriteRender_->GetImageSize().halffloat4();
	playerselboxSpriteRender_->SetPivotPos(float4(ImageHarfSize.x + 220.f, ImageHarfSize.y + 232.f));
	playerselboxSpriteRender_->SetRenderSize(float4(250.f, 150.f));
	playerselboxSpriteRender_->SetCameraEffectOff();

	// 220127 SJH �ӽ��ּ� : CPU ��� ����
	// ���ð����� �÷��̾� ��Ͽ� CPU �߰�
	// ������ 5�� �����Ѵ�.
	//for (int i = 0; i < 5; ++i)
	//{
		//std::string CPUName = "CPU";
		//CPUName += std::to_string((i + 1));

		//LobbySelectablePlayer* NewPlayer = GetLevel()->CreateActor<LobbySelectablePlayer>();
		//NewPlayer->CreatePlayer(CPUName, i + Index + 1, i, false);

		//SelectablePlayerList.push_back(NewPlayer);
	//}

	// ���ð����� �÷��̾� ��� ����
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

	// ���� �������� �÷��̾� ����� �ִ� �÷��̾� ǥ�� ������ŭ �÷��̾� On
	for (int i = 0; i < 4; ++i)
	{
		// �� ���� ��ġ ��� �� �÷��̾� ǥ��
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
	// ���� ���õ� �÷��̾� �ڽ�
	playerboxSpriteRender_->Render();

	// ���ð����� �÷��̾� �ڽ�
	playerselboxSpriteRender_->Render();

	// �����ϴ� �� �̸� �Է¹ڽ�
	playerselInputSpriteRender_->Render();

	// ���õ� �÷��̾��� ������
	if (!SelectPlayerNameList.empty())
	{
		int PlayerListSize = static_cast<int>(SelectPlayerRendererList.size());
		for (int i = 0; i < PlayerListSize; ++i)
		{
			if (true == SelectPlayerRendererList[i]->IsOn())
			{
				SelectPlayerRendererList[i]->Render();

				// �÷��̾� �̸��� ǥ��
				float4 NamePos = SelectPlayerNamePosList[i];
				TextOut(GameEngineImage::GetInst().GetBackBufferImage()->GetDC(), NamePos.ix(), NamePos.iy(), SelectPlayerNameList[i].c_str(), lstrlen(SelectPlayerNameList[i].c_str()));
			}
		}
	}
}

void LobbyCreateTeam::SetSelectPlayer(const std::string& _Name, int _Index)
{
	// �Ѱܹ��� �÷��̾������ �÷��̾����� CPU���� �Ǵ��Ѵ�.
	std::string CurSelPlayerName = _Name;
	
	// �÷��̾�(���)�̶��
	GameEngineRenderer* NewRender = nullptr;
	if (0 != CurSelPlayerName.find("CPU"))
	{
		NewRender = CreateRenderer("Lobby_Player");
	}
	else // CPU(��ǻ��)�̶��
	{
		std::string CPURendererName = "Lobby_";
		CPURendererName += CurSelPlayerName;
		NewRender = CreateRenderer(CPURendererName);
	}

	// �ִ� ǥ�ú��� Ŀ���� ������ off
	int RenderListSize = static_cast<int>(SelectPlayerRendererList.size());
	if (4 < RenderListSize)
	{
		NewRender->Off();
	}

	// ������ ũ�� �� ��ġ ����
	NewRender->SetRenderSize(float4(32.f, 32.f));
	float4 ImageHarfSize = NewRender->GetImageSize().halffloat4();
	NewRender->SetPivotPos(float4(ImageHarfSize.x + 230.f, ImageHarfSize.y + 20.f + (RenderListSize * 34.f)));

	SelectPlayerRendererList.push_back(NewRender);

	// �÷��̾��̸� ǥ�� �� ������ �÷��̾��̸���Ͽ� �߰�
	int NameListSize = static_cast<int>(SelectPlayerNameList.size());
	SelectPlayerNameList.push_back(CurSelPlayerName);

	// �÷��̾��̸� ǥ�ø� ���� ��ġ��� �߰�
	float4 NamePos = float4::ZERO;
	NamePos.x = 272.f;
	NamePos.y = 30.f + (RenderListSize * 36.f);
	SelectPlayerNamePosList.push_back(NamePos);

	// ���� ���ð����÷��̾��Ͽ��� ���� ���õ� �÷��̾ Off��Ű��,
	// ���� �������ε����� ��ġ�� �÷��̾��� �׳� Off,
	// ó�� or �߰��ε����� ��ġ�� �÷��̾��� ����ǥ�ð����� �÷��̾� ��ġ ������
	int CurPlayerListSize = static_cast<int>(SelectablePlayerList.size());
	if (CurPlayerListSize == _Index) // ������ �ε������
	{
		SelectablePlayerList[_Index]->SetPlayerOff();
	}
	else // ó�� or �߰� �ε������ ǥ���ϴ� ���ð��� �÷��̾��� ����
	{
		// ���� ���õ� �ε��� Off
		SelectablePlayerList[_Index]->SetPlayerOff();
		SelectablePlayerList[_Index]->DelActiveIndex();

		// ���� ���õ� �÷��̾ Ȱ��ȭ�Ǿ��־����Ƿ� �ش� �÷��̾��� Ȱ��ȭ �ε����� �����´�.
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

