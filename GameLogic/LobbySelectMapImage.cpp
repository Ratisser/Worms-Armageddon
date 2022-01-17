#include "LobbySelectMapImage.h"
#include "eCollisionGroup.h"

#include <GameEngineWindow.h>
#include <GameEngineInput.h>
#include <GameEngineCollision.h>
#include <GameEngineRenderer.h>
#include <EngineEnum.h>

LobbySelectMapImage::LobbySelectMapImage() :
	curmapimage_(0),
	mainrenderer_(nullptr),
	maincollision_(nullptr)
{

}

LobbySelectMapImage::~LobbySelectMapImage() // default destructer 디폴트 소멸자
{

}

LobbySelectMapImage::LobbySelectMapImage(LobbySelectMapImage&& _other) noexcept :
	curmapimage_(_other.curmapimage_),
	mainrenderer_(_other.mainrenderer_),
	maincollision_(_other.maincollision_)
{
}

void LobbySelectMapImage::CreateSelMapImageNameList(const std::vector<std::string>& _NameList)
{
	mapimagenamelist_ = _NameList;
}

void LobbySelectMapImage::Start()
{
	float4 HarfResolution = GameEngineWindow::GetInst().GetSize().halffloat4();

	SetRenderOrder(static_cast<int>(RenderOrder::UI));
	mainrenderer_ = CreateRenderer("MapSel1");
	mainrenderer_->SetRenderSize({ HarfResolution.x- 120.f, 200.f });
	mainrenderer_->SetImagePivot({ 0.f, 0.f });
	mainrenderer_->SetCameraEffectOff();

	maincollision_ = CreateCollision(static_cast<int>(eCollisionGroup::MOUSE), CollisionCheckType::RECT);
}

void LobbySelectMapImage::UpdateBefore()
{
	float4 HarfResolution = GameEngineWindow::GetInst().GetSize().halffloat4();

	// 충돌체크
	GameEngineCollision* ColUI = maincollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MOUSE));
	if (nullptr != ColUI)
	{
		// 마우스 오른쪽버튼 체크
		if (true == GameEngineInput::GetInst().IsDown("Lobby_MapSelect"))
		{
			// 메인렌더러 이미지 변경
			++curmapimage_;
			if (curmapimage_ > mapimagenamelist_.size() - 1)
			{
				curmapimage_ = 0;
			}

			mainrenderer_->SetImage(mapimagenamelist_[curmapimage_]);
			mainrenderer_->SetRenderSize({ HarfResolution.x - 120.f, 200.f });
			mainrenderer_->SetImagePivot({ 0.f, 0.f });
			mainrenderer_->SetCameraEffectOff();
		}
	}
}

void LobbySelectMapImage::Update()
{
}

void LobbySelectMapImage::UpdateAfter()
{
}

void LobbySelectMapImage::Render()
{
	mainrenderer_->Render();
}

