#include <GameEngineLevelManager.h>
#include <GameEngineLevel.h>
#include <GameEngineInput.h>
#include <GameEngineWindow.h>

#include "MapTrain.h"
#include "PlayLevel.h"
#include "Worm.h"
#include "UIController.h"

#include "BottomHealthBar.h"
#include "BottomNameTag.h"
#include "BottomFlag.h"

#include "WaterWave.h"
#include "UnderWater.h"


#include "BackgroundScatter.h"

PlayLevel::PlayLevel() // default constructer 디폴트 생성자
{

}

PlayLevel::~PlayLevel() // default destructer 디폴트 소멸자
{

}

PlayLevel::PlayLevel(PlayLevel&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
{

}

void PlayLevel::Loading()
{
	if (false == GameEngineInput::GetInst().IsKey("Debug_Next"))
	{
		GameEngineInput::GetInst().CreateKey("Debug_Next", 'P');
	}
	CreateActor<MapTrain>();


	if (false == GameEngineInput::GetInst().IsKey("Up"))
	{
		GameEngineInput::GetInst().CreateKey("Up", 'w');
	}
	if (false == GameEngineInput::GetInst().IsKey("Down"))
	{
		GameEngineInput::GetInst().CreateKey("Down", 's');
	}
	if (false == GameEngineInput::GetInst().IsKey("Left"))
	{
		GameEngineInput::GetInst().CreateKey("Left", 'a');
	}
	if (false == GameEngineInput::GetInst().IsKey("Right"))
	{
		GameEngineInput::GetInst().CreateKey("Right", 'd');
	}

	CreateActor<Worm>();

	for (int i = 0; i < 39; i++)
	{
		// 배경 바람에 흩날리는 엑터 생성(추후 자료구조로 관리 예정)
		BackgroundScatter* newScatter = CreateActor<BackgroundScatter>();
	}

	{
		// 플레이화면 하단 체력바
		BottomNameTag* p1NameTag = CreateActor<BottomNameTag>();
		p1NameTag->SetPos({ 555, 700 });

		BottomFlag* p1Flag = CreateActor<BottomFlag>();
		p1Flag->SetPos({ 610, 700 });

		BottomHealthBar* p1Health = CreateActor<BottomHealthBar>();
		p1Health->SetPos({ 672, 700 });
	}

	// UI관리자생성
	CreateActor<UIController>();
	MakeWaterLevel();
}

void PlayLevel::LevelUpdate()
{
	if (true == GameEngineInput::GetInst().IsDown("Debug_Next"))
	{
		GameEngineLevelManager::GetInst().ChangeLevel("LobbyLevel");
	}

	if (true == GameEngineInput::GetInst().IsPress("Up"))
	{
		GameEngineLevel::SetCamMove(float4::UP);
	}
	if (true == GameEngineInput::GetInst().IsPress("Down"))
	{
		GameEngineLevel::SetCamMove(float4::DOWN);
	}
	if (true == GameEngineInput::GetInst().IsPress("Left"))
	{
		GameEngineLevel::SetCamMove(float4::LEFT);
	}
	if (true == GameEngineInput::GetInst().IsPress("Right"))
	{
		GameEngineLevel::SetCamMove(float4::RIGHT);
	}
}

void PlayLevel::MakeWaterLevel() // 이현
{
	WaterLevel_ = CreateActor<WaterLevel>("WaterLevel");

	WaterWave* WaterWave1 = CreateActor<WaterWave>("WaterWave1");
	WaterWave* WaterWave2 = CreateActor<WaterWave>("WaterWave2");
	WaterWave* WaterWave3 = CreateActor<WaterWave>("WaterWave3");
	WaterWave* WaterWave4 = CreateActor<WaterWave>("WaterWave4");
	WaterWave* WaterWave5 = CreateActor<WaterWave>("WaterWave5");
	UnderWater* UnderWater1 = CreateActor<UnderWater>("UnderWater");

	UnderWater1->SetPos(float4(0.f, 1580,0.f));

	WaterWave1->SetRenderOrder(0);
	WaterWave1->SetPos(float4(0.f, 900, 0.f));

	WaterWave2->SetRenderOrder(0);
	WaterWave2->SetPos(float4(0.f, 930, 0.f));
	WaterWave2->ChangeAnimationframe(2);

	WaterWave3->SetRenderOrder(1);
	WaterWave3->SetPos(float4(0.f, 960, 0.f));
	WaterWave3->ChangeAnimationframe(4);

	WaterWave4->SetRenderOrder(1);
	WaterWave4->SetPos(float4(0.f, 990, 0.f));
	WaterWave4->ChangeAnimationframe(6);

	WaterWave5->SetRenderOrder(1);
	WaterWave5->SetPos(float4(0.f, 1020, 0.f));
	WaterWave5->ChangeAnimationframe(8);


	WaterWave* WaterWave6 = CreateActor<WaterWave>("WaterWave6");
	WaterWave* WaterWave7 = CreateActor<WaterWave>("WaterWave7");
	WaterWave* WaterWave8 = CreateActor<WaterWave>("WaterWave8");
	WaterWave* WaterWave9 = CreateActor<WaterWave>("WaterWave9");
	WaterWave* WaterWave10 = CreateActor<WaterWave>("WaterWave10");
	UnderWater* UnderWater2 = CreateActor<UnderWater>("UnderWater2");
	UnderWater2->SetPos(float4(2560.f, 1580, 0.f));

	WaterWave6->SetRenderOrder(0);
	WaterWave6->SetPos(float4(2560.f, 900, 0.f));

	WaterWave7->SetRenderOrder(0);
	WaterWave7->SetPos(float4(2560.f, 930, 0.f));
	WaterWave7->ChangeAnimationframe(2);

	WaterWave8->SetRenderOrder(1);
	WaterWave8->SetPos(float4(2560.f, 960, 0.f));
	WaterWave8->ChangeAnimationframe(4);

	WaterWave9->SetRenderOrder(1);
	WaterWave9->SetPos(float4(2560.f, 990, 0.f));
	WaterWave9->ChangeAnimationframe(6);

	WaterWave10->SetRenderOrder(1);
	WaterWave10->SetPos(float4(2560.f, 1020,0.f));
	WaterWave10->ChangeAnimationframe(8);

	WaterLevel_->Waterlist.push_back(WaterWave1);
	WaterLevel_->Waterlist.push_back(WaterWave2);
	WaterLevel_->Waterlist.push_back(WaterWave3);
	WaterLevel_->Waterlist.push_back(WaterWave4);
	WaterLevel_->Waterlist.push_back(WaterWave5);
	WaterLevel_->Waterlist.push_back(WaterWave6);
	WaterLevel_->Waterlist.push_back(WaterWave7);
	WaterLevel_->Waterlist.push_back(WaterWave8);
	WaterLevel_->Waterlist.push_back(WaterWave9);
	WaterLevel_->Waterlist.push_back(WaterWave10);
	WaterLevel_->Waterlist.push_back(UnderWater1);
	WaterLevel_->Waterlist.push_back(UnderWater2);
}