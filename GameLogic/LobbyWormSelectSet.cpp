#include "LobbyWormSelectSet.h"
#include "eCollisionGroup.h"
#include "GameOptionInfo.h"

#include <EngineEnum.h>
#include <GameEngineWindow.h>
#include <GameEngineInput.h>
#include <GameEngineRenderer.h>
#include <GameEngineCollision.h>

LobbyWormSelectSet::LobbyWormSelectSet() :
	ImageIndex_(0),
	mainrenderer_(nullptr),
	maincollision_(nullptr)
{
	SetRenderOrder(static_cast<int>(RenderOrder::UI));
}

LobbyWormSelectSet::~LobbyWormSelectSet() // default destructer ����Ʈ �Ҹ���
{

}

LobbyWormSelectSet::LobbyWormSelectSet(LobbyWormSelectSet&& _other) noexcept :
	ImageIndex_(_other.ImageIndex_),
	mainrenderer_(_other.mainrenderer_),
	maincollision_(_other.maincollision_)
{

}

void LobbyWormSelectSet::Start()
{
	mainrenderer_ = CreateRenderer("Lobby_BasicOption_WormSelect0");
	float4 ImageHarfSize = mainrenderer_->GetImageSize().halffloat4();
	mainrenderer_->SetPivotPos(float4(ImageHarfSize.x + 705.f, ImageHarfSize.y + 314.f));
	mainrenderer_->SetCameraEffectOff();

	maincollision_ = CreateCollision(static_cast<int>(eCollisionGroup::UI), CollisionCheckType::RECT);
	maincollision_->SetSize(mainrenderer_->GetImageSize());
	maincollision_->SetPivot(float4(ImageHarfSize.x + 705.f, ImageHarfSize.y + 314.f));
}

void LobbyWormSelectSet::UpdateBefore()
{
	// ���콺 �浹üũ
	GameEngineCollision* ColUI = maincollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MOUSE));
	if (nullptr != ColUI)
	{
		// �����ɼ��̵�
		if (true == GameEngineInput::GetInst().IsDown("LobbyLevel_MouseLButton"))
		{
			// ���� �̹��� �ε��� ����
			++ImageIndex_;

			if (2 < ImageIndex_)
			{
				ImageIndex_ = 0;
			}

			// �̹��� ��ȯ
			std::string ImageName = "Lobby_BasicOption_WormSelect";
			ImageName += std::to_string(ImageIndex_);
			mainrenderer_->SetImage(ImageName);

			// �ɼǼ��� Ŭ������ ����
			int WormSelect = GameOptionInfo::WormSelect;
			WormSelect += 1;
			if (0 == ImageIndex_)
			{
				WormSelect = 0;
			}

			GameOptionInfo::WormSelect = WormSelect;
		}

		// �����ɼ��̵�
		if (true == GameEngineInput::GetInst().IsDown("LobbyLevel_MouseRButton"))
		{
			// ���� �̹��� �ε��� ����
			--ImageIndex_;

			if (0 > ImageIndex_)
			{
				ImageIndex_ = 2;
			}

			// �̹��� ��ȯ
			std::string ImageName = "Lobby_BasicOption_WormSelect";
			ImageName += std::to_string(ImageIndex_);
			mainrenderer_->SetImage(ImageName);

			// �ɼǼ��� Ŭ������ ����
			int WormSelect = GameOptionInfo::WormSelect;
			WormSelect -= 1;
			if (2 == ImageIndex_)
			{
				WormSelect = 2;
			}

			GameOptionInfo::WormSelect = WormSelect;
		}
	}
}

void LobbyWormSelectSet::Update()
{
}

void LobbyWormSelectSet::UpdateAfter()
{
}

void LobbyWormSelectSet::Render()
{
	mainrenderer_->Render();
}

