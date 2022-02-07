#include "LobbyRoundTimeSet.h"
#include "eCollisionGroup.h"
#include "GameOptionInfo.h"

#include <EngineEnum.h>
#include <GameEngineWindow.h>
#include <GameEngineInput.h>
#include <GameEngineRenderer.h>
#include <GameEngineCollision.h>

LobbyRoundTimeSet::LobbyRoundTimeSet() :
	ImageIndex_(3),
	mainrenderer_(nullptr),
	maincollision_(nullptr)
{
	SetRenderOrder(static_cast<int>(RenderOrder::UI));
}

LobbyRoundTimeSet::~LobbyRoundTimeSet() // default destructer ����Ʈ �Ҹ���
{

}

LobbyRoundTimeSet::LobbyRoundTimeSet(LobbyRoundTimeSet&& _other) noexcept :
	ImageIndex_(_other.ImageIndex_),
	mainrenderer_(_other.mainrenderer_),
	maincollision_(_other.maincollision_)
{

}

void LobbyRoundTimeSet::Start()
{
	mainrenderer_ = CreateRenderer("Lobby_BasicOption_RoundTime3");
	float4 ImageHarfSize = mainrenderer_->GetImageSize().halffloat4();
	mainrenderer_->SetPivotPos(float4(ImageHarfSize.x + 555.f, ImageHarfSize.y + 314.f));
	mainrenderer_->SetCameraEffectOff();

	maincollision_ = CreateCollision(static_cast<int>(eCollisionGroup::UI), CollisionCheckType::RECT);
	maincollision_->SetSize(mainrenderer_->GetImageSize());
	maincollision_->SetPivot(float4(ImageHarfSize.x + 555.f, ImageHarfSize.y + 314.f));
}

void LobbyRoundTimeSet::UpdateBefore()
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

			if (6 < ImageIndex_)
			{
				ImageIndex_ = 0;
			}

			// �̹��� ��ȯ
			std::string ImageName = "Lobby_BasicOption_RoundTime";
			ImageName += std::to_string(ImageIndex_);
			mainrenderer_->SetImage(ImageName);

			// �ɼǼ��� Ŭ������ ����
			int RoundTime = GameOptionInfo::RoundTime;
			RoundTime += 5;
			if (0 == ImageIndex_)
			{
				RoundTime = 0;
			}

			GameOptionInfo::RoundTime = RoundTime;
		}

		// �����ɼ��̵�
		if (true == GameEngineInput::GetInst().IsDown("LobbyLevel_MouseRButton"))
		{
			// ���� �̹��� �ε��� ����
			--ImageIndex_;

			if (0 > ImageIndex_)
			{
				ImageIndex_ = 6;
			}

			// �̹��� ��ȯ
			std::string ImageName = "Lobby_BasicOption_RoundTime";
			ImageName += std::to_string(ImageIndex_);
			mainrenderer_->SetImage(ImageName);

			// �ɼǼ��� Ŭ������ ����
			int RoundTime = GameOptionInfo::RoundTime;
			RoundTime -= 5;
			if (6 == ImageIndex_)
			{
				RoundTime = 30;
			}

			GameOptionInfo::RoundTime = RoundTime;
		}
	}
}

void LobbyRoundTimeSet::Update()
{
}

void LobbyRoundTimeSet::UpdateAfter()
{
}

void LobbyRoundTimeSet::Render()
{
	mainrenderer_->Render();
}

