#include "GameEngineTime.h"

// Static Var
GameEngineTime* GameEngineTime::Inst = new GameEngineTime();
// Static Func
// constructer destructer
GameEngineTime::GameEngineTime() :
	F_(0),
	FPS_(0),
	Second_(0),
	deltaTime_(0.0)
{
	TimeCheckReset();
}

GameEngineTime::~GameEngineTime()
{
}

// �ð��� �غ� �Ѵ�.
void GameEngineTime::TimeCheckReset()
{
	// window�� ���� �������ϴ�.
	QueryPerformanceFrequency(&timeCount_);
	QueryPerformanceCounter(&startCheck_);
	QueryPerformanceCounter(&endCheck_);
}

void GameEngineTime::TimeCheck()
{
	QueryPerformanceCounter(&endCheck_);
	deltaTime_ = static_cast<double>((endCheck_.QuadPart - startCheck_.QuadPart)) / static_cast<double>(timeCount_.QuadPart);
	startCheck_.QuadPart = endCheck_.QuadPart;

	Second_ += static_cast<float>(deltaTime_);
	F_++;

	if (Second_ >= 1.f)
	{
		FPS_ = F_;
		F_ = 0;
		Second_ = 0.f;
	}
}