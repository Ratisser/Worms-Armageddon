#include "LobbyLevel.h"
#include "LobbyImage.h"
#include "LobbySelectMapImage.h"
#include "LobbyScatter.h"
#include "LobbyHost.h"
#include "ChattingInput.h"
#include "ChattingHistory.h"
#include "LobbyStartButton.h"
#include "LobbyExitButton.h"
#include "MouseObject.h"

// 팀생성 관련
#include "LobbyCreateTeam.h"

// 게임옵션관련
// 기본
#include "LobbyTernTimeSet.h"
#include "LobbyRoundTimeSet.h"
#include "LobbyWinsreQuiredSet.h"
#include "LobbyWormSelectSet.h"
#include "LobbyWormEnergySet.h"
#include "LobbyTeleportinSet.h"

// 상세
#include "GameOptionSet.h"

// 무기
#include "WeaponOptionSet.h"

#include <GameEngineInput.h>
#include <GameEngineLevelManager.h>
#include <GameEngineWindow.h>
#include <GameEngineImage.h>

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
	// 대기실화면 배경 및 맵선택 이미지
	Loading_SJH();
}

void LobbyLevel::LevelUpdate()
{

}

void LobbyLevel::Loading_SJH()
{
	// 로딩시에 로드한 모든 이미지파일의 이름을 체크하여 MapSel* 으로시작하는 이미지파일이름 모두 찾아서
	// LobbySelectMapImage 액터에 넘겨준다.
	std::vector<std::string> ImageNameList = GameEngineImage::GetInst().FindAllSpecKeyImage("LobbyMap_");
	int CurMapIndex = 0;
	for (size_t i = 0; i < ImageNameList.size(); ++i)
	{
		// 첫 맵이 LobbyMap_MapTrain 이므로 해당 인덱스를 찾는다.
		if (ImageNameList[i] == "LobbyMap_MapTrain")
		{
			CurMapIndex = static_cast<int>(i);
			break;
		}
	}

	// 맵선택 키 생성
	if (false == GameEngineInput::GetInst().IsKey("Lobby_MapSelect"))
	{
		GameEngineInput::GetInst().CreateKey("Lobby_MapSelect", VK_RBUTTON);
	}

	float4 HalfResoultion = GameEngineWindow::GetInst().GetSize().halffloat4();

	// 대기실 배경
	CreateActor<LobbyImage>();

	// 대기실오브젝트(바람액터)
	for (int i = 0; i < 39; i++)
	{
		LobbyScatter* newScatter = CreateActor<LobbyScatter>();
	}

	// 맵선택이미지
	LobbySelectMapImage* SelectMapImage = CreateActor<LobbySelectMapImage>();
	SelectMapImage->SetPos({ HalfResoultion.x + 100.f, 20.f });
	SelectMapImage->CreateSelMapImageNameList(ImageNameList);
	SelectMapImage->SetCurMapIndex(CurMapIndex);

	// 채팅기능
	CreateActor<ChattingHistory>(); // 채팅이력
	CreateActor<ChattingInput>(); // 채팅 입력

	// 옵션셋팅(게임옵션, 무기옵션)
	CreateActor<GameOptionSet>();
	CreateActor<WeaponOptionSet>();

	// 게임시작 및 종료 버튼
	CreateActor<LobbyStartButton>();
	CreateActor<LobbyExitButton>();

	// 호스트
	CreateActor<LobbyHost>();

	// 기본게임옵션
	CreateActor<LobbyTernTimeSet>();
	CreateActor<LobbyRoundTimeSet>();
	CreateActor<LobbyWinsreQuiredSet>();
	CreateActor<LobbyWormSelectSet>();
	CreateActor<LobbyWormEnergySet>();
	CreateActor<LobbyTeleportinSet>();

	// 팀 생성
	CreateActor<LobbyCreateTeam>();

	// 마우스
	CreateActor<MouseObject>();
}
