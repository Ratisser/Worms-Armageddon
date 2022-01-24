#include "GameEngineTime.h"

// Static Var
GameEngineTime* GameEngineTime::Inst = new GameEngineTime();
// Static Func
// constructer destructer
GameEngineTime::GameEngineTime() :
	F_(0),
	FPS_(0),
	Second_(0.f),
	deltaTime_(0.f)
{
	TimeCheckReset();
}

GameEngineTime::~GameEngineTime()
{
}

GameEngineTime::GameEngineTime(const GameEngineTime&& _Other)
	: timeCount_(_Other.timeCount_),
	startCheck_(_Other.startCheck_),
	endCheck_(_Other.endCheck_),
	F_(0),
	FPS_(0),
	Second_(0.f),
	deltaTime_(0.f)
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

	Second_ += deltaTime_;
	F_++;

	if (Second_ >= 1.f)
	{
		FPS_ = F_;
		F_ = 0;
		Second_ = 0.f;
	}
}