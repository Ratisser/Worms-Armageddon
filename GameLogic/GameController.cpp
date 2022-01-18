#include "GameController.h"

#include <GameEngineMath.h>
#include <GameEngineLevel.h>
#include "Worm.h"

GameController::GameController() // default constructer 디폴트 생성자
	: currentIndex_(0)
	, currentWorm_(nullptr)
{

}

GameController::~GameController() // default destructer 디폴트 소멸자
{

}

void GameController::Start()
{
}

void GameController::UpdateBefore()
{
}

void GameController::Update()
{
}

void GameController::UpdateAfter()
{
}

void GameController::Render()
{
}

void GameController::CreateWorm(const float _minX, const float _maxX)
{
	if (wormList_.size() >= MAX_WORM_COUNT)
	{
		GameEngineDebug::MsgBoxError("최대 지렁이 개수를 초과하였습니다.");
		return;
	}

	GameEngineMath::Random randomGenerator;
	std::string name = "Worm";
	name += std::to_string(currentIndex_++);
	Worm* newWorm = parentLevel_->CreateActor<Worm>(name);
	newWorm->SetPos({ randomGenerator.RandomFloat(_minX, _maxX) , -500.0f });


}
