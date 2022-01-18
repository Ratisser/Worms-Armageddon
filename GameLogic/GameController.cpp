#include "GameController.h"

#include <GameEngineMath.h>
#include <GameEngineLevel.h>
#include "Worm.h"

GameController::GameController() // default constructer ����Ʈ ������
	: currentIndex_(0)
	, currentWorm_(nullptr)
{

}

GameController::~GameController() // default destructer ����Ʈ �Ҹ���
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
		GameEngineDebug::MsgBoxError("�ִ� ������ ������ �ʰ��Ͽ����ϴ�.");
		return;
	}

	GameEngineMath::Random randomGenerator;
	std::string name = "Worm";
	name += std::to_string(currentIndex_++);
	Worm* newWorm = parentLevel_->CreateActor<Worm>(name);
	newWorm->SetPos({ randomGenerator.RandomFloat(_minX, _maxX) , -500.0f });


}
