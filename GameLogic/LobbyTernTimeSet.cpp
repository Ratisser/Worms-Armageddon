#include "LobbyTernTimeSet.h"
#include "eCollisionGroup.h"
#include "GameOptionInfo.h"
#include <time.h>

#include <EngineEnum.h>
#include <GameEngineWindow.h>
#include <GameEngineInput.h>
#include <GameEngineRenderer.h>
#include <GameEngineCollision.h>

LobbyTernTimeSet::LobbyTernTimeSet() :
	ImageIndex_(3),
	mainrenderer_(nullptr),
	maincollision_(nullptr)
{
	SetRenderOrder(static_cast<int>(RenderOrder::UI));
}

LobbyTernTimeSet::~LobbyTernTimeSet() // default destructer ����Ʈ �Ҹ���
{

}

LobbyTernTimeSet::LobbyTernTimeSet(LobbyTernTimeSet&& _other) noexcept :
	ImageIndex_(_other.ImageIndex_),
	mainrenderer_(_other.mainrenderer_),
	maincollision_(_other.maincollision_)
{

}

void LobbyTernTimeSet::Start()
{
	mainrenderer_ = CreateRenderer("Lobby_BasicOption_TernTime3");
	float4 ImageHarfSize = mainrenderer_->GetImageSize().halffloat4();
	mainrenderer_->SetPivotPos(float4(ImageHarfSize.x + 480.f, ImageHarfSize.y + 314.f));
	mainrenderer_->SetCameraEffectOff();

	maincollision_ = CreateCollision(static_cast<int>(eCollisionGroup::UI), CollisionCheckType::RECT);
	maincollision_->SetSize(mainrenderer_->GetImageSize());
	maincollision_->SetPivot(float4(ImageHarfSize.x + 480.f, ImageHarfSize.y + 314.f));
}

void LobbyTernTimeSet::UpdateBefore()
{
	// ���콺 �浹üũ
	GameEngineCollision* ColUI = maincollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MOUSE));
	if (nullptr != ColUI)
	{
		if (true == GameEngineInput::GetInst().IsDown("LobbyLevel_MouseLButton"))
		{
			// ���� �̹��� �ε��� ����
			++ImageIndex_;

			if (6 < ImageIndex_)
			{
				ImageIndex_ = 0;
			}

			// �̹��� ��ȯ
			std::string ImageName = "Lobby_BasicOption_TernTime";
			ImageName += std::to_string(ImageIndex_);
			mainrenderer_->SetImage(ImageName);

			// �ɼǼ��� Ŭ������ ����
			int TernTime = static_cast<int>(GameOptionInfo::TernTime);
			if (3 >= ImageIndex_)
			{
				// ������ ���Ѵ� �ɼ��ΰ��� �����Ͽ� �̸� ���Ѵ�
				if (0 == TernTime)
				{
					TernTime = 15;
				}

				TernTime = TernTime + (ImageIndex_ * 5);
			}
			else if(5 >= ImageIndex_)
			{
				TernTime = TernTime + ((ImageIndex_ - 3) * 5) + ((ImageIndex_ - 3) * 10);
			}
			else
			{
				// ���Ѵ�(infinity) ���� �� 20~100������ ���������� ����
				srand((unsigned int)time(0));
				int InfinityRandom = rand() % 100 + 20;
				TernTime = InfinityRandom;
			}

			GameOptionInfo::TernTime = static_cast<float>(TernTime);
		}
	}
}

void LobbyTernTimeSet::Update()
{

}

void LobbyTernTimeSet::UpdateAfter()
{
}

void LobbyTernTimeSet::Render()
{
	mainrenderer_->Render();
}

