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
	// ��ư ������ ����

	// ��ư �浹ü ����

	// ��ư Text ����


	// �������� Ű���(�ӽ�)
	// ���� ��ư ������ ��ư Ŭ���� ������ȯ���� ����
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

		// ĳ�� �ݳ� �� Flag ����
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

