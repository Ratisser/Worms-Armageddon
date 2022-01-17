#include "WindBar.h"
#include <GameEngineRenderer.h>
#include "WindController.h"

WindBar::WindBar() // default constructer 디폴트 생성자
{
	SetRenderOrder(10001);
	SetPos({ 1180,700 });
}

WindBar::~WindBar() // default destructer 디폴트 소멸자
{

}

WindBar::WindBar(WindBar&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
{

}

void WindBar::Start()
{
	mainRender_ = CreateRenderer("windBar");
	mainRender_->CreateAnimation("windToLeft", "windBar", 0, 7, true, 0.102f);
	mainRender_->CreateAnimation("windToRight", "windBar", 10, 17, true, 0.102f);
	mainRender_->CreateAnimation("default", "windBar", 8, 8, false, 0.102f);
	mainRender_->ChangeAnimation("default");
	mainRender_->SetCameraEffectOff();

}
void WindBar::UpdateBefore()
{

}
void WindBar::Update()
{
	switch (parentController_->windDir_)
	{
	case WindDir::TOLEFT:
	{
		SetPos({1135,700});
		mainRender_->ChangeAnimation("windToLeft");
		break;
	}
	case WindDir::TORIGHT:
	{
		SetPos({ 1225,700 });
		mainRender_->ChangeAnimation("windToRight");
		break;
	}
	case WindDir::NONE:
	{
		SetPos({ 1180,700 });
		mainRender_->ChangeAnimation("default");
		break;
	}

	default:
		break;
	}
}
void WindBar::UpdateAfter()
{

}
void WindBar::Render()
{
	mainRender_->AnimationUpdate();
}