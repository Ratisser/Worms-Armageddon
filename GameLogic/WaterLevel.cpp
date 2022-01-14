#include "WaterLevel.h"
#include "WaterWave.h"
#include "UnderWater.h"

#include <GameEngineTime.h>
#include <GameEngineWindow.h>
#include <GameEngineRenderer.h>
#include <GameEngineInput.h>

#define MOVE_SPEED 100.f

WaterLevel::WaterLevel() // default constructer ����Ʈ ������
	:mainSpriteRender_(nullptr),
	waterLevel_(0.f)

{
}

WaterLevel::~WaterLevel() // default destructer ����Ʈ �Ҹ���
{

}

WaterLevel::WaterLevel(WaterLevel&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
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
	
	// �׽�Ʈ �ڵ�
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

	// �׽�Ʈ �ڵ�
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

