#include "BottomFlag.h"
#include <GameEngineRenderer.h>

BottomFlag::BottomFlag() // default constructer 디폴트 생성자
	: mainRender_(nullptr), parentWorm_(nullptr)
{
	SetRenderOrder((int)RenderOrder::UI);
}

BottomFlag::~BottomFlag() // default destructer 디폴트 소멸자
{

}

BottomFlag::BottomFlag(BottomFlag&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
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
	// 턴 끝나기 직전 세션에서 다른 Bottom UI 와 함께 위 아래로 이동할 예정
}

void BottomFlag::UpdateAfter()
{

}

void BottomFlag::Render()
{
	mainRender_->Render();
}


void BottomFlag::NationInit(int _wormNumber)
{
	switch (_wormNumber)
	{
	case 0:
		mainRender_ = CreateRenderer("BottomFlagRUS");
		break;
	case 1:
		mainRender_ = CreateRenderer("BottomFlagBRA");
		break;
	case 2:
		mainRender_ = CreateRenderer("BottomFlagKOR");
		break;
	case 3:
		mainRender_ = CreateRenderer("BottomFlagUSA");
		break;
	case 4:
		mainRender_ = CreateRenderer("BottomFlagGER");
		break;
	case 5:
		mainRender_ = CreateRenderer("BottomFlagJPN");
		break;
	case 6:
		mainRender_ = CreateRenderer("BottomFlagRUS");
		break;
	case 7:
		mainRender_ = CreateRenderer("BottomFlagRUS");
		break;
	default:
		mainRender_ = CreateRenderer("BottomFlagRUS");
		break;
	}
}
void BottomFlag::StartPosInit(int _wormNumber)
{
	switch (_wormNumber)
	{
	case 0:
		SetPos({ 605, 580 });
		break;
	case 1:
		SetPos({ 605, 600 });
		break;
	case 2:
		SetPos({ 605, 620 });
		break;
	case 3:
		SetPos({ 605, 640 });
		break;
	case 4:
		SetPos({ 605, 660 });
		break;
	case 5:
		SetPos({ 605, 680 });
		break;
	case 6:
		SetPos({ 605, 700 });
		break;
	case 7:
		SetPos({ 605, 720 });
		break;
	default:
		SetPos({ 0, 0 });
		break;
	}
	mainRender_->SetCameraEffectOff();
}