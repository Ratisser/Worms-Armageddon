#include "LobbyWormEnergySet.h"
#include "eCollisionGroup.h"
#include "GameOptionInfo.h"

#include <EngineEnum.h>
#include <GameEngineWindow.h>
#include <GameEngineInput.h>
#include <GameEngineRenderer.h>
#include <GameEngineCollision.h>

LobbyWormEnergySet::LobbyWormEnergySet() :
	ImageIndex_(0),
	mainrenderer_(nullptr),
	maincollision_(nullptr)
{
	SetRenderOrder(static_cast<int>(RenderOrder::UI));
}

LobbyWormEnergySet::~LobbyWormEnergySet() // default destructer 디폴트 소멸자
{

}

LobbyWormEnergySet::LobbyWormEnergySet(LobbyWormEnergySet&& _other) noexcept :
	ImageIndex_(_other.ImageIndex_),
	mainrenderer_(_other.mainrenderer_),
	maincollision_(_other.maincollision_)
{

}

void LobbyWormEnergySet::Start()
{
	mainrenderer_ = CreateRenderer("Lobby_BasicOption_WormEnergy0");
	float4 ImageHarfSize = mainrenderer_->GetImageSize().halffloat4();
	mainrenderer_->SetPivotPos(float4(ImageHarfSize.x + 780.f, ImageHarfSize.y + 314.f));
	mainrenderer_->SetCameraEffectOff();

	maincollision_ = CreateCollision(static_cast<int>(eCollisionGroup::UI), CollisionCheckType::RECT);
	maincollision_->SetSize(mainrenderer_->GetImageSize());
	maincollision_->SetPivot(float4(ImageHarfSize.x + 780.f, ImageHarfSize.y + 314.f));
}

void LobbyWormEnergySet::UpdateBefore()
{
	// 마우스 충돌체크
	GameEngineCollision* ColUI = maincollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MOUSE));
	if (nullptr != ColUI)
	{
		if (true == GameEngineInput::GetInst().IsDown("LobbyLevel_MouseLButton"))
		{
			// 현재 이미지 인덱스 증가
			++ImageIndex_;

			if (3 < ImageIndex_)
			{
				ImageIndex_ = 0;
			}

			// 이미지 전환
			std::string ImageName = "Lobby_BasicOption_WormEnergy";
			ImageName += std::to_string(ImageIndex_);
			mainrenderer_->SetImage(ImageName);

			// 옵션설정 클래스에 전달
			int WormEnergy = GameOptionInfo::WormEnergy;
			WormEnergy += 50;
			if (0 == ImageIndex_)
			{
				WormEnergy = 50;
			}

			GameOptionInfo::WormEnergy = WormEnergy;
		}
	}
}

void LobbyWormEnergySet::Update()
{
}

void LobbyWormEnergySet::UpdateAfter()
{
}

void LobbyWormEnergySet::Render()
{
	mainrenderer_->Render();
}

