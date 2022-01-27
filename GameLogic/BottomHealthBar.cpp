#include "BottomHealthBar.h"
#include <GameEngineRenderer.h>
BottomHealthBar::BottomHealthBar() // default constructer 디폴트 생성자
	: mainRender_(nullptr), parentWorm_(nullptr)
{
	SetRenderOrder((int)RenderOrder::UI);
}

BottomHealthBar::~BottomHealthBar() // default destructer 디폴트 소멸자
{

}

BottomHealthBar::BottomHealthBar(BottomHealthBar&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
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
	// 턴 끝나기 직전 세션에서 다른 Bottom UI 와 함께 위 아래로 이동할 예정
}

void BottomHealthBar::UpdateAfter()
{

}

void BottomHealthBar::Render()
{
	mainRender_->Render();
}

void BottomHealthBar::RenderColorInit(int _wormNumber) // 웜의 번호를 받아 체력바의 색깔을 조정해줍니다.
{
	switch (_wormNumber)
	{
	case 0:
		mainRender_ = CreateRenderer("BottomHPbarR");
		break;
	case 1:
		mainRender_ = CreateRenderer("BottomHPbarB");
		break;
	case 2:
		mainRender_ = CreateRenderer("BottomHPbarG");
		break;
	case 3:
		mainRender_ = CreateRenderer("BottomHPbarY");
		break;
	case 4:
		mainRender_ = CreateRenderer("BottomHPbarP");
		break;
	case 5:
		mainRender_ = CreateRenderer("BottomHPbarS");
		break;
	case 6:
		mainRender_ = CreateRenderer("BottomHPbarR");
		break;
	case 7:
		mainRender_ = CreateRenderer("BottomHPbarR");
		break;
	default:
		mainRender_ = CreateRenderer("BottomHPbarR");
		break;
	}
}

void BottomHealthBar::StartPosInit(int _wormNumber) // 웜의 번호를 받아 체력바의 색깔을 조정해줍니다.
{
	switch (_wormNumber)
	{
	case 0:
		SetPos({ 672, 580 });
		break;
	case 1:
		SetPos({ 672, 600 });
		break;
	case 2:
		SetPos({ 672, 620 });
		break;
	case 3:
		SetPos({ 672, 640 });
		break;
	case 4:
		SetPos({ 672, 660 });
		break;
	case 5:
		SetPos({ 672, 680 });
		break;
	case 6:
		SetPos({ 672, 700 });
		break;
	case 7:
		SetPos({ 672, 720 });
		break;
	default:
		SetPos({ 0, 0 });
		break;
	}
	mainRender_->SetCameraEffectOff();
}

void BottomHealthBar::DamageInit(int _damage)
{

}