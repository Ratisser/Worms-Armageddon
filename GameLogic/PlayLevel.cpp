#include <GameEngineLevelManager.h>
#include <GameEngineLevel.h>
#include <GameEngineInput.h>
#include <GameEngineWindow.h>
#include <GameEngineDebugExtension.h>
#include <GameEngineTime.h>

#include "LoadingImage.h"
#include "BackGroundGradation.h"
#include "MouseObject.h"
#include "MapTrain.h"
#include "PlayLevel.h"
#include "Worm.h"
#include "GameController.h"
#include "DrumActor.h"
#include "Bazooka.h"
#include "Uzi.h"
#include "UziBullet.h"

#include "BottomHealthBar.h"
#include "BottomNameTag.h"
#include "BottomFlag.h"
#include "WindBarBlank.h"
#include "WindBar.h"
#include "WindBarHider.h"

#include "WaterWave.h"
#include "UnderWater.h"

#include "EffectActor.h"
#include "ExplosionSize.h"

#include "BackgroundScatter.h"
#include "Midground.h"
#include "WindController.h"
#include "FadeObject.h"
#include "Cloud.h"

#include "GlobalValue.h"


FadeObject* PlayLevel::fadeObject_ = nullptr;

PlayLevel::PlayLevel() // default constructer 디폴트 생성자
	: Train_(nullptr),
	Bazooka_(nullptr),
	WaterLevel_(nullptr),
	windController_(nullptr),
	isDebugOn_(true),
	randomGenerator_(),
	isWormLanded_(false),// default constructer 디폴트 생성자
	fadeInterTime_(0.0f),
	isFadeIn_(false),
	Controller_(nullptr)
{

}

PlayLevel::~PlayLevel() // default destructer 디폴트 소멸자
{

}

