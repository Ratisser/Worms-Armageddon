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
#include "FadeObject.h"

FadeObject* PlayLevel::fadeObject_ = nullptr;

PlayLevel::PlayLevel() // default constructer ����Ʈ ������
	: Train_(nullptr),
	Ground_(nullptr),
	// Worm_(nullptr),
	Bazooka_(nullptr),
	WaterLevel_(nullptr),
	IsCameraMove_(true),
	windController_(nullptr),
	CameraPos_(0.f, 0.f),
	FocusWormNumber_(8),
	isDebugOn_(true),
	randomGenerator_(),
	isWormLanded_(false),// default constructer ����Ʈ ������
	fadeInterTime_(0.0f),
	isFadeIn_(false)
	
{
	for (size_t i = 0; i < 8; i++)
	{
		Worm_[i] = nullptr;
	}
}

PlayLevel::~PlayLevel() // default destructer ����Ʈ �Ҹ���
{

}

PlayLevel::PlayLevel(PlayLevel&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������	
	: Train_(nullptr),
	Ground_(nullptr),
	// Worm_(nullptr),
	Bazooka_(nullptr),
	WaterLevel_(nullptr),
	IsCameraMove_(true)
	,windController_(nullptr),
	CameraPos_(0.f, 0.f),
	isDebugOn_(true),
	randomGenerator_(),
	isWormLanded_(false),
	fadeInterTime_(0.0f),
	isFadeIn_(false) // default RValue Copy constructer ����Ʈ RValue ���������
{
	for (size_t i = 0; i < 8; i++)
	{
		Worm_[i] = nullptr;
	}
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

	//Worm_ = CreateActor<Worm>();

	{
		// �÷���ȭ�� �ϴ� ü�¹�
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
		// ��� �ٶ��� �𳯸��� ���� ����(���� �ڷᱸ���� ���� ����)
		BackgroundScatter* newScatter = CreateActor<BackgroundScatter>();
		newScatter->SetParent(windController_);
	}
	// �޹�� ����
	CreateActor<Midground>();
	// �ٶ� UI �� ����
	CreateActor<WindBarBlank>();
	WindBar* windBar = CreateActor<WindBar>();
	windBar->SetParentController(windController_);
	WindBarHider* windBarHider = CreateActor<WindBarHider>();
	windBarHider->SetParentController(windController_);
	// UI�����ڻ���
	UIController* CurUIController = CreateActor<UIController>();
	CurUIController->SetCurPlayer(Worm_[0]);
	std::vector<eItemList> ItemListTest;
	ItemListTest.resize(2);
	ItemListTest[0] = eItemList::WEAPON_BAZOOKA;
	ItemListTest[1] = eItemList::WEAPON_HOMINGMISSILE;
	CurUIController->CreateWeaponList(ItemListTest);									// �÷��̾ ó�� �������ִ� �����۸��(��������)
	CurUIController->AddWeapon(eItemList::WEAPON_AIRSTRIKE);		// �÷��̾ ��Ϳ�����Ʈ ȹ������ ���� ����ȹ��� ȣ��(���ο���߰� �Ǵ� �������ⰳ������)
	//CurUIController->UseWeapon(eItemList::WEAPON_AIRSTRIKE);		// �÷��̾ ������������ ȣ��(�������ִ� ���ⰳ������)

	MakeWaterLevel(); // ���� ���� ���� �Լ� ����
	CreateGimmickObject();
}

void PlayLevel::LevelUpdate()
{
	AJYLevelUpdate();
	PJWLevelUpdate();
	float Speed = 5.f;

	if (false == isWormLanded_)
	{	// ������ ��ġ�� �� ������ (900~3300 Train �� ���� �ּ�~�ִ� �����Դϴ�.)
		RandomWormArrange(900.0f, 3300.0f);
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
		// ����� ��� �����Դϴ�.
		GameEngineDebugExtension::PrintDebugWindowText("Resolution : ", GameEngineWindow::GetInst().GetSize().x, " X ", GameEngineWindow::GetInst().GetSize().y);

		GameEngineDebugExtension::PrintDebugWindowText("FPS : ", GameEngineTime::GetInst().GetFPS());
		GameEngineDebugExtension::PrintDebugWindowText("CamPos X : ", GetCamPos().ix(), ", CamPos Y : ", GetCamPos().iy());
		GameEngineDebugExtension::PrintDebugWindowText("Mouse X : ", GameEngineWindow::GetInst().GetMousePos().x, ", Mouse Y : ", GameEngineWindow::GetInst().GetMousePos().y);
		GameEngineDebugExtension::PrintDebugWindowText("Worm 1 Pos X : ", Worm_[0]->GetPos().x, ", Pos Y : ", Worm_[0]->GetPos().y);
		GameEngineDebugExtension::PrintDebugWindowText("Worm 2 Pos X : ", Worm_[1]->GetPos().x, ", Pos Y : ", Worm_[1]->GetPos().y);
		GameEngineDebugExtension::PrintDebugWindowText("Worm 3 Pos X : ", Worm_[2]->GetPos().x, ", Pos Y : ", Worm_[2]->GetPos().y);
		GameEngineDebugExtension::PrintDebugWindowText("Worm 4 Pos X : ", Worm_[3]->GetPos().x, ", Pos Y : ", Worm_[3]->GetPos().y);
		GameEngineDebugExtension::PrintDebugWindowText("Worm 4 Pos X : ", Worm_[4]->GetPos().x, ", Pos Y : ", Worm_[4]->GetPos().y);
		GameEngineDebugExtension::PrintDebugWindowText("Worm 4 Pos X : ", Worm_[5]->GetPos().x, ", Pos Y : ", Worm_[5]->GetPos().y);
		GameEngineDebugExtension::PrintDebugWindowText("Worm 4 Pos X : ", Worm_[6]->GetPos().x, ", Pos Y : ", Worm_[6]->GetPos().y);
		GameEngineDebugExtension::PrintDebugWindowText("Worm 4 Pos X : ", Worm_[7]->GetPos().x, ", Pos Y : ", Worm_[7]->GetPos().y);
		GameEngineDebugExtension::PrintDebugWindowText("Wind Direction : ", windController_->GetCurrentWindDir(), ", Wind Speed : ", windController_->GetCurrentWindSpeed());
		GameEngineDebugExtension::PrintDebugWindowText("Water Level : ", WaterLevel_->GetWaterLevel());
	}

	

}

void PlayLevel::LevelUpdateBefore()
{
}

void PlayLevel::AJYLoading()
{
	for (size_t i = 0; i < 8; i++)
	{
		Worm_[i] = CreateActor<Worm>();;
	}

	//Bazooka_ = CreateActor<Bazooka>();
	//Ground_ = CreateActor<MapGround>();

	if (false == GameEngineInput::GetInst().IsKey("Boom"))
	{
		GameEngineInput::GetInst().CreateKey("Boom", VK_LBUTTON);
	}

	if (false == GameEngineInput::GetInst().IsKey("CameraFocus"))
	{
		GameEngineInput::GetInst().CreateKey("CameraFocus", 0x31);
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
	}

	if (true == GameEngineInput::GetInst().IsDown("CameraFocus"))
	{
		++FocusWormNumber_;

		if (true == IsCameraMove_)
		{
			for (int i = 0; i < 8; i++)
			{
				Worm_[i]->SetFocus(false);
			}

			FocusWormNumber_ = 0;
			IsCameraMove_ = false;
		}

		if (FocusWormNumber_ >= 8)
		{
			for (int i = 0; i < 8; i++)
			{
				Worm_[i]->SetFocus(false);
			}

			IsCameraMove_ = true;
		}
	}

	if (false == IsCameraMove_)
	{
		GameEngineLevel::SetCamPos(Worm_[FocusWormNumber_]->GetPos() - GameEngineWindow::GetInst().GetSize().halffloat4());

		for (int i = 0; i < 8; i++)
		{
			if (i == FocusWormNumber_)
			{
				Worm_[FocusWormNumber_]->SetFocus(true);
			}
			else
			{
				Worm_[i]->SetFocus(false);
			}
		}
	}
}

void PlayLevel::AJYGround(float4 _pos)
{
	Train_->GroundUpdate(_pos);
	Ground_->GroundUpdate(_pos);

	CreateExplosion100(_pos);
}

void PlayLevel::CreateExplosion100(float4 Pos)
{
	float4 _Pos = float4(Pos.x + 50.f, Pos.y + 50.f);

	EffectBundle::Explosion::Size100* actor = CreateActor<EffectBundle::Explosion::Size100>
		(_Pos);
	actor->SetRenderOrder((int)RenderOrder::Effect);
}

void PlayLevel::CreateExplosion75(float4 Pos)
{
	float4 _Pos = float4(Pos.x + 37.5f, Pos.y + 37.5f);

	EffectBundle::Explosion::Size75* actor = CreateActor<EffectBundle::Explosion::Size75>
		(_Pos);
	actor->SetRenderOrder((int)RenderOrder::Effect);
}

void PlayLevel::CreateExplosion50(float4 Pos)
{
	float4 _Pos = float4(Pos.x + 25.f, Pos.y + 25.f);

	EffectBundle::Explosion::Size50* actor = CreateActor<EffectBundle::Explosion::Size50>
		(_Pos);
	actor->SetRenderOrder((int)RenderOrder::Effect);
}

void PlayLevel::CreateExplosion25(float4 Pos)
{
	float4 _Pos = float4(Pos.x + 12.5f, Pos.y + 12.5f);

	EffectBundle::Explosion::Size25* actor = CreateActor<EffectBundle::Explosion::Size25>
		(_Pos);
	actor->SetRenderOrder((int)RenderOrder::Effect);
}

void PlayLevel::MakeWaterLevel(float _WaterLevel) // �� �ٴ��� ���� ����
{
	WaterLevel_ = CreateActor<WaterLevel>("WaterLevel"); // ��� �ĵ� actor �׷�ȭ
	WaterLevel_->SetwaterLevel(_WaterLevel);

	WaterWave* WaterWaveactor = CreateActor<WaterWave>("WaterWave1");
	WaterWaveactor->SetRenderOrder((int)RenderOrder::WaterLevel_Back);
	WaterWaveactor->SetPos(float4(0.f, _WaterLevel, 0.f));
	WaterLevel_->Waterlist.push_back(WaterWaveactor);

	WaterWaveactor = CreateActor<WaterWave>("WaterWave2");
	WaterWaveactor->SetRenderOrder((int)RenderOrder::WaterLevel_Back);
	WaterWaveactor->SetPos(float4(0.f, _WaterLevel+30.f, 0.f));
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
	UnderWaterActor->SetPos(float4(0.f, _WaterLevel + 680.f,0.f));
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
	WaterWaveactor->SetPos(float4(2560.f, _WaterLevel + 120.f,0.f));
	WaterWaveactor->SetAnimationCurrentFrame(8);
	WaterLevel_->Waterlist.push_back(WaterWaveactor);

	UnderWaterActor = CreateActor<UnderWater>("UnderWater2");
	UnderWaterActor->SetPos(float4(2560.f, _WaterLevel + 680.f, 0.f));
	UnderWaterActor->SetRenderOrder((int)RenderOrder::WaterLevel_Front);
	WaterLevel_->Waterlist.push_back(UnderWaterActor);

}

void PlayLevel::CreateGimmickObject()
{
	DrumActor* DrumActor1 = CreateActor<DrumActor>();

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
}

void PlayLevel::RandomWormArrange(float _minX, float _maxX)
{
	// ���� ���� ������ �ʰ� ���õ� ���� �� �� x�� ��ǥ ���� �� �ּ���.
	if (false == isWormLanded_)
	{
		for (size_t i = 0; i < 8; i++)
		{
			Worm_[i]->SetPos({ randomGenerator_.RandomFloat(_minX, _maxX) , -500.0f });
		}
		isWormLanded_ = true;
	}
	
}