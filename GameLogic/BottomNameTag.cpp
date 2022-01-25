#include "BottomNameTag.h"
#include <GameEngineRenderer.h>
BottomNameTag::BottomNameTag() // default constructer 디폴트 생성자
	: mainRender_(nullptr), parentWorm_(nullptr)
{
	SetRenderOrder((int)RenderOrder::UI);
}

BottomNameTag::~BottomNameTag() // default destructer 디폴트 소멸자
{

}

BottomNameTag::BottomNameTag(BottomNameTag&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
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
	// 턴 끝나기 직전 세션에서 다른 Bottom UI 와 함께 위 아래로 이동할 예정
}

void BottomNameTag::UpdateAfter()
{

}

void BottomNameTag::Render()
{
	mainRender_->Render();
}