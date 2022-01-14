#include "TitleLevel.h"
#include "TitleImage.h"
#include <GameEngineInput.h>
#include <GameEngineLevelManager.h>
TitleLevel::TitleLevel() // default constructer ����Ʈ ������
{

}

TitleLevel::~TitleLevel() // default destructer ����Ʈ �Ҹ���
{

}

TitleLevel::TitleLevel(TitleLevel&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
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