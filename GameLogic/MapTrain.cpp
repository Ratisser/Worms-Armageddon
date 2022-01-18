#include "MapTrain.h"
#include "GlobalValue.h"
#include <GameEngineWindow.h>
#include <GameEngineRenderer.h>
#include "GameEngineImage.h"
#include "GameEngineImageFile.h"

MapTrain::MapTrain() // default constructer 디폴트 생성자
	:firstupdate_(false),
	mainSpriteRender_(nullptr),
	colSpriteRender_(nullptr),
	boomSpriteRender_(nullptr)
{
	SetRenderOrder((int)RenderOrder::Map);
}

MapTrain::~MapTrain() // default destructer 디폴트 소멸자
{

}

MapTrain::MapTrain(MapTrain&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
	:firstupdate_(_other.firstupdate_),
	mainSpriteRender_(nullptr),
	colSpriteRender_(nullptr),
	boomSpriteRender_(nullptr)
{

}

void MapTrain::Start()
{
	boomSpriteRender_ = CreateRenderer("Boom");
}

void MapTrain::UpdateBefore()
{
	// 렌더러를 이때 생성한다
	if (false == firstupdate_)
	{
		// 맵 렌더러 생성 및 위치 지정
		mainSpriteRender_ = CreateRenderer(GlobalValue::CurPlayMap);
		float4 imageSize = mainSpriteRender_->GetImageSize();
		mainSpriteRender_->SetPivotPos(imageSize.halffloat4());

		// 충돌맵 렌더러 생성 및 위치 지정
		colSpriteRender_ = CreateRenderer(GlobalValue::CurPlayColMap);
		imageSize = colSpriteRender_->GetImageSize();
		colSpriteRender_->SetPivotPos(imageSize.halffloat4());

		// 최초갱신일때만 실행되도록 설정
		firstupdate_ = true;
	}
}

void MapTrain::Update()
{

}

void MapTrain::UpdateAfter()
{

}

void MapTrain::Render()
{
	// 충돌맵
	colSpriteRender_->Render();

	// 진짜 맵
	mainSpriteRender_->Render();
}

void MapTrain::GroundUpdate(float4 pos)
{
	//float4 mousepos = GameEngineWindow::GetInst().GetMousePos() + pos;
	GameEngineImageFile* WindowImage = mainSpriteRender_->GetImage();
	WindowImage->TransCopy(boomSpriteRender_->GetImage(),
		pos,
		{ 100.f, 100.f },
		{ 0.f, 0.f },
		{ 100.f, 100.f },
		RGB(0, 255, 0));
}

