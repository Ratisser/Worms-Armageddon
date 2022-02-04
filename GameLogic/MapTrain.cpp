#include "MapTrain.h"
#include "GlobalValue.h"
#include "eCollisionGroup.h"

#include <GameEngineWindow.h>
#include <GameEngineRenderer.h>
#include <GameEngineCollision.h>
#include "GameEngineImage.h"
#include "GameEngineImageFile.h"

MapTrain::MapTrain() // default constructer 디폴트 생성자
	:firstupdate_(false),
	gradationSpriteRender_(nullptr),
	mainSpriteRender_(nullptr),
	colSpriteRender_(nullptr),
	boomSpriteRender_(nullptr),
	boomEdgeSpriteRender_(nullptr),
	boomSpriteRender25_(nullptr),
	boomSpriteRender50_(nullptr),
	boomSpriteRender75_(nullptr),
	boomSpriteRender100_(nullptr),
	boomEdgeSpriteRender25_(nullptr),
	boomEdgeSpriteRender50_(nullptr),
	boomEdgeSpriteRender75_(nullptr),
	boomEdgeSpriteRender100_(nullptr),
	boomEdgeSpriteRender13_(nullptr),
	boomSpriteRender13_(nullptr),
	bodyCollision_(nullptr)
{
	SetRenderOrder((int)RenderOrder::Map);
}

MapTrain::~MapTrain() // default destructer 디폴트 소멸자
{

}

