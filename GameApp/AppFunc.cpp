#include "AppFunc.h"
#include <GameEngineLevelManager.h>
#include <GameEngineTime.h>
#include <GameEngineImage.h>
#include <GameEngineWindow.h>
#include <GameEngineInput.h>
#include <GameEngineSound.h>
#include <GameEngineDirectroy.h>
#include <GameEngineFile.h>
#include <GameEngineImageFile.h>
#include <GameEngineDebugExtension.h>
#include <iostream>
#include <map>
#include <list>
#include <vector>

void AppResourcesInit() 
{
	// 이미지 로드
	{
		GameEngineDirectroy Dir = GameEngineDirectroy();
		Dir.MoveParent("Worms-Armageddon");

		if (false == Dir.MoveChild("\\Resources\\Image\\"))
		{
			GameEngineDebug::AssertFalse();
			return;
		}

		// 절대 경로
		GameEngineImage::GetInst().LoadGameImage("TitleImage", Dir.PathToPlusFileName("TitleImage.bmp"));
		GameEngineImage::GetInst().LoadGameImage("LobbyImage", Dir.PathToPlusFileName("LobbyImage.bmp"));
		GameEngineImage::GetInst().LoadGameImage("MapTrain", Dir.PathToPlusFileName("MapTrain.bmp"));
		LoadingImageInit();

	}

	// 사운드 로드
	{
		//GameEngineDirectroy Dir = GameEngineDirectroy();
		//Dir.MoveParent("API38");
		//
		//if (false == Dir.MoveChild("\\Resources\\Sound\\"))
		//{
		//	GameEngineDebug::AssertFalse();
		//	return;
		//}
		//
		//GameEngineSound::GetInst().LoadSound("test.mp3", Dir.PathToPlusFileName("test.mp3"));

	}
}

void AppRelease() 
{
	GameEngineDebugExtension::Release();
	GameEngineLevelManager::Destroy();


	GameEngineImage::Destroy();
	GameEngineSound::Destroy();
	GameEngineInput::Destroy();
	GameEngineWindow::Destroy();
	GameEngineTime::Destroy();
}


void LoadingImageInit()
{
	GameEngineDirectroy Dir = GameEngineDirectroy();
	Dir.MoveParent("Worms-Armageddon");

	if (false == Dir.MoveChild("\\Resources\\Image\\"))
	{
		GameEngineDebug::AssertFalse();
		return;
	}
	GameEngineImageFile* loadingImage = GameEngineImage::GetInst().LoadGameImage("LoadingSprites", Dir.PathToPlusFileName("LoadingSprites.bmp"));
	loadingImage->Cut({ 160,160 });
}