PlayLevel::PlayLevel(PlayLevel&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자	
	: Train_(nullptr),
	Bazooka_(nullptr),
	WaterLevel_(nullptr),
	windController_(nullptr),
	isDebugOn_(true),
	randomGenerator_(),
	isWormLanded_(false),
	fadeInterTime_(0.0f),
	isFadeIn_(false),
	Controller_(nullptr)
{

}

void PlayLevel::Loading()
{
	if (false == GameEngineInput::GetInst().IsKey("Debug_Next"))
	{
		GameEngineInput::GetInst().CreateKey("Debug_Next", 'P');
	}
	
	fadeObject_ = CreateActor<FadeObject>();
	loadingImage_ = CreateActor<LoadingImage>();

	CreateActor<BackGroundGradation>();
	Train_ = CreateActor<MapTrain>();
	Train_->UpdateBefore();

	{
		windController_ = CreateActor<WindController>();
	}

	for (int i = 0; i < 70; i++)
	{
		BackgroundScatter* newScatter = CreateActor<BackgroundScatter>();
		newScatter->SetParent(windController_);
	}

	for (int i = 0; i < 50; i++)
	{
		Cloud* newCloud = CreateActor<Cloud>();
		newCloud->SetParent(windController_);
	}

	// 뒷배경 생성
	CreateActor<Midground>();
	// 바람 UI 바 생성
	CreateActor<WindBarBlank>();
	WindBar* windBar = CreateActor<WindBar>();
	windBar->SetParentController(windController_);
	WindBarHider* windBarHider = CreateActor<WindBarHider>();
	windBarHider->SetParentController(windController_);

	MakeWaterLevel(); // 수면 엑터 생성 함수 묶음
	CreateGimmickObject();

	wormLoading();

	KeySetting();
}

void PlayLevel::LevelUpdate()
{
	PJWLevelUpdate();

	if (true == GameEngineInput::GetInst().IsDown("Debug_Next"))
	{

		//GameEngineLevelManager::GetInst().ChangeLevel("LobbyLevel");
	}

	{
		// 디버깅 출력 내용입니다.
		GameEngineDebugExtension::PrintDebugWindowText("Resolution : ", GameEngineWindow::GetInst().GetSize().x, " X ", GameEngineWindow::GetInst().GetSize().y);
		GameEngineDebugExtension::PrintDebugWindowText("FPS : ", GameEngineTime::GetInst().GetFPS());
		GameEngineDebugExtension::PrintDebugWindowText("CamPos X : ", GetCamPos().ix(), ", CamPos Y : ", GetCamPos().iy());
		GameEngineDebugExtension::PrintDebugWindowText("Mouse X : ", GameEngineWindow::GetInst().GetMousePos().x, ", Mouse Y : ", GameEngineWindow::GetInst().GetMousePos().y);
		GameEngineDebugExtension::PrintDebugWindowText("Mouse+CamPos X : ", GameEngineWindow::GetInst().GetMousePos().x + GetCamPos().ix(), ", Mouse+CamPos Y : ", GameEngineWindow::GetInst().GetMousePos().y+ GetCamPos().iy());
		GameEngineDebugExtension::PrintDebugWindowText("Worm 1 Pos X : ", Controller_->GetWormList()[0]->GetPos().x, ", Pos Y : ", Controller_->GetWormList()[0]->GetPos().y);
		GameEngineDebugExtension::PrintDebugWindowText("Worm 2 Pos X : ", Controller_->GetWormList()[1]->GetPos().x, ", Pos Y : ", Controller_->GetWormList()[1]->GetPos().y);
		GameEngineDebugExtension::PrintDebugWindowText("Worm 3 Pos X : ", Controller_->GetWormList()[2]->GetPos().x, ", Pos Y : ", Controller_->GetWormList()[2]->GetPos().y);
		GameEngineDebugExtension::PrintDebugWindowText("Worm 4 Pos X : ", Controller_->GetWormList()[3]->GetPos().x, ", Pos Y : ", Controller_->GetWormList()[3]->GetPos().y);
		GameEngineDebugExtension::PrintDebugWindowText("Worm 5 Pos X : ", Controller_->GetWormList()[4]->GetPos().x, ", Pos Y : ", Controller_->GetWormList()[4]->GetPos().y);
		GameEngineDebugExtension::PrintDebugWindowText("Worm 6 Pos X : ", Controller_->GetWormList()[5]->GetPos().x, ", Pos Y : ", Controller_->GetWormList()[5]->GetPos().y);
//		GameEngineDebugExtension::PrintDebugWindowText("Worm 7 Pos X : ", Controller_->GetWormList()[6]->GetPos().x, ", Pos Y : ", Controller_->GetWormList()[6]->GetPos().y);
//		GameEngineDebugExtension::PrintDebugWindowText("Worm 8 Pos X : ", Controller_->GetWormList()[7]->GetPos().x, ", Pos Y : ", Controller_->GetWormList()[7]->GetPos().y);
		GameEngineDebugExtension::PrintDebugWindowText("Wind Direction : ", windController_->GetCurrentWindDir(), ", Wind Speed : ", windController_->GetCurrentWindSpeed());
		GameEngineDebugExtension::PrintDebugWindowText("Water Level : ", WaterLevel_->GetWaterLevel());
	}
	//디버그
	{
		if (true == GameEngineInput::GetInst().IsDown("DrumSpawn"))
		{
			CreateGimmickObject();
		}
	}
}

void PlayLevel::wormLoading()
{
	Controller_ = CreateActor<GameController>("GameController");


	float4 minMaxInfo = GlobalValue::MapMinMaxInfo[GlobalValue::CurPlayMap];


	for (size_t i = 0; i < 6; i++)
	{
		Controller_->CreateWorm(minMaxInfo.x, minMaxInfo.y);
	}

	MouseObject* MainMouse = CreateActor<MouseObject>("PlayLevelMouse");
	MainMouse->SetGameController(Controller_);

	// 플레이어별 UIController 생성
	Controller_->CreateWormUI();
	GameEngineTime::GetInst().TimeCheck();
}

void PlayLevel::CreateExplosion100(float4 Pos, int _Damage, bool _DamageAll)
{
	ExplosionSize100* actor = CreateActor<ExplosionSize100>
		(Pos);
	actor->SetRenderOrder((int)RenderOrder::Effect);
	actor->SetDamage(_Damage, _DamageAll);

	GroundUpdate100(Pos);
}

void PlayLevel::CreateExplosion75(float4 Pos, int _Damage, bool _DamageAll)
{
	ExplosionSize75* actor = CreateActor<ExplosionSize75>
		(Pos);
	actor->SetRenderOrder((int)RenderOrder::Effect);
	actor->SetDamage(_Damage, _DamageAll);

	GroundUpdate75(Pos);
}

void PlayLevel::CreateExplosion50(float4 Pos, int _Damage, bool _DamageAll)
{
	ExplosionSize50* actor = CreateActor<ExplosionSize50>
		(Pos);
	actor->SetRenderOrder((int)RenderOrder::Effect);
	actor->SetDamage(_Damage, _DamageAll);

	GroundUpdate50(Pos);
}

void PlayLevel::CreateExplosion25(float4 Pos, int _Damage, bool _DamageAll)
{
	ExplosionSize25* actor = CreateActor<ExplosionSize25>
		(Pos);
	actor->SetRenderOrder((int)RenderOrder::Effect);
	actor->SetDamage(_Damage, _DamageAll);

	GroundUpdate25(Pos);
}

void PlayLevel::GroundUpdate100(float4 _pos)
{
	float4 _Pos = float4(_pos.x - 56.f, _pos.y - 56.f);
	Train_->GroundUpdate100(_Pos);
}

void PlayLevel::GroundUpdate75(float4 _pos)
{
	float4 _Pos = float4(_pos.x - 43.5f, _pos.y - 43.5f);

	Train_->GroundUpdate75(_Pos);
}

void PlayLevel::GroundUpdate50(float4 _pos)
{
	float4 _Pos = float4(_pos.x - 31.f, _pos.y -31.f);
	Train_->GroundUpdate50(_Pos);
}

void PlayLevel::GroundUpdate25(float4 _pos)
{
	float4 _Pos = float4(_pos.x - 18.5f, _pos.y - 18.5f);
	Train_->GroundUpdate25(_Pos);
}

void PlayLevel::GroundUpdate13(float4 _pos)
{
	float4 _Pos = float4(_pos.x - 9.5f, _pos.y- 6.5f);
	Train_->GroundUpdate13(_Pos);
}

void PlayLevel::KeySetting()
{
	if (false == GameEngineInput::GetInst().IsKey("DrumExplode"))
	{
		GameEngineInput::GetInst().CreateKey("DrumExplode", 'G');
	}

	if (false == GameEngineInput::GetInst().IsKey("DrumSpawn"))
	{
		GameEngineInput::GetInst().CreateKey("DrumSpawn", 'H');
	}

	if (false == GameEngineInput::GetInst().IsKey("TestWaterLevelUp"))
	{
		GameEngineInput::GetInst().CreateKey("TestWaterLevelUp", 'Q');
	}

	if (false == GameEngineInput::GetInst().IsKey("TestWaterLevelDown"))
	{
		GameEngineInput::GetInst().CreateKey("TestWaterLevelDown", 'E');
	}
}

void PlayLevel::MakeWaterLevel(float _WaterLevel) // 맵 바닥의 수면 생성
{
	WaterLevel_ = CreateActor<WaterLevel>("WaterLevel"); // 모든 파도 actor 그룹화
	WaterLevel_->SetwaterLevel(_WaterLevel);

	WaterWave* WaterWaveactor = CreateActor<WaterWave>("WaterWave1");
	WaterWaveactor->SetRenderOrder((int)RenderOrder::WaterLevel_Back);
	WaterWaveactor->SetPos(float4(0.f, _WaterLevel, 0.f));
	WaterLevel_->Waterlist.push_back(WaterWaveactor);

	WaterWaveactor = CreateActor<WaterWave>("WaterWave2");
	WaterWaveactor->SetRenderOrder((int)RenderOrder::WaterLevel_Back);
	WaterWaveactor->SetPos(float4(0.f, _WaterLevel + 30.f, 0.f));
	WaterWaveactor->SetAnimationCurrentFrame(2);
	WaterLevel_->Waterlist.push_back(WaterWaveactor);

	WaterWaveactor = CreateActor<WaterWave>("WaterWave3");
	WaterWaveactor->SetRenderOrder((int)RenderOrder::WaterLevel_Front);
	WaterWaveactor->SetPos(float4(0.f, _WaterLevel + 60.f, 0.f));
	WaterWaveactor->SetAnimationCurrentFrame(4);
	WaterLevel_->Waterlist.push_back(WaterWaveactor);

	WaterWaveactor = CreateActor<WaterWave>("WaterWave4");
	WaterWaveactor->SetRenderOrder((int)RenderOrder::WaterLevel_Front);
	WaterWaveactor->SetPos(float4(0.f, _WaterLevel + 90.f, 0.f));
	WaterWaveactor->SetAnimationCurrentFrame(6);
	WaterLevel_->Waterlist.push_back(WaterWaveactor);

	WaterWaveactor = CreateActor<WaterWave>("WaterWave5");
	WaterWaveactor->SetRenderOrder((int)RenderOrder::WaterLevel_Front);
	WaterWaveactor->SetPos(float4(0.f, _WaterLevel + 120.f, 0.f));
	WaterWaveactor->SetAnimationCurrentFrame(8);
	WaterLevel_->Waterlist.push_back(WaterWaveactor);

	UnderWater* UnderWaterActor = CreateActor<UnderWater>("UnderWater");
	UnderWaterActor->SetPos(float4(0.f, _WaterLevel + 680.f, 0.f));
	UnderWaterActor->SetRenderOrder((int)RenderOrder::WaterLevel_Front);
	WaterLevel_->Waterlist.push_back(UnderWaterActor);

	WaterWaveactor = CreateActor<WaterWave>("WaterWave6");
	WaterWaveactor->SetRenderOrder((int)RenderOrder::WaterLevel_Back);
	WaterWaveactor->SetPos(float4(2560.f, _WaterLevel, 0.f));
	WaterLevel_->Waterlist.push_back(WaterWaveactor);

	WaterWaveactor = CreateActor<WaterWave>("WaterWave7");
	WaterWaveactor->SetRenderOrder((int)RenderOrder::WaterLevel_Back);
	WaterWaveactor->SetPos(float4(2560.f, _WaterLevel + 30.f, 0.f));
	WaterWaveactor->SetAnimationCurrentFrame(2);
	WaterLevel_->Waterlist.push_back(WaterWaveactor);

	WaterWaveactor = CreateActor<WaterWave>("WaterWave8");
	WaterWaveactor->SetRenderOrder((int)RenderOrder::WaterLevel_Front);
	WaterWaveactor->SetPos(float4(2560.f, _WaterLevel + 60.f, 0.f));
	WaterWaveactor->SetAnimationCurrentFrame(4);
	WaterLevel_->Waterlist.push_back(WaterWaveactor);

	WaterWaveactor = CreateActor<WaterWave>("WaterWave9");
	WaterWaveactor->SetRenderOrder((int)RenderOrder::WaterLevel_Front);
	WaterWaveactor->SetPos(float4(2560.f, _WaterLevel + 90.f, 0.f));
	WaterWaveactor->SetAnimationCurrentFrame(6);
	WaterLevel_->Waterlist.push_back(WaterWaveactor);

	WaterWaveactor = CreateActor<WaterWave>("WaterWave10");
	WaterWaveactor->SetRenderOrder((int)RenderOrder::WaterLevel_Front);
	WaterWaveactor->SetPos(float4(2560.f, _WaterLevel + 120.f, 0.f));
	WaterWaveactor->SetAnimationCurrentFrame(8);
	WaterLevel_->Waterlist.push_back(WaterWaveactor);

	UnderWaterActor = CreateActor<UnderWater>("UnderWater2");
	UnderWaterActor->SetPos(float4(2560.f, _WaterLevel + 680.f, 0.f));
	UnderWaterActor->SetRenderOrder((int)RenderOrder::WaterLevel_Front);
	WaterLevel_->Waterlist.push_back(UnderWaterActor);

}

void PlayLevel::CreateGimmickObject()
{
	DrumActor* DrumActor1 = CreateActor<DrumActor>(float4(1600.f,150.f));
	DrumActor1->SetRenderOrder((int)RenderOrder::Worm);
	//DrumActor1 ->SetPos(float4(2560.f, 1580, 0.f));
}

void PlayLevel::PJWLevelUpdate()
{
	if (true == GameEngineInput::GetInst().IsDown("Debug_Toggle"))
	{
		if (true == isDebugOn_)
		{
			GameEngineDebugExtension::DebugWindowClose();

			isDebugOn_ = false;
			return;
		}
		GameEngineDebugExtension::DebugWindowOpen({ 500, 500 }, { 0, 0 });
		isDebugOn_ = true;
		return;
	}

	if (false == loadingImage_->IsOn() && false == isFadeIn_)
	{
		fadeObject_->SetFadeOutSpeed(200.0f);
		fadeObject_->FadeOut();
		isFadeIn_ = true;
	}
}
