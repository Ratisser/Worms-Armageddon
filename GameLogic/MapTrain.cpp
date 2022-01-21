#include "MapTrain.h"
#include "GlobalValue.h"
#include "eCollisionGroup.h"

#include <GameEngineWindow.h>
#include <GameEngineRenderer.h>
#include <GameEngineCollision.h>
#include "GameEngineImage.h"
#include "GameEngineImageFile.h"

MapTrain::MapTrain() // default constructer ����Ʈ ������
	:firstupdate_(false),
	gradationSpriteRender_(nullptr),
	mainSpriteRender_(nullptr),
	colSpriteRender_(nullptr),
	boomSpriteRender_(nullptr),
	boomEdgeSpriteRender_(nullptr)
{
	SetRenderOrder((int)RenderOrder::Map);
}

MapTrain::~MapTrain() // default destructer ����Ʈ �Ҹ���
{

}

MapTrain::MapTrain(MapTrain&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
	:firstupdate_(_other.firstupdate_),
	gradationSpriteRender_(nullptr),
	mainSpriteRender_(nullptr),
	colSpriteRender_(nullptr),
	boomSpriteRender_(nullptr),
	boomEdgeSpriteRender_(nullptr)
{

}

void MapTrain::Start()
{
	float4 WindowSize = GameEngineWindow::GetInst().GetSize();

	gradationSpriteRender_ = CreateRenderer("Gradient");
	float4 ImageSize = gradationSpriteRender_->GetImageSize();
	gradationSpriteRender_->SetPivotPos(ImageSize.halffloat4());
	gradationSpriteRender_->SetCameraEffectOff();

	gradationSpriteRender_->SetRenderSize(WindowSize);

	boomSpriteRender_ = CreateRenderer("Boom");
	boomEdgeSpriteRender_ = CreateRenderer("BoomEdge");
}

void MapTrain::UpdateBefore()
{
	// �������� �̶� �����Ѵ�
	if (false == firstupdate_)
	{
		// �� ������ ���� �� ��ġ ����
		mainSpriteRender_ = CreateRenderer(GlobalValue::CurPlayMap);
		float4 imageSize = mainSpriteRender_->GetImageSize();
		mainSpriteRender_->SetPivotPos(imageSize.halffloat4());

		// �浹�� ������ ���� �� ��ġ ����
		colSpriteRender_ = CreateRenderer(GlobalValue::CurPlayColMap);
		imageSize = colSpriteRender_->GetImageSize();
		colSpriteRender_->SetPivotPos(imageSize.halffloat4());

		bodyCollision_ = CreateCollision(eCollisionGroup::MAP, CollisionCheckType::IMAGE);
		bodyCollision_->SetImage(GlobalValue::CurPlayColMap);

		// ���ʰ����϶��� ����ǵ��� ����
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
	// �׶��̼� 
	gradationSpriteRender_->Render();

	// �浹��
	colSpriteRender_->Render();

	// ��¥ ��
	mainSpriteRender_->Render();
}

void MapTrain::GroundUpdate(float4 pos)
{
	GameEngineImageFile* ColImage = colSpriteRender_->GetImage();
	ColImage->TransCopy(boomSpriteRender_->GetImage(),
		pos,
		{ 100.f, 100.f },
		{ 0.f, 0.f },
		{ 100.f, 100.f },
		RGB(0, 255, 0));

	GameEngineImageFile* mapImage = mainSpriteRender_->GetImage();
	mapImage->TransCopy(boomEdgeSpriteRender_->GetImage(),
		pos,
		{ 100.f, 100.f },
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

