#include "LobbyStartButton.h"

#include <GameEngineInput.h>
#include <GameEngineWindow.h>
#include <GameEngineLevelManager.h>

LobbyStartButton::LobbyStartButton() :
	mainrenderer_(nullptr),
	maincollision_(nullptr)
{

}

LobbyStartButton::~LobbyStartButton()
{

}

LobbyStartButton::LobbyStartButton(LobbyStartButton&& _other) noexcept :
	mainrenderer_(_other.mainrenderer_),
	maincollision_(_other.maincollision_)
{

}

void LobbyStartButton::Start()
{
	// 버튼 렌더러 생성

	// 버튼 충돌체 생성

	// 버튼 Text 생성


	// 레벨변경 키등록(임시)
	// 추후 버튼 구현후 버튼 클릭시 레벨전환으로 변경
	if (false == GameEngineInput::GetInst().IsKey("Debug_Next"))
	{
		GameEngineInput::GetInst().CreateKey("Debug_Next", 'P');
	}
}

void LobbyStartButton::UpdateBefore()
{
}

void LobbyStartButton::Update()
{
	if (true == GameEngineInput::GetInst().IsDown("Debug_Next"))
	{
		GameEngineLevelManager::GetInst().ChangeLevel("LoadingLevel", true);

		// 캐럿 반납 및 Flag 해제
		GameEngineWindow::caretshow_ = false;
		SetCaretBlinkTime(500);
		HideCaret(GameEngineWindow::GetInst().GetMainWindowHandle());
		DestroyCaret();
	}
}

void LobbyStartButton::UpdateAfter()
{
}

void LobbyStartButton::Render()
{
}

