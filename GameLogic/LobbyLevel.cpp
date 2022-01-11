#include "LobbyImage.h"
#include "LobbyLevel.h"
#include <GameEngineInput.h>
#include <GameEngineLevelManager.h>
LobbyLevel::LobbyLevel() // default constructer ����Ʈ ������
{

}

LobbyLevel::~LobbyLevel() // default destructer ����Ʈ �Ҹ���
{

}

LobbyLevel::LobbyLevel(LobbyLevel&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
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