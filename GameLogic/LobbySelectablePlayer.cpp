#include "LobbySelectablePlayer.h"
#include "eCollisionGroup.h"

#include <EngineEnum.h>
#include <GameEngineWindow.h>
#include <GameEngineRenderer.h>
#include <GameEngineCollision.h>

LobbySelectablePlayer::LobbySelectablePlayer() :
	ShowPlayer_(false),
	Index_(-1),
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
	mainrenderer_(_other.mainrenderer_),
	maincollision_(_other.maincollision_)
{
}

void LobbySelectablePlayer::Start()
{
}

void LobbySelectablePlayer::UpdateBefore()
{
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

void LobbySelectablePlayer::SetPlayerOn(const float4& _RenderPos, const float4& _RenderSize)
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

	// ���� �÷��̾� ���� �� Index���� ����
	ShowPlayer_ = true;
}

void LobbySelectablePlayer::SetPlayerOff()
{
	// ���� ShowPlayer_���� Off
	ShowPlayer_ = true;

	// �浹ü Off
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

