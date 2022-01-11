#include <GameEngineLevelManager.h>
#include <GameEngineLevel.h>
#include <GameEngineInput.h>
#include <GameEngineWindow.h>

#include "MapTrain.h"
#include "PlayLevel.h"
#include "Worm.h"
#include "WeaponSheet.h"

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

	// 아이템창 생성
	float4 Resolution = GameEngineWindow::GetInst().GetSize();
	GameEngineActor* NewWeaponSheet = CreateActor<WeaponSheet>();
	NewWeaponSheet->SetPos({ Resolution.x  - 100.f, Resolution.y - 240.f, Resolution.z, Resolution.w});
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