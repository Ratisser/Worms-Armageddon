#include <GameEngineLevelManager.h>
#include <GameEngineLevel.h>
#include <GameEngineInput.h>
#include <GameEngineWindow.h>
#include <GameEngineDebugExtension.h>

#include "MapTrain.h"
#include "MapGround.h"
#include "PlayLevel.h"
#include "Worm.h"
#include "UIController.h"
#include "DrumActor.h"
#include "Bazooka.h"

#include "BottomHealthBar.h"
#include "BottomNameTag.h"
#include "BottomFlag.h"
#include "WindBarBlank.h"
#include "WindBar.h"
#include "WindBarHider.h"

#include "WaterWave.h"
#include "UnderWater.h"

#include "EffectActor.h"
#include "EffectBundleActor.h"

#include "Explosion.h"

#include "BackgroundScatter.h"
#include "Midground.h"
#include "WindController.h"

PlayLevel::PlayLevel() // default constructer 디폴트 생성자
	: Train_(nullptr),
	Ground_(nullptr),
	Worm_(nullptr),
	Bazooka_(nullptr),
	WaterLevel_(nullptr),
	IsCameraMove_(true),
	windController_(nullptr),
	CameraPos_(0.f, 0.f),
	isDebugOn_(true),
	Worm2P_(nullptr),
	Worm3P_(nullptr),
	Worm4P_(nullptr),
	Worm5P_(nullptr),
	Worm6P_(nullptr),
	Worm7P_(nullptr),
	Worm8P_(nullptr),
	randomGenerator_(),
	isWormLanded_(false)// default constructer 디폴트 생성자
	
{

}

PlayLevel::~PlayLevel() // default destructer 디폴트 소멸자
{

}

