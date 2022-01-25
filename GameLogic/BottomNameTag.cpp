#include "BottomNameTag.h"
#include <GameEngineRenderer.h>
BottomNameTag::BottomNameTag() // default constructer ����Ʈ ������
	: mainRender_(nullptr), parentWorm_(nullptr)
{
	SetRenderOrder((int)RenderOrder::UI);
}

BottomNameTag::~BottomNameTag() // default destructer ����Ʈ �Ҹ���
{

}

BottomNameTag::BottomNameTag(BottomNameTag&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
	: mainRender_(nullptr), parentWorm_(nullptr)
{

}

void BottomNameTag::Start()
{
	mainRender_ = CreateRenderer("BottomNameTag");
	mainRender_->SetCameraEffectOff();
}

void BottomNameTag::UpdateBefore()
{

}

void BottomNameTag::Update()
{
	// �� ������ ���� ���ǿ��� �ٸ� Bottom UI �� �Բ� �� �Ʒ��� �̵��� ����
}

void BottomNameTag::UpdateAfter()
{

}

void BottomNameTag::Render()
{
	mainRender_->Render();
}