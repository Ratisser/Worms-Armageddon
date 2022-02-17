// 00AR38Start.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <GameEngineWindow.h>
#include <Windows.h>
#include <GameEngineDebugExtension.h>
#include <GameEngineLevelManager.h>
#include <GameEngineActor.h>

#include <TitleLevel.h>
#include <MenuSelectLevel.h>
#include <LobbyLevel.h>
#include <LoadingLevel.h>
#include <PlayLevel.h>
#include <EndingLevel.h>


#include <GameEngineMath.h>
#include <GameEngineInput.h>
#include <GameEngineSoundManager.h>
#include <GameEngineMath.h>
#include "AppFunc.h"

void UpdateFunc() 
{
	GameEngineDebugExtension::Update();
	GameEngineLevelManager::GetInst().Update();
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	// 디버깅 기본 기능 실행
	GameEngineDebugExtension::LeakCheckOn();

	GameEngineSoundManager::GetInstance().Initialize();
	// 윈도우 생성 및 기본 윈도우 창에서 게임을 돌릴 준비를 한다.
	GameEngineWindow::GetInst().CreateMainWindowClass(hInstance, "GameWindow");
	GameEngineWindow::GetInst().CreateMainWindow("MyWindow", { 1280, 720 }, {0, 0});
	GameEngineDebugExtension::DebugWindowOpen({ 500, 500 }, { 0, 0 });
	
	AppResourcesInit();

	// 각 씬을 생성하고 로딩을 완료한후
	// 최초 만들어질 씬을 지정한다.
	GameEngineLevelManager::GetInst().CreateLevel<TitleLevel>("TitleLevel");
	GameEngineLevelManager::GetInst().CreateLevel<MenuSelectLevel>("MenuSelectLevel");
	GameEngineLevelManager::GetInst().CreateLevel<LobbyLevel>("LobbyLevel");
	GameEngineLevelManager::GetInst().CreateLevel<PlayLevel>("PlayLevel");
	GameEngineLevelManager::GetInst().CreateLevel<EndingLevel>("EndingLevel");


	// 최초 씬 지정.
	GameEngineLevelManager::GetInst().ChangeLevel("LobbyLevel");

	GameEngineWindow::GetInst().Loop(UpdateFunc);

	AppRelease();
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
