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

#include "BottomHealthBar.h"
#include "BottomNameTag.h"
#include "BottomFlag.h"

#include "WaterWave.h"
#include "UnderWater.h"


#include "BackgroundScatter.h"
#include "WindController.h"

PlayLevel::PlayLevel() // default constructer ����Ʈ ������
	: Train_(nullptr),
	Worm_(nullptr),
	WaterLevel_(nullptr),
	IsCameraMove_(true),
	windController_(nullptr)// default constructer ����Ʈ ������
{

}

PlayLevel::~PlayLevel() // default destructer ����Ʈ �Ҹ���
{

}

PlayLevel::PlayLevel(PlayLevel&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������	
	: Train_(nullptr),
	Worm_(nullptr),
	WaterLevel_(nullptr),
	IsCameraMove_(true)
	,windController_(nullptr)  // default RValue Copy constructer ����Ʈ RValue ���������
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
	// UI�����ڻ���
	CreateActor<UIController>();

	MakeWaterLevel(); // ���� ���� ���� �Լ� ����
	CreateGimmickObject();

}

void PlayLevel::LevelUpdate()
{
	AJYLevelUpdate();
	float Speed = 5.f;


	if (true == GameEngineInput::GetInst().IsDown("Debug_Next"))
	{
		GameEngineLevelManager::GetInst().ChangeLevel("LobbyLevel");
	}

	if (IsCameraMove_)
	{
		if (true == GameEngineInput::GetInst().IsPress("Up"))
		{
			GameEngineLevel::SetCamMove(float4::UP * Speed); 
		}
		if (true == GameEngineInput::GetInst().IsPress("Down"))
		{
			GameEngineLevel::SetCamMove(float4::DOWN * Speed);
		}
		if (true == GameEngineInput::GetInst().IsPress("Left"))
		{
			GameEngineLevel::SetCamMove(float4::LEFT * Speed);
		}
		if (true == GameEngineInput::GetInst().IsPress("Right"))
		{
			GameEngineLevel::SetCamMove(float4::RIGHT * Speed);
		}
	}

	{
		// ����� ��� �����Դϴ�.
		GameEngineDebugExtension::PrintDebugWindowText("CamPos X : ", GetCamPos().ix(), ", CamPos Y : ", GetCamPos().iy());
		GameEngineDebugExtension::PrintDebugWindowText("Mouse X : ", GameEngineWindow::GetInst().GetMousePos().x, ", Mouse Y : ", GameEngineWindow::GetInst().GetMousePos().y);
		GameEngineDebugExtension::PrintDebugWindowText("Worm 1 Pos X : ", Worm_->GetPos().x, ", Pos Y : ", Worm_->GetPos().y);
		GameEngineDebugExtension::PrintDebugWindowText("Worm 2 Pos X : ", "0", ", Pos Y : ", "0");
		GameEngineDebugExtension::PrintDebugWindowText("Worm 3 Pos X : ", "0", ", Pos Y : ", "0");
		GameEngineDebugExtension::PrintDebugWindowText("Worm 4 Pos X : ", "0", ", Pos Y : ", "0");
		GameEngineDebugExtension::PrintDebugWindowText("Wind Direction : ", windController_->GetCurrentWindDir(), ", Wind Speed : ", windController_->GetCurrentWindSpeed());
		GameEngineDebugExtension::PrintDebugWindowText("Water Level : ", ", NumberofTides : ", WaterLevel_->Waterlist.size());
	}

	

}

