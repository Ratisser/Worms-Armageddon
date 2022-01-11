#include <GameEngineLevelManager.h>
#include <GameEngineInput.h>

#include "MapTrain.h"
#include "PlayLevel.h"
#include "Worm.h"


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
	CreateActor<Worm>();
}

void PlayLevel::LevelUpdate()
{
	if (true == GameEngineInput::GetInst().IsDown("Debug_Next"))
	{
		GameEngineLevelManager::GetInst().ChangeLevel("LobbyLevel");
	}
}