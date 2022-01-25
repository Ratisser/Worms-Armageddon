#include "BottomFlag.h"
#include <GameEngineRenderer.h>

BottomFlag::BottomFlag() // default constructer ����Ʈ ������
	: mainRender_(nullptr), parentWorm_(nullptr)
{
	SetRenderOrder((int)RenderOrder::UI);
}

BottomFlag::~BottomFlag() // default destructer ����Ʈ �Ҹ���
{

}

BottomFlag::BottomFlag(BottomFlag&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
	: mainRender_(nullptr), parentWorm_(nullptr)
{

}


void BottomFlag::Start()
{
	mainRender_ = CreateRenderer("BottomFlagRUS");
	mainRender_->SetCameraEffectOff();
}

void BottomFlag::UpdateBefore()
{

}

void BottomFlag::Update()
{
	// �� ������ ���� ���ǿ��� �ٸ� Bottom UI �� �Բ� �� �Ʒ��� �̵��� ����
}

void BottomFlag::UpdateAfter()
{

}

void BottomFlag::Render()
{
	mainRender_->Render();
}