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
	// �Ѱܹ��� �÷��̾������ �÷��̾����� CPU���� �Ǵ��Ѵ�.
	std::string CurSelPlayerName = _PlayerName;

	// CPU(��ǻ��)�̶��
	GameEngineRenderer* NewRender = nullptr;
	if (0 == CurSelPlayerName.find("CPU"))
	{
		
	}
	else // �÷��̾�(���)�̶��
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

LobbyCreateTeam::~LobbyCreateTeam() // default destructer ����Ʈ �Ҹ���
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

	// ���ð����� �÷��̾� ��� ����
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

	// ���ð����� �÷��̾� ��Ͽ� CPU �߰�
	// ������ 5�� �����Ѵ�.
	for (int i = 0; i < 5; ++i)
	{
		std::string CPUName = "CPU";
		CPUName += std::to_string((i + 1));

		LobbySelectablePlayer* NewPlayer = GetLevel()->CreateActor<LobbySelectablePlayer>();
		NewPlayer->CreatePlayer(CPUName, i + Index + 1, i, false);

		SelectablePlayerList.push_back(NewPlayer);
	}

	// ���� �������� �÷��̾� ����� �ִ� �÷��̾� ǥ�� ������ŭ �÷��̾� On
	for (int i = 0; i < 4; ++i)
	{
		// �� ���� ��ġ ��� �� �÷��̾� ǥ��
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
	// ���� ���õ� �÷��̾� �ڽ�
	playerboxSpriteRender_->Render();

	// ���ð����� �÷��̾� �ڽ�
	playerselboxSpriteRender_->Render();

	// �����ϴ� �� �̸� �Է¹ڽ�
	playerselInputSpriteRender_->Render();
}