PlayLevel::PlayLevel(PlayLevel&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자	
	: Train_(nullptr),
	Ground_(nullptr),
	Worm_(nullptr),
	Bazooka_(nullptr),
	WaterLevel_(nullptr),
	IsCameraMove_(true)
	,windController_(nullptr),
	CameraPos_(0.f, 0.f),
	isDebugOn_(true),
	Worm2P_(nullptr),
	Worm3P_(nullptr),
	Worm4P_(nullptr),
	Worm5P_(nullptr),
	Worm6P_(nullptr),
	Worm7P_(nullptr),
	Worm8P_(nullptr),
	randomGenerator_(),
	isWormLanded_(false)// default RValue Copy constructer 디폴트 RValue 복사생성자
{

}

void PlayLevel::Loading()
{
	AJYLoading();

	if (false == GameEngineInput::GetInst().IsKey("Debug_Next"))
	{
		GameEngineInput::GetInst().CreateKey("Debug_Next", 'P');
	}

	Train_ = CreateActor<MapTrain>();

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

	Worm_ = CreateActor<Worm>();
	Worm2P_ = CreateActor<Worm>();
	Worm3P_ = CreateActor<Worm>();
	Worm4P_ = CreateActor<Worm>();
	Worm5P_ = CreateActor<Worm>();
	Worm6P_ = CreateActor<Worm>();
	Worm7P_ = CreateActor<Worm>();
	Worm8P_ = CreateActor<Worm>();

	{
		// 플레이화면 하단 체력바
		BottomNameTag* p1NameTag = CreateActor<BottomNameTag>();
		p1NameTag->SetPos({ 555, 700 });
		BottomFlag* p1Flag = CreateActor<BottomFlag>();
		p1Flag->SetPos({ 610, 700 });
		BottomHealthBar* p1Health = CreateActor<BottomHealthBar>();
		p1Health->SetPos({ 672, 700 });
		windController_ = CreateActor<WindController>();

	}
	for (int i = 0; i < 39; i++)
	{
		// 배경 바람에 흩날리는 엑터 생성(추후 자료구조로 관리 예정)
		BackgroundScatter* newScatter = CreateActor<BackgroundScatter>();
		newScatter->SetParent(windController_);
	}
	// 뒷배경 생성
	CreateActor<Midground>();
	// 바람 UI 바 생성
	CreateActor<WindBarBlank>();
	WindBar* windBar = CreateActor<WindBar>();
	windBar->SetParentController(windController_);
	WindBarHider* windBarHider = CreateActor<WindBarHider>();
	windBarHider->SetParentController(windController_);
	// UI관리자생성
	UIController* CurUIController = CreateActor<UIController>();
	CurUIController->SetCurPlayer(Worm_);
	std::vector<eItemList> ItemListTest;
	ItemListTest.resize(2);
	ItemListTest[0] = eItemList::WEAPON_BAZOOKA;
	ItemListTest[1] = eItemList::WEAPON_HOMINGMISSILE;
	CurUIController->CreateWeaponList(ItemListTest);									// 플레이어가 처음 가지고있는 아이템목록(최초지정)
	CurUIController->AddWeapon(eItemList::WEAPON_AIRSTRIKE);		// 플레이어가 기믹오브젝트 획득으로 인한 무기획득시 호출(새로운무기추가 또는 기존무기개수증가)
	//CurUIController->UseWeapon(eItemList::WEAPON_AIRSTRIKE);		// 플레이어가 무기사용했을대 호출(가지고있는 무기개수감수)

	MakeWaterLevel(); // 수면 엑터 생성 함수 묶음
	CreateGimmickObject();
	
	Testfunc(); // 테스트해볼 함수를 집어넣는 함수, 사용후 비워둘것

}

void PlayLevel::LevelUpdate()
{
	TestUpdate(); //디버그용 테스트 함수
	AJYLevelUpdate();
	PJWLevelUpdate();
	float Speed = 5.f;

	if (false == isWormLanded_)
	{	// 랜덤한 위치에 웜 떨구기
		RandomWormArrange(1000.0f, 2000.0f);
	}

	if (true == GameEngineInput::GetInst().IsDown("Debug_Next"))
	{
		GameEngineLevelManager::GetInst().ChangeLevel("LobbyLevel");
	}

	if (IsCameraMove_)
	{
		if (true == GameEngineInput::GetInst().IsPress("Up"))
		{
			GameEngineLevel::SetCamMove(float4::UP * Speed);
			CameraPos_ += float4::UP * Speed;
		}
		if (true == GameEngineInput::GetInst().IsPress("Down"))
		{
			GameEngineLevel::SetCamMove(float4::DOWN * Speed);
			CameraPos_ += float4::DOWN * Speed;
		}
		if (true == GameEngineInput::GetInst().IsPress("Left"))
		{
			GameEngineLevel::SetCamMove(float4::LEFT * Speed);
			CameraPos_ += float4::LEFT * Speed;
		}
		if (true == GameEngineInput::GetInst().IsPress("Right"))
		{
			GameEngineLevel::SetCamMove(float4::RIGHT * Speed);
			CameraPos_ += float4::RIGHT * Speed;
		}
	}

	{
		// 디버깅 출력 내용입니다.
		GameEngineDebugExtension::PrintDebugWindowText("Resolution : ", GameEngineWindow::GetInst().GetSize().x, " X ", GameEngineWindow::GetInst().GetSize().y);

		GameEngineDebugExtension::PrintDebugWindowText("CamPos X : ", GetCamPos().ix(), ", CamPos Y : ", GetCamPos().iy());
		GameEngineDebugExtension::PrintDebugWindowText("Mouse X : ", GameEngineWindow::GetInst().GetMousePos().x, ", Mouse Y : ", GameEngineWindow::GetInst().GetMousePos().y);
		GameEngineDebugExtension::PrintDebugWindowText("Worm 1 Pos X : ", Worm_->GetPos().x, ", Pos Y : ", Worm_->GetPos().y);
		GameEngineDebugExtension::PrintDebugWindowText("Worm 2 Pos X : ", "0", ", Pos Y : ", "0");
		GameEngineDebugExtension::PrintDebugWindowText("Worm 3 Pos X : ", "0", ", Pos Y : ", "0");
		GameEngineDebugExtension::PrintDebugWindowText("Worm 4 Pos X : ", "0", ", Pos Y : ", "0");
		GameEngineDebugExtension::PrintDebugWindowText("Wind Direction : ", windController_->GetCurrentWindDir(), ", Wind Speed : ", windController_->GetCurrentWindSpeed());
		GameEngineDebugExtension::PrintDebugWindowText("Water Level : ", WaterLevel_->GetWaterLevel());
	}

	

}

void PlayLevel::AJYLoading()
{
	//Bazooka_ = CreateActor<Bazooka>();
	Ground_ = CreateActor<MapGround>();

	if (false == GameEngineInput::GetInst().IsKey("Boom"))
	{
		GameEngineInput::GetInst().CreateKey("Boom", VK_LBUTTON);
	}

	if (false == GameEngineInput::GetInst().IsKey("FreeCameraOnOff"))
	{
		GameEngineInput::GetInst().CreateKey("FreeCameraOnOff", 0x31);
	}
}

void PlayLevel::AJYLevelUpdate()
{
	if (true == GameEngineInput::GetInst().IsDown("Boom"))
	{
		Bazooka_ = CreateActor<Bazooka>();
		float4 mousepos = GameEngineWindow::GetInst().GetMousePos() + CameraPos_;
		Bazooka_->SetPos(mousepos);
		//Train_->GroundUpdate();

		//테스트 삽입 이현

		//CreateExplosion();
	}

	if (true == GameEngineInput::GetInst().IsDown("FreeCameraOnOff"))
	{
		if (true == IsCameraMove_)
		{
			IsCameraMove_ = false;
		}	
		else
		{
			IsCameraMove_ = true;
		}
	}

	if (false == IsCameraMove_)
	{
		GameEngineLevel::SetCamPos(Worm_->GetPos() - GameEngineWindow::GetInst().GetSize().halffloat4());
	}
}

void PlayLevel::AJYGround(float4 _pos)
{
	Train_->GroundUpdate(_pos);
	Ground_->GroundUpdate(_pos);

	EffectBundle::Explosion::Size100* actor = CreateActor<EffectBundle::Explosion::Size100>
		(float4(_pos.x + 50.f, _pos.y + 50.f));
	actor->SetRenderOrder((int)RenderOrder::Effect);
}

void PlayLevel::MakeWaterLevel() // 맵 바닥의 수면 생성
{
	WaterLevel_ = CreateActor<WaterLevel>("WaterLevel"); // 모든 파도 actor 그룹화

	WaterWave* WaterWaveactor = CreateActor<WaterWave>("WaterWave1");
	WaterWaveactor->SetRenderOrder((int)RenderOrder::WaterLevel_Back);
	WaterWaveactor->SetPos(float4(0.f, 900, 0.f));
	WaterLevel_->Waterlist.push_back(WaterWaveactor);

	WaterWaveactor = CreateActor<WaterWave>("WaterWave2");
	WaterWaveactor->SetRenderOrder((int)RenderOrder::WaterLevel_Back);
	WaterWaveactor->SetPos(float4(0.f, 930, 0.f));
	WaterWaveactor->SetAnimationCurrentFrame(2);
	WaterLevel_->Waterlist.push_back(WaterWaveactor);

	WaterWaveactor = CreateActor<WaterWave>("WaterWave3");
	WaterWaveactor->SetRenderOrder((int)RenderOrder::WaterLevel_Front);
	WaterWaveactor->SetPos(float4(0.f, 960, 0.f));
	WaterWaveactor->SetAnimationCurrentFrame(4);
	WaterLevel_->Waterlist.push_back(WaterWaveactor);

	WaterWaveactor = CreateActor<WaterWave>("WaterWave4");
	WaterWaveactor->SetRenderOrder((int)RenderOrder::WaterLevel_Front);
	WaterWaveactor->SetPos(float4(0.f, 990, 0.f));
	WaterWaveactor->SetAnimationCurrentFrame(6);
	WaterLevel_->Waterlist.push_back(WaterWaveactor);

	WaterWaveactor = CreateActor<WaterWave>("WaterWave5");
	WaterWaveactor->SetRenderOrder((int)RenderOrder::WaterLevel_Front);
	WaterWaveactor->SetPos(float4(0.f, 1020, 0.f));
	WaterWaveactor->SetAnimationCurrentFrame(8);
	WaterLevel_->Waterlist.push_back(WaterWaveactor);

	UnderWater* UnderWaterActor = CreateActor<UnderWater>("UnderWater");
	UnderWaterActor->SetPos(float4(0.f, 1580,0.f));
	UnderWaterActor->SetRenderOrder((int)RenderOrder::WaterLevel_Front);
	WaterLevel_->Waterlist.push_back(UnderWaterActor);

	WaterWaveactor = CreateActor<WaterWave>("WaterWave6");
	WaterWaveactor->SetRenderOrder((int)RenderOrder::WaterLevel_Back);
	WaterWaveactor->SetPos(float4(2560.f, 900, 0.f));
	WaterLevel_->Waterlist.push_back(WaterWaveactor);

	WaterWaveactor = CreateActor<WaterWave>("WaterWave7");
	WaterWaveactor->SetRenderOrder((int)RenderOrder::WaterLevel_Back);
	WaterWaveactor->SetPos(float4(2560.f, 930, 0.f));
	WaterWaveactor->SetAnimationCurrentFrame(2);
	WaterLevel_->Waterlist.push_back(WaterWaveactor);

	WaterWaveactor = CreateActor<WaterWave>("WaterWave8");
	WaterWaveactor->SetRenderOrder((int)RenderOrder::WaterLevel_Front);
	WaterWaveactor->SetPos(float4(2560.f, 960, 0.f));
	WaterWaveactor->SetAnimationCurrentFrame(4);
	WaterLevel_->Waterlist.push_back(WaterWaveactor);

	WaterWaveactor = CreateActor<WaterWave>("WaterWave9");
	WaterWaveactor->SetRenderOrder((int)RenderOrder::WaterLevel_Front);
	WaterWaveactor->SetPos(float4(2560.f, 990, 0.f));
	WaterWaveactor->SetAnimationCurrentFrame(6);
	WaterLevel_->Waterlist.push_back(WaterWaveactor);

	WaterWaveactor = CreateActor<WaterWave>("WaterWave10");
	WaterWaveactor->SetRenderOrder((int)RenderOrder::WaterLevel_Front);
	WaterWaveactor->SetPos(float4(2560.f, 1020,0.f));
	WaterWaveactor->SetAnimationCurrentFrame(8);
	WaterLevel_->Waterlist.push_back(WaterWaveactor);

	UnderWaterActor = CreateActor<UnderWater>("UnderWater2");
	UnderWaterActor->SetPos(float4(2560.f, 1580, 0.f));
	UnderWaterActor->SetRenderOrder((int)RenderOrder::WaterLevel_Front);
	WaterLevel_->Waterlist.push_back(UnderWaterActor);

}

void PlayLevel::CreateGimmickObject()
{
	DrumActor* DrumActor1 = CreateActor<DrumActor>();

	//DrumActor1 ->SetPos(float4(2560.f, 1580, 0.f));

}

void PlayLevel::CreateExplosion()
{
	float4 mousepos = GameEngineWindow::GetInst().GetMousePos() + float4(1230.f, 280.f, 0.f, 0.f);
	EffectBundle::Explosion::Size100* actor =CreateActor<EffectBundle::Explosion::Size100>
		(mousepos);
	actor->SetRenderOrder((int)RenderOrder::Effect);
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
}

void PlayLevel::Testfunc() // 테스트해볼 함수를 집어넣는 함수, 사용후 비워둘것
{
	CreateExplosion();
}

void PlayLevel::TestUpdate()
{
}

void PlayLevel::RandomWormArrange(float _minX, float _maxX)
{
	if (false == isWormLanded_)
	{
		Worm_->SetPos({ randomGenerator_.RandomFloat(_minX, _maxX) , -1000.0f });
		Worm2P_->SetPos({ randomGenerator_.RandomFloat(_minX, _maxX) , -1000.0f });
		Worm3P_->SetPos({ randomGenerator_.RandomFloat(_minX, _maxX) , -1000.0f });
		Worm4P_->SetPos({ randomGenerator_.RandomFloat(_minX, _maxX) , -1000.0f });
		Worm5P_->SetPos({ randomGenerator_.RandomFloat(_minX, _maxX) , -1000.0f });
		Worm6P_->SetPos({ randomGenerator_.RandomFloat(_minX, _maxX) , -1000.0f });
		Worm7P_->SetPos({ randomGenerator_.RandomFloat(_minX, _maxX) , -1000.0f });
		Worm8P_->SetPos({ randomGenerator_.RandomFloat(_minX, _maxX) , -1000.0f });
		isWormLanded_ = true;
	}

}