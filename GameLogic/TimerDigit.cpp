#include "TimerDigit.h"
#include "TimerManager.h"
#include <GameEngineRenderer.h>

TimerDigit::TimerDigit() // default constructer 디폴트 생성자
	: mainRender_(nullptr), timerManager_(nullptr), curCount_(0.0f)
{

}

TimerDigit::~TimerDigit() // default destructer 디폴트 소멸자
{

}

TimerDigit::TimerDigit(TimerDigit&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
	: mainRender_(nullptr), timerManager_(nullptr), curCount_(0.0f)
{

}

void TimerDigit::AnimationInit()
{
	mainRender_ = CreateRenderer("TimerNum");
	mainRender_->CreateAnimation("0", "TimerNum", 0, 0, false, 1.0f);
	mainRender_->CreateAnimation("1", "TimerNum", 1, 1, false, 1.0f);
	mainRender_->CreateAnimation("2", "TimerNum", 2, 2, false, 1.0f);
	mainRender_->CreateAnimation("3", "TimerNum", 3, 3, false, 1.0f);
	mainRender_->CreateAnimation("4", "TimerNum", 4, 4, false, 1.0f);
	mainRender_->CreateAnimation("5", "TimerNum", 5, 5, false, 1.0f);
	mainRender_->CreateAnimation("6", "TimerNum", 6, 6, false, 1.0f);
	mainRender_->CreateAnimation("7", "TimerNum", 7, 7, false, 1.0f);
	mainRender_->CreateAnimation("8", "TimerNum", 8, 8, false, 1.0f);
	mainRender_->CreateAnimation("9", "TimerNum", 9, 9, false, 1.0f);
	mainRender_->ChangeAnimation("0");
}


void TimerDigit::Start()
{
	AnimationInit();

}
void TimerDigit::UpdateBefore()
{

}
void TimerDigit::Update()
{
	if (false == this->IsOn())
	{
		// 디버깅 무한 시간 시 적용할 수 있는 코드
		mainRender_->ChangeAnimation("9");
		return;
	}





}
void TimerDigit::UpdateAfter()
{

}
void TimerDigit::Render()
{
	if (true)
	{
		mainRender_->AnimationUpdate();
	}

}

