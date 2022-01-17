#include "LobbyLevel.h"
#include "LobbyImage.h"
#include "LobbySelectMapImage.h"
#include "WindController.h"
#include "BackgroundScatter.h"
#include "MouseObject.h"

#include <GameEngineInput.h>
#include <GameEngineLevelManager.h>
#include <GameEngineWindow.h>
#include <GameEngineImage.h>

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

	// ����ȭ�� ��� �� �ʼ��� �̹���
	Loading_SJH();

}

void LobbyLevel::LevelUpdate()
{
	if (true == GameEngineInput::GetInst().IsDown("Debug_Next"))
	{
		GameEngineLevelManager::GetInst().ChangeLevel("LoadingLevel");
	}
}

void LobbyLevel::Loading_SJH()
{
	// �ε��ÿ� �ε��� ��� �̹��������� �̸��� üũ�Ͽ� MapSel* ���ν����ϴ� �̹��������̸� ��� ã�Ƽ�
	// LobbySelectMapImage ���Ϳ� �Ѱ��ش�.
	std::vector<std::string> ImageNameList = GameEngineImage::GetInst().FindAllSpecKeyImage("LobbyMap_");
	int CurMapIndex = 0;
	for (size_t i = 0; i < ImageNameList.size(); ++i)
	{
		// ù ���� LobbyMap_MapTrain �̹Ƿ� �ش� �ε����� ã�´�.
		if (ImageNameList[i] == "LobbyMap_MapTrain")
		{
			CurMapIndex = i;
			break;
		}
	}

	// �ʼ��� Ű ����
	if (false == GameEngineInput::GetInst().IsKey("Lobby_MapSelect"))
	{
		GameEngineInput::GetInst().CreateKey("Lobby_MapSelect", VK_RBUTTON);
	}

	float4 HalfResoultion = GameEngineWindow::GetInst().GetSize().halffloat4();

	// ���� ���
	CreateActor<LobbyImage>();

	// ���ǿ�����Ʈ(�ٶ�����)
	WindController* windController_ = CreateActor<WindController>();
	for (int i = 0; i < 39; i++)
	{
		// ��� �ٶ��� �𳯸��� ���� ����(���� �ڷᱸ���� ���� ����)
		BackgroundScatter* newScatter = CreateActor<BackgroundScatter>();
		newScatter->SetParent(windController_);
	}

	// �ʼ����̹���
	LobbySelectMapImage* SelectMapImage = CreateActor<LobbySelectMapImage>();
	SelectMapImage->SetPos({ HalfResoultion.x + 100.f, 20.f });
	SelectMapImage->CreateSelMapImageNameList(ImageNameList);
	SelectMapImage->SetCurMapIndex(CurMapIndex);

	// ���콺
	CreateActor<MouseObject>();
}
