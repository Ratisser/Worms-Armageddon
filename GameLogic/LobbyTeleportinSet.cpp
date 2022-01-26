#include "LobbyTeleportinSet.h"
#include "eCollisionGroup.h"
#include "GameOptionInfo.h"

#include <EngineEnum.h>
#include <GameEngineWindow.h>
#include <GameEngineInput.h>
#include <GameEngineRenderer.h>
#include <GameEngineCollision.h>

LobbyTeleportinSet::LobbyTeleportinSet() :
	ImageIndex_(0),
	mainrenderer_(nullptr),
	maincollision_(nullptr)
{
	SetRenderOrder(static_cast<int>(RenderOrder::UI));
}

LobbyTeleportinSet::~LobbyTeleportinSet() // default destructer ����Ʈ �Ҹ���
{

}

LobbyTeleportinSet::LobbyTeleportinSet(LobbyTeleportinSet&& _other) noexcept :
	ImageIndex_(_other.ImageIndex_),
	mainrenderer_(_other.mainrenderer_),
	maincollision_(_other.maincollision_)
{

}

void LobbyTeleportinSet::Start()
{
	mainrenderer_ = CreateRenderer("Lobby_BasicOption_Teleportin0");
	float4 ImageHarfSize = mainrenderer_->GetImageSize().halffloat4();
	mainrenderer_->SetPivotPos(float4(ImageHarfSize.x + 855.f, ImageHarfSize.y + 314.f));
	mainrenderer_->SetCameraEffectOff();

	maincollision_ = CreateCollision(static_cast<int>(eCollisionGroup::UI), CollisionCheckType::RECT);
	maincollision_->SetSize(mainrenderer_->GetImageSize());
	maincollision_->SetPivot(float4(ImageHarfSize.x + 855.f, ImageHarfSize.y + 314.f));
}

void LobbyTeleportinSet::UpdateBefore()
{
	// ���콺 �浹üũ
	GameEngineCollision* ColUI = maincollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MOUSE));
	if (nullptr != ColUI)
	{
		if (true == GameEngineInput::GetInst().IsDown("LobbyLevel_MouseLButton"))
		{
			// ���� �̹��� �ε��� ����
			++ImageIndex_;

			if (1 < ImageIndex_)
			{
				ImageIndex_ = 0;
			}

			// �̹��� ��ȯ
			std::string ImageName = "Lobby_BasicOption_Teleportin";
			ImageName += std::to_string(ImageIndex_);
			mainrenderer_->SetImage(ImageName);

			// �ɼǼ��� Ŭ������ ����
			bool Teleportin = GameOptionInfo::Teleportin;
			if (false == Teleportin)
			{
				Teleportin = true;
			}
			else
			{
				Teleportin = false;
			}

			GameOptionInfo::Teleportin = Teleportin;
		}
	}
}

void LobbyTeleportinSet::Update()
{
}

void LobbyTeleportinSet::UpdateAfter()
{
}

void LobbyTeleportinSet::Render()
{
	mainrenderer_->Render();
}