MapTrain::MapTrain(MapTrain&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
	:firstupdate_(_other.firstupdate_),
	gradationSpriteRender_(nullptr),
	mainSpriteRender_(nullptr),
	colSpriteRender_(nullptr),
	boomSpriteRender_(nullptr),
	boomEdgeSpriteRender_(nullptr),
	boomSpriteRender25_(nullptr),
	boomSpriteRender50_(nullptr),
	boomSpriteRender75_(nullptr),
	boomSpriteRender100_(nullptr),
	boomEdgeSpriteRender25_(nullptr),
	boomEdgeSpriteRender50_(nullptr),
	boomEdgeSpriteRender75_(nullptr),
	boomEdgeSpriteRender100_(nullptr),
	boomEdgeSpriteRender13_(nullptr),
	boomSpriteRender13_(nullptr),
	bodyCollision_(nullptr)
{

}

void MapTrain::Start()
{
	//float4 WindowSize = GameEngineWindow::GetInst().GetSize();
	//
	//gradationSpriteRender_ = CreateRenderer("Gradient");
	//float4 ImageSize = gradationSpriteRender_->GetImageSize();
	//gradationSpriteRender_->SetPivotPos(ImageSize.halffloat4());
	//gradationSpriteRender_->SetCameraEffectOff();
	//
	//gradationSpriteRender_->SetRenderSize(WindowSize);

	boomSpriteRender_ = CreateRenderer("Boom");
	boomEdgeSpriteRender_ = CreateRenderer("BoomEdge");

	boomSpriteRender13_ = CreateRenderer("Boom_13");
	boomSpriteRender25_ = CreateRenderer("Boom_25");
	boomSpriteRender50_ = CreateRenderer("Boom_50");
	boomSpriteRender75_ = CreateRenderer("Boom_75");
	boomSpriteRender100_ = CreateRenderer("Boom_100");
	boomEdgeSpriteRender13_ = CreateRenderer("BoomEdge_13");
	boomEdgeSpriteRender25_ = CreateRenderer("BoomEdge_25");
	boomEdgeSpriteRender50_ = CreateRenderer("BoomEdge_50");
	boomEdgeSpriteRender75_ = CreateRenderer("BoomEdge_75");
	boomEdgeSpriteRender100_ = CreateRenderer("BoomEdge_100");
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

		bodyCollision_ = CreateCollision(eCollisionGroup::MAP, CollisionCheckType::IMAGE);
		bodyCollision_->SetImage(GlobalValue::CurPlayColMap);

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
	// 그라데이션 
	//gradationSpriteRender_->Render();

	// 충돌맵
	colSpriteRender_->Render();

	// 진짜 맵
	mainSpriteRender_->Render();
}

void MapTrain::GroundUpdate(float4 pos, float4 size)
{
	GameEngineImageFile* ColImage = colSpriteRender_->GetImage();
	ColImage->TransCopy(boomSpriteRender_->GetImage(),
		pos,
		size,
		{ 0.f, 0.f },
		{ 100.f, 100.f },
		RGB(0, 255, 0));

	GameEngineImageFile* mapImage = mainSpriteRender_->GetImage();
	mapImage->TransCopy(boomEdgeSpriteRender_->GetImage(),
		pos,
		size,
		{ 0.f, 0.f },
		{ 100.f, 100.f },
		RGB(0, 255, 0));

	mapImage->TransCopy(colSpriteRender_->GetImage(),
		{ 0.f, 0.f },
		colSpriteRender_->GetImageSize(),
		{ 0.f, 0.f },
		colSpriteRender_->GetImageSize(),
		RGB(0, 0, 255));
}

void MapTrain::GroundUpdate13(float4 pos)
{
	GameEngineImageFile* ColImage = colSpriteRender_->GetImage();
	ColImage->TransCopy(boomSpriteRender13_->GetImage(),
		pos,
		{ 25.f, 25.f },
		{ 0.f, 0.f },
		{ 25.f, 25.f },
		RGB(0, 255, 0));

	GameEngineImageFile* mapImage = mainSpriteRender_->GetImage();
	mapImage->TransCopy(boomEdgeSpriteRender13_->GetImage(),
		pos,
		{ 25.f, 25.f },
		{ 0.f, 0.f },
		{ 25.f, 25.f },
		RGB(0, 255, 0));

	mapImage->TransCopy(colSpriteRender_->GetImage(),
		{ 0.f, 0.f },
		colSpriteRender_->GetImageSize(),
		{ 0.f, 0.f },
		colSpriteRender_->GetImageSize(),
		RGB(0, 0, 255));
}

void MapTrain::GroundUpdate25(float4 pos)
{
	GameEngineImageFile* ColImage = colSpriteRender_->GetImage();
	ColImage->TransCopy(boomSpriteRender25_->GetImage(),
		pos,
		{ 37.f, 37.f },
		{ 0.f, 0.f },
		{ 37.f, 37.f },
		RGB(0, 255, 0));

	GameEngineImageFile* mapImage = mainSpriteRender_->GetImage();
	mapImage->TransCopy(boomEdgeSpriteRender25_->GetImage(),
		pos,
		{ 37.f, 37.f },
		{ 0.f, 0.f },
		{ 37.f, 37.f },
		RGB(0, 255, 0));

	mapImage->TransCopy(colSpriteRender_->GetImage(),
		{ 0.f, 0.f },
		colSpriteRender_->GetImageSize(),
		{ 0.f, 0.f },
		colSpriteRender_->GetImageSize(),
		RGB(0, 0, 255));
}

void MapTrain::GroundUpdate50(float4 pos)
{
	GameEngineImageFile* ColImage = colSpriteRender_->GetImage();
	ColImage->TransCopy(boomSpriteRender50_->GetImage(),
		pos,
		{ 62.f, 62.f },
		{ 0.f, 0.f },
		{ 62.f, 62.f },
		RGB(0, 255, 0));

	GameEngineImageFile* mapImage = mainSpriteRender_->GetImage();
	mapImage->TransCopy(boomEdgeSpriteRender50_->GetImage(),
		pos,
		{ 62.f, 62.f },
		{ 0.f, 0.f },
		{ 62.f, 62.f },
		RGB(0, 255, 0));

	mapImage->TransCopy(colSpriteRender_->GetImage(),
		{ 0.f, 0.f },
		colSpriteRender_->GetImageSize(),
		{ 0.f, 0.f },
		colSpriteRender_->GetImageSize(),
		RGB(0, 0, 255));
}

void MapTrain::GroundUpdate75(float4 pos)
{
	GameEngineImageFile* ColImage = colSpriteRender_->GetImage();
	ColImage->TransCopy(boomSpriteRender75_->GetImage(),
		pos,
		{ 87.f, 87.f },
		{ 0.f, 0.f },
		{ 87.f, 87.f },
		RGB(0, 255, 0));

	GameEngineImageFile* mapImage = mainSpriteRender_->GetImage();
	mapImage->TransCopy(boomEdgeSpriteRender75_->GetImage(),
		pos,
		{ 87.f, 87.f },
		{ 0.f, 0.f },
		{ 87.f, 87.f },
		RGB(0, 255, 0));

	mapImage->TransCopy(colSpriteRender_->GetImage(),
		{ 0.f, 0.f },
		colSpriteRender_->GetImageSize(),
		{ 0.f, 0.f },
		colSpriteRender_->GetImageSize(),
		RGB(0, 0, 255));
}

void MapTrain::GroundUpdate100(float4 pos)
{
	GameEngineImageFile* ColImage = colSpriteRender_->GetImage();
	ColImage->TransCopy(boomSpriteRender100_->GetImage(),
		pos,
		{ 112.f, 112.f },
		{ 0.f, 0.f },
		{ 112.f, 112.f },
		RGB(0, 255, 0));

	GameEngineImageFile* mapImage = mainSpriteRender_->GetImage();
	mapImage->TransCopy(boomEdgeSpriteRender100_->GetImage(),
		pos,
		{ 112.f, 112.f },
		{ 0.f, 0.f },
		{ 112.f, 112.f },
		RGB(0, 255, 0));

	mapImage->TransCopy(colSpriteRender_->GetImage(),
		{ 0.f, 0.f },
		colSpriteRender_->GetImageSize(),
		{ 0.f, 0.f },
		colSpriteRender_->GetImageSize(),
		RGB(0, 0, 255));
}

void MapTrain::BuildGirder(float4 pos, GameEngineRenderer* _Image, GameEngineRenderer* _ColImage)
{
	GameEngineImageFile* ColImage = colSpriteRender_->GetImage();
	ColImage->TransCopy(_ColImage->GetImage(),
		pos,
		_ColImage->GetImageSize(),
		{ 0.f, 0.f },
		_ColImage->GetImageSize(),
		RGB(255, 0, 255));

	GameEngineImageFile* mapImage = mainSpriteRender_->GetImage();
	mapImage->TransCopy(_Image->GetImage(),
		pos,
		_Image->GetImageSize(),
		{ 0.f, 0.f },
		_Image->GetImageSize(),
		RGB(255, 0, 255));
}

