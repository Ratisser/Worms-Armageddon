#include "FadeObject.h"
#include <GameEngineRenderer.h>
#include <GameEngineWindow.h>


// Static Var
// Static Func

// constructer destructer
FadeObject::FadeObject()
	:FadeState(this)
	, Alpha_(255.0f)
{
}

FadeObject::~FadeObject()
{
}

FadeObject::FadeObject(FadeObject&& _other) noexcept
	:FadeState(this)
{
}

void FadeObject::FadeIn() 
{
	FadeState.ChangeState("FadeIn");
}
void FadeObject::FadeOut() 
{
	FadeState.ChangeState("FadeOut");
}

void FadeObject::Start() 
{
	SetRenderOrder(200000);
	mainRender_ = CreateRenderer("BackGround.bmp");
	mainRender_->SetPivotPos(GameEngineWindow::GetInst().GetSize().halffloat4());
	mainRender_->SetCameraEffectOff();

	FadeState.CreateState("FadeIn", &FadeObject::FadeInStart, &FadeObject::FadeInUpdate);
	FadeState.CreateState("FadeOut", &FadeObject::FadeOutStart, &FadeObject::FadeOutUpdate);
	FadeState.ChangeState("FadeOut");
}


void FadeObject::Update() 
{
	FadeState.Update();

}

void FadeObject::Render() 
{
	mainRender_->Render();
}

//member Func

StateInfo FadeObject::FadeInStart(StateInfo _Info)
{
	Alpha_ = 0.0f;
	return "";
}

StateInfo FadeObject::FadeOutStart(StateInfo _Info)
{
	Alpha_ = 255.0f;
	return "";
}

StateInfo FadeObject::FadeInUpdate(StateInfo _Info)
{
	Alpha_ += 100.0f * GameEngineTime::GetInst().GetDeltaTime();
	mainRender_->SetAlpha(static_cast<int>(Alpha_));
	return "";
}

StateInfo FadeObject::FadeOutUpdate(StateInfo _Info)
{
	Alpha_ -= 100.0f * GameEngineTime::GetInst().GetDeltaTime();
	mainRender_->SetAlpha(static_cast<int>(Alpha_));
	return "";
}