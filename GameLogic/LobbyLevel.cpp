#include "LobbyImage.h"
#include "LobbyLevel.h"
#include <GameEngineInput.h>
#include <GameEngineLevelManager.h>
LobbyLevel::LobbyLevel() // default constructer 디폴트 생성자
{

}

LobbyLevel::~LobbyLevel() // default destructer 디폴트 소멸자
{

}

LobbyLevel::LobbyLevel(LobbyLevel&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
{

}


void LobbyLevel::Loading()
{
	if (false == GameEngineInput::GetInst().IsKey("Debug_Next"))
	{
		GameEngineInput::GetInst().CreateKey("Debug_Next", 'P');
	}

	CreateActor<LobbyImage>();

}

void LobbyLevel::LevelUpdate()
{
	if (true == GameEngineInput::GetInst().IsDown("Debug_Next"))
	{
		GameEngineLevelManager::GetInst().ChangeLevel("PlayLevel");
	}
}