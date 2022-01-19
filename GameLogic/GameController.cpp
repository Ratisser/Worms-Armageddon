#include "GameController.h"

#include <GameEngineMath.h>
#include <GameEngineWindow.h>
#include <GameEngineLevel.h>
#include <GameEngineInput.h>
#include "Worm.h"

GameController::GameController() // default constructer 디폴트 생성자
	: currentIndex_(0)
	, currentWorm_(nullptr)
	, cameraMoveSpeed_(10.f)
	, wormIndex_(MAX_WORM_COUNT)
	, IsCameraMove_(true)
{

}

GameController::~GameController() // default destructer 디폴트 소멸자
{

}

void GameController::Start()
{
	if (false == GameEngineInput::GetInst().IsKey("Up"))
	{
		GameEngineInput::GetInst().CreateKey("Up", VK_UP);
	}

	if (false == GameEngineInput::GetInst().IsKey("Down"))
	{
		GameEngineInput::GetInst().CreateKey("Down", VK_DOWN);
	}

	if (false == GameEngineInput::GetInst().IsKey("Left"))
	{
		GameEngineInput::GetInst().CreateKey("Left", VK_LEFT);
	}

	if (false == GameEngineInput::GetInst().IsKey("Right"))
	{
		GameEngineInput::GetInst().CreateKey("Right", VK_RIGHT);
	}

	if (false == GameEngineInput::GetInst().IsKey("CameraFocus"))
	{
		GameEngineInput::GetInst().CreateKey("CameraFocus", 0x31);
	}
}

void GameController::UpdateBefore()
{
}

void GameController::Update()
{
	if (true == GameEngineInput::GetInst().IsPress("Up"))
	{
		GetLevel()->SetCamMove(float4::UP * cameraMoveSpeed_);
	}

	if (true == GameEngineInput::GetInst().IsPress("Down"))
	{
		GetLevel()->SetCamMove(float4::DOWN * cameraMoveSpeed_);
	}

	if (true == GameEngineInput::GetInst().IsPress("Left"))
	{
		GetLevel()->SetCamMove(float4::LEFT * cameraMoveSpeed_);
	}

	if (true == GameEngineInput::GetInst().IsPress("Right"))
	{
		GetLevel()->SetCamMove(float4::RIGHT * cameraMoveSpeed_);
	}

	if (true == GameEngineInput::GetInst().IsDown("CameraFocus"))
	{
		++wormIndex_;

		if (true == IsCameraMove_)
		{
			wormIndex_ = 0;
			IsCameraMove_ = false;
		}	

		if (false == IsCameraMove_)
		{
			for (int i = 0; i < MAX_WORM_COUNT; i++)
			{
				if (i == wormIndex_)
				{
					wormList_[wormIndex_]->SetFocus(true);
				}
				else
				{
					wormList_[i]->SetFocus(false);
				}
			}
		}
	}

	if (wormIndex_ == MAX_WORM_COUNT)
	{
		IsCameraMove_ = true;

		for (int i = 0; i < MAX_WORM_COUNT; ++i)
		{
			wormList_[i]->SetFocus(false);
		}
	}
	else
	{
		GetLevel()->SetCamPos(wormList_[wormIndex_]->GetPos() - GameEngineWindow::GetInst().GetSize().halffloat4());
	}
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
	randomFloatContainer_ = randomGenerator.RandomFloat(_minX, _maxX); // 전에 생성한 좌표를 저장

	std::vector<float>::iterator startIter = xPosList_.begin();
	std::vector<float>::iterator endIter = xPosList_.end();
	for (; startIter != endIter; startIter++)
	{
		if (randomFloatContainer_ >= *startIter - 100.0f && randomFloatContainer_ <= *startIter + 100.0f)
		{
			randomFloatContainer_ = randomGenerator.RandomFloat(_minX, _maxX);
		}
	}
	
	newWorm->SetPos({ randomFloatContainer_ , -500.0f });
	newWorm->SetFocus(false);
	wormList_.push_back(newWorm);
	xPosList_.push_back(randomFloatContainer_);
}
