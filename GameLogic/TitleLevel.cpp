#include "TitleLevel.h"
#include "TitleImage.h"
#include <GameEngineInput.h>
#include <GameEngineLevelManager.h>
TitleLevel::TitleLevel() // default constructer 디폴트 생성자
{

}

TitleLevel::~TitleLevel() // default destructer 디폴트 소멸자
{

}

TitleLevel::TitleLevel(TitleLevel&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
{

}

void TitleLevel::Loading()
{
	if (false == GameEngineInput::GetInst().IsKey("Debug_Next"))
	{
		GameEngineInput::GetInst().CreateKey("Debug_Next", 'P');
		GameEngineInput::GetInst().CreateKey("Debug_Toggle", VK_TAB);
	}

	CreateActor<TitleImage>();

}

void TitleLevel::LevelUpdate()
{
	if (true == GameEngineInput::GetInst().IsDown("Debug_Next"))
	{
		GameEngineLevelManager::GetInst().ChangeLevel("LobbyLevel");
	}
}