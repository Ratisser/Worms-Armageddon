#include "BottomHealthBar.h"
#include <GameEngineRenderer.h>
BottomHealthBar::BottomHealthBar() // default constructer ����Ʈ ������
	: mainRender_(nullptr), parentWorm_(nullptr)
{
	SetRenderOrder(10000);
}

BottomHealthBar::~BottomHealthBar() // default destructer ����Ʈ �Ҹ���
{

}

BottomHealthBar::BottomHealthBar(BottomHealthBar&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
	: mainRender_(nullptr), parentWorm_(nullptr)
{

}

void BottomHealthBar::Start()
{
	mainRender_ = CreateRenderer("BottomHPbarR");
	mainRender_->SetCameraEffectOff();
}

void BottomHealthBar::UpdateBefore()
{

}

void BottomHealthBar::Update()
{
	// �� ������ ���� ���ǿ��� �ٸ� Bottom UI �� �Բ� �� �Ʒ��� �̵��� ����
}

void BottomHealthBar::UpdateAfter()
{

}

void BottomHealthBar::Render()
{
	mainRender_->Render();
}