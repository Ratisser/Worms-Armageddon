#include <GameEngineInput.h>
#include <GameEngineLevelManager.h>
#include "LoadingLevel.h"
#include "LoadingImage.h"
LoadingLevel::LoadingLevel() // default constructer 디폴트 생성자
{

}

LoadingLevel::~LoadingLevel() // default destructer 디폴트 소멸자
{

}

LoadingLevel::LoadingLevel(LoadingLevel&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
{

}

void LoadingLevel::Loading()
{
	if (false == GameEngineInput::GetInst().IsKey("Debug_Next"))
	{
		GameEngineInput::GetInst().CreateKey("Debug_Next", 'P');
	}

	CreateActor<LoadingImage>();

}

void LoadingLevel::LevelUpdate()
{
	if (true == GameEngineInput::GetInst().IsDown("Debug_Next"))
	{
		GameEngineLevelManager::GetInst().ChangeLevel("PlayLevel");
	}
}