void PlayLevel::AJYLoading()
{
	CreateActor<MapGround>();

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
		Train_->GroundUpdate();
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

void PlayLevel::MakeWaterLevel() // �� �ٴ��� ���� ����
{
	WaterLevel_ = CreateActor<WaterLevel>("WaterLevel"); // ��� �ĵ� actor �׷�ȭ

	WaterWave* WaterWaveactor = CreateActor<WaterWave>("WaterWave1");
	WaterWaveactor->SetRenderOrder(1);
	WaterWaveactor->SetPos(float4(0.f, 900, 0.f));
	WaterLevel_->Waterlist.push_back(WaterWaveactor);

	WaterWaveactor = CreateActor<WaterWave>("WaterWave2");
	WaterWaveactor->SetRenderOrder(1);
	WaterWaveactor->SetPos(float4(0.f, 930, 0.f));
	WaterWaveactor->SetAnimationCurrentFrame(2);
	WaterLevel_->Waterlist.push_back(WaterWaveactor);

	WaterWaveactor = CreateActor<WaterWave>("WaterWave3");
	WaterWaveactor->SetRenderOrder(2);
	WaterWaveactor->SetPos(float4(0.f, 960, 0.f));
	WaterWaveactor->SetAnimationCurrentFrame(4);
	WaterLevel_->Waterlist.push_back(WaterWaveactor);


	WaterWaveactor = CreateActor<WaterWave>("WaterWave4");
	WaterWaveactor->SetRenderOrder(2);
	WaterWaveactor->SetPos(float4(0.f, 990, 0.f));
	WaterWaveactor->SetAnimationCurrentFrame(6);
	WaterLevel_->Waterlist.push_back(WaterWaveactor);

	WaterWaveactor = CreateActor<WaterWave>("WaterWave5");
	WaterWaveactor->SetRenderOrder(2);
	WaterWaveactor->SetPos(float4(0.f, 1020, 0.f));
	WaterWaveactor->SetAnimationCurrentFrame(8);
	WaterLevel_->Waterlist.push_back(WaterWaveactor);

	UnderWater* UnderWaterActor = CreateActor<UnderWater>("UnderWater");
	UnderWaterActor->SetPos(float4(0.f, 1580,0.f));
	WaterLevel_->Waterlist.push_back(UnderWaterActor);

	WaterWaveactor = CreateActor<WaterWave>("WaterWave6");
	WaterWaveactor->SetRenderOrder(1);
	WaterWaveactor->SetPos(float4(2560.f, 900, 0.f));
	WaterLevel_->Waterlist.push_back(WaterWaveactor);

	WaterWaveactor = CreateActor<WaterWave>("WaterWave7");
	WaterWaveactor->SetRenderOrder(1);
	WaterWaveactor->SetPos(float4(2560.f, 930, 0.f));
	WaterWaveactor->SetAnimationCurrentFrame(2);
	WaterLevel_->Waterlist.push_back(WaterWaveactor);

	WaterWaveactor = CreateActor<WaterWave>("WaterWave8");
	WaterWaveactor->SetRenderOrder(2);
	WaterWaveactor->SetPos(float4(2560.f, 960, 0.f));
	WaterWaveactor->SetAnimationCurrentFrame(4);
	WaterLevel_->Waterlist.push_back(WaterWaveactor);

	WaterWaveactor = CreateActor<WaterWave>("WaterWave9");
	WaterWaveactor->SetRenderOrder(2);
	WaterWaveactor->SetPos(float4(2560.f, 990, 0.f));
	WaterWaveactor->SetAnimationCurrentFrame(6);
	WaterLevel_->Waterlist.push_back(WaterWaveactor);

	WaterWaveactor = CreateActor<WaterWave>("WaterWave10");
	WaterWaveactor->SetRenderOrder(2);
	WaterWaveactor->SetPos(float4(2560.f, 1020,0.f));
	WaterWaveactor->SetAnimationCurrentFrame(8);
	WaterLevel_->Waterlist.push_back(WaterWaveactor);

	UnderWaterActor = CreateActor<UnderWater>("UnderWater2");
	UnderWaterActor->SetPos(float4(2560.f, 1580, 0.f));
	WaterLevel_->Waterlist.push_back(UnderWaterActor);

}

void PlayLevel::CreateGimmickObject()
{
	DrumActor* DrumActor1 = CreateActor<DrumActor>();

	//DrumActor1 ->SetPos(float4(2560.f, 1580, 0.f));

}