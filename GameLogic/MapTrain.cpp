#include "MapTrain.h"
#include "GlobalValue.h"
#include <GameEngineWindow.h>
#include <GameEngineRenderer.h>
#include "GameEngineImage.h"
#include "GameEngineImageFile.h"

MapTrain::MapTrain() // default constructer ����Ʈ ������
	:firstupdate_(false),
	mainSpriteRender_(nullptr),
	colSpriteRender_(nullptr),
	boomSpriteRender_(nullptr)
{
	SetRenderOrder((int)RenderOrder::Map);
}

MapTrain::~MapTrain() // default destructer ����Ʈ �Ҹ���
{

}

MapTrain::MapTrain(MapTrain&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
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
	// �浹��
	colSpriteRender_->Render();

	// ��¥ ��
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

