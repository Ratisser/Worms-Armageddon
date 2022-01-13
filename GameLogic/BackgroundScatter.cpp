#include "BackgroundScatter.h"
#include "WindController.h"
#include <GameEngineTime.h>
#include <GameEngineRenderer.h>	
#include <GameEngineMath.h>

BackgroundScatter::BackgroundScatter() // default constructer ����Ʈ ������
: mainRender_(nullptr), spawnPos_({0,-1000.0f})
{
	this->SetPos({1,0});
	SetRenderOrder(1);
}

BackgroundScatter::~BackgroundScatter() // default destructer ����Ʈ �Ҹ���
{

}

BackgroundScatter::BackgroundScatter(BackgroundScatter&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
	: mainRender_(nullptr), spawnPos_({ 0,-1000.0f })
{

}


void BackgroundScatter::Start()
{
	mainRender_ = CreateRenderer("ScatterStar");
	fallSpeed_ = randomGenerator_.RandomFloat(100.0f, 400.0f);
	spawnPos_.x = randomGenerator_.RandomFloat(0.0f, 3000.0f);
	int a = randomGenerator_.RandomInt(0, 9);

	if (5 <= a)
	{
		mainRender_->SetImage("ScatterSnow");
	}
}

void BackgroundScatter::UpdateBefore()
{
}

void BackgroundScatter::Update()
{
		SetMove({ parent_->windSpeed_ * GameEngineTime::GetInst().GetDeltaTime(), fallSpeed_ * GameEngineTime::GetInst().GetDeltaTime() });
}

void BackgroundScatter::UpdateAfter()
{
	if (this->GetPos().y > 1000.0f) // ���麸�� pos �� ������ ���
	{
		SetPos({ randomGenerator_.RandomFloat(0.0f, 3000.0f) , spawnPos_.y}); // ��ġ����
	}
}

void BackgroundScatter::Render()
{
	mainRender_->Render();
}