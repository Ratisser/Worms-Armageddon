#include <GameEngineLevelManager.h>
#include <GameEngineInput.h>

#include "MapTrain.h"
#include "PlayLevel.h"
#include "Worm.h"


PlayLevel::PlayLevel() // default constructer ����Ʈ ������
{

}

PlayLevel::~PlayLevel() // default destructer ����Ʈ �Ҹ���
{

}

PlayLevel::PlayLevel(PlayLevel&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
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