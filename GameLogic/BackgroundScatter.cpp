#include "BackgroundScatter.h"
#include <GameEngineTime.h>
#include <GameEngineRenderer.h>	
#include <GameEngineMath.h>

BackgroundScatter::BackgroundScatter() // default constructer ����Ʈ ������
	: windSpeed_(0.0f), fallSpeed_(0.0f), mainRender_(nullptr), spawnPos_({0,-1000.0f})
{
	this->SetPos({1,0});
	SetRenderOrder(1);
}

BackgroundScatter::~BackgroundScatter() // default destructer ����Ʈ �Ҹ���
{

}

BackgroundScatter::BackgroundScatter(BackgroundScatter&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
	: windSpeed_(0.0f), fallSpeed_(0.0f), mainRender_(nullptr), spawnPos_({ 0,-1000.0f })
{

}


void BackgroundScatter::Start()
{
	mainRender_ = CreateRenderer("ScatterStar");
	windSpeed_ = randomGenerator_.RandomFloat(100.0f, 400.0f);
	fallSpeed_ = randomGenerator_.RandomFloat(100.0f, 400.0f);
	spawnPos_.x = randomGenerator_.RandomFloat(0.0f, 3000.0f);
}

void BackgroundScatter::UpdateBefore()
{

}

void BackgroundScatter::Update()
{
	SetMove(float4::DOWN * fallSpeed_ * GameEngineTime::GetInst().GetDeltaTime());

	if (true)
	{
		SetMove(float4::LEFT * windSpeed_ * GameEngineTime::GetInst().GetDeltaTime());
	}
	else if (true)
	{
		SetMove(float4::RIGHT * windSpeed_ * GameEngineTime::GetInst().GetDeltaTime());
	}
	
}

void BackgroundScatter::UpdateAfter()
{
	if (this->GetPos().y > 1000.0f) // ���麸�� pos �� ������ ���
	{
		SetPos(spawnPos_); // ��ġ����
	}
}

void BackgroundScatter::Render()
{
	mainRender_->Render();
}