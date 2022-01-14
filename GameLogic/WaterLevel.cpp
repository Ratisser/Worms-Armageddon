#include "WaterLevel.h"
#include "WaterWave.h"
#include "UnderWater.h"

#include <GameEngineTime.h>
#include <GameEngineWindow.h>
#include <GameEngineRenderer.h>
#include <GameEngineInput.h>

#define MOVE_SPEED 100.f

WaterLevel::WaterLevel() // default constructer 디폴트 생성자
	:mainSpriteRender_(nullptr),
	waterLevel_(0.f)

{
}

WaterLevel::~WaterLevel() // default destructer 디폴트 소멸자
{

}

WaterLevel::WaterLevel(WaterLevel&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
	:mainSpriteRender_(nullptr),
	waterLevel_(0.f)
{
}

void WaterLevel::WaterLevelUp(float deltaTime)
{
	auto iterfirst = Waterlist.begin();
	auto iterEnd = Waterlist.end();

	for (; iterfirst != iterEnd; iterfirst++)
	{
		(*iterfirst)->SetMove(float4::UP * MOVE_SPEED * deltaTime);
	}
	waterLevel_ += (MOVE_SPEED * deltaTime);
}

void WaterLevel::WaterLevelDown(float deltaTime)
{
	auto iterfirst = Waterlist.begin();
	auto iterEnd = Waterlist.end();

	for (; iterfirst != iterEnd; iterfirst++)
	{
		(*iterfirst)->SetMove(float4::DOWN * MOVE_SPEED * deltaTime);
	}
	waterLevel_ -= (MOVE_SPEED * deltaTime);
}

void WaterLevel::Start()
{
	
	// 테스트 코드
	{
		if (false == GameEngineInput::GetInst().IsKey("TestWaterLevelUp"))
		{
			GameEngineInput::GetInst().CreateKey("TestWaterLevelUp", 'Q');
		}
		if (false == GameEngineInput::GetInst().IsKey("TestWaterLevelDown"))
		{
			GameEngineInput::GetInst().CreateKey("TestWaterLevelDown", 'E');
		}
	}
}

void WaterLevel::UpdateBefore()
{

}

void WaterLevel::Update()
{
	float deltaTime = GameEngineTime::GetInst().GetDeltaTime();

	// 테스트 코드
	{
		if (true == GameEngineInput::GetInst().IsPress("TestWaterLevelUp"))
		{
			WaterLevelUp(deltaTime);
		}
		if (true == GameEngineInput::GetInst().IsPress("TestWaterLevelDown"))
		{
			WaterLevelDown(deltaTime);
		}
	}
}

void WaterLevel::UpdateAfter()
{
}


void WaterLevel::Render()
{
	//mainSpriteRender_->Render();
}

