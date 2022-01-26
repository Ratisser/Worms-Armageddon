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
	// ���콺�� �浹üũ
	GameEngineCollision* ColUI = maincollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MOUSE));
	if (nullptr != ColUI)
	{
		if (true == GameEngineInput::GetInst().IsDown("LobbyLevel_MouseLButton"))
		{
			// ���õ� �÷��̾� off ���°��Ǹ� LobbyCreateTeam�� ���� ���õ� �÷��̾� �̸��� ����
			//ShowPlayer_ = false; // �ӽ��ּ�

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
	// ȭ��� ǥ���ϴ� �͸� ǥ��
	if (true == ShowPlayer_)
	{
		// �÷��̾� �̹��� ǥ��
		if (nullptr != mainrenderer_)
		{
			mainrenderer_->Render();
		}

		// �÷��̾� ��Ī ǥ��
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
	// ������ ��ġ ����
	if (nullptr == mainrenderer_)
	{
		return;
	}

	float4 ImageSize = mainrenderer_->GetImageSize();
	float4 HarfSize = ImageSize.halffloat4();
	float4 RenderSize = _RenderSize;

	mainrenderer_->SetPivotPos(float4(HarfSize.x + _RenderPos.x, HarfSize.y + _RenderPos.y));

	// ����ũ�Ⱑ ���������ʾҴٸ� �������� �̹��� ũ��� �����ȴ�.
	if (RenderSize == float4::ZERO)
	{
		mainrenderer_->SetRenderSize(ImageSize);
	}
	else
	{
		mainrenderer_->SetRenderSize(_RenderSize);
	}

	// �浹ü ��ġ ���� �� �浹ü On
	if (nullptr == maincollision_)
	{
		return;
	}

	maincollision_->SetSize(_RenderSize);
	maincollision_->SetPivot(float4((_RenderSize.x * 0.5f) + _RenderPos.x, (_RenderSize.y * 0.5f) + _RenderPos.y));
	maincollision_->On();

	// Index���� ����
	NamePos_ = _NamePos;
}

void LobbySelectablePlayer::SetPlayerOn()
{
	// ���� ShowPlayer_���� On
	ShowPlayer_ = true;

	// �浹ü On
	if (nullptr == maincollision_)
	{
		return;
	}
	maincollision_->On();
}

void LobbySelectablePlayer::SetPlayerOff()
{
	// ���� ShowPlayer_���� Off
	ShowPlayer_ = false;

	// �浹ü Off
	if (nullptr == maincollision_)
	{
		return;
	}
	maincollision_->Off();
}

void LobbySelectablePlayer::CreatePlayer(const std::string& _PlayerName, int _Index, int _CPUIndex, bool _PlayerAndCPU)
{
	// �⺻���� ����
	Index_ = _Index;
	Name_ = _PlayerName;
	ShowPlayer_ = false;

	// ������ ����
	if (true == _PlayerAndCPU) // �÷��̾�
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

	// �浹ü ���� �� OFF
	maincollision_ = CreateCollision(static_cast<int>(eCollisionGroup::UI), CollisionCheckType::RECT);
	maincollision_->Off();
}

