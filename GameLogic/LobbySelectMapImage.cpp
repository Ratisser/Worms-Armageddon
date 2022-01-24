#include "LobbySelectMapImage.h"
#include "eCollisionGroup.h"
#include "GlobalValue.h"

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

void LobbySelectMapImage::SetCurMapIndex(int _Index)
{
	curmapimage_ = _Index;
}

void LobbySelectMapImage::Start()
{
	float4 HarfResolution = GameEngineWindow::GetInst().GetSize().halffloat4();

	SetRenderOrder(static_cast<int>(RenderOrder::UI));
	mainrenderer_ = CreateRenderer("LobbyMap_MapTrain");
	mainrenderer_->SetRenderSize({ HarfResolution.x - 120.f, 180.f });
	mainrenderer_->SetImagePivot({ 0.f, 10.f });
	mainrenderer_->SetCameraEffectOff();

	maincollision_ = CreateCollision(static_cast<int>(eCollisionGroup::UI), CollisionCheckType::RECT);
	maincollision_->SetSize({ 520.f, 220.f });
	maincollision_->SetPivot({ 260.f, 110.f });	// 충돌체 크기 * 0.5 한곳이 기준점
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
			mainrenderer_->SetRenderSize({ HarfResolution.x - 120.f, 180.f });
			mainrenderer_->SetImagePivot({ 0.f, 10.f });
			mainrenderer_->SetCameraEffectOff();

			// 전역변수에 현재선택된 맵이름 저장
			// 단, 맵이름을 넘겨줄때 LobbyMap_ 문자열을 제외한 문자열을 넘긴다.
			std::string CurMapName = mapimagenamelist_[curmapimage_];
			CurMapName = CurMapName.substr(9);
			GlobalValue::CurPlayMap = CurMapName;

			// 현재선택된 맵타입의 충돌맵 이름 저장
			// 단, 맵이름을 넘겨줄때 LobbyMap_ 문자열을 제외한 문자열에 _Ground 문자열을 이어붙인 이름 저장
			std::string CurColMapName = mapimagenamelist_[curmapimage_];
			CurColMapName = CurColMapName.substr(9);
			CurColMapName += "_Ground";
			GlobalValue::CurPlayColMap = CurColMapName;
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

