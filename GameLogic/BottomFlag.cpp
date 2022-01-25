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