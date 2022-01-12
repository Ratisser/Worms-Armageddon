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



		ResourceInitPJW();
		CharactorImageInit();
		UIImageInit();
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


void ResourceInitPJW()
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

	if (false == Dir.MoveChild("\\Misc\\"))
	{
		GameEngineDebug::AssertFalse();
		return;
	}

	GameEngineImage::GetInst().LoadGameImage("ScatterStar", Dir.PathToPlusFileName("ScatterStar.bmp"));

	Dir.MoveParent("Image");

	if (false == Dir.MoveChild("\\UI\\HPbar\\"))
	{
		GameEngineDebug::AssertFalse();
		return;
	}
	GameEngineImage::GetInst().LoadGameImage("HPbar", Dir.PathToPlusFileName("HPbar.bmp"));
	GameEngineImage::GetInst().LoadGameImage("BottomNameTag", Dir.PathToPlusFileName("BottomNameTag.bmp"));
	GameEngineImage::GetInst().LoadGameImage("BottomFlagRUS", Dir.PathToPlusFileName("BottomFlagRUS.bmp"));
	GameEngineImage::GetInst().LoadGameImage("BottomHPbarR", Dir.PathToPlusFileName("BottomHPbarR.bmp"));

}

void UIImageInit()
{
	GameEngineDirectroy Dir = GameEngineDirectroy();
	Dir.MoveParent("Worms-Armageddon");

	if (false == Dir.MoveChild("\\Resources\\Image\\UI\\"))
	{
		GameEngineDebug::AssertFalse();
		return;
	}

	GameEngineImageFile* loadingImage = GameEngineImage::GetInst().LoadGameImage("WeaponSheet", Dir.PathToPlusFileName("WeaponSheet_Temp.bmp"));
}

void CharactorImageInit()
{
	GameEngineDirectroy dir = GameEngineDirectroy();
	dir.MoveParent("Worms-Armageddon");
	dir.MoveChild("\\Resources\\Image\\Worms");

	GameEngineImageFile* image = nullptr; 
	image = RS::LoadImageFromFile(dir.PathToPlusFileName("walkLeft.bmp"));
	image->Cut({ 60, 60 });

	image = RS::LoadImageFromFile(dir.PathToPlusFileName("walkRight.bmp"));
	image->Cut({ 60, 60 });

	image = RS::LoadImageFromFile(dir.PathToPlusFileName("jumpReadyLeft.bmp"));
	image->Cut({ 60, 60 });

	image = RS::LoadImageFromFile(dir.PathToPlusFileName("jumpReadyRight.bmp"));
	image->Cut({ 60, 60 });

	image = RS::LoadImageFromFile(dir.PathToPlusFileName("flyUpLeft.bmp"));
	image->Cut({ 60, 60 });

	image = RS::LoadImageFromFile(dir.PathToPlusFileName("flyUpRight.bmp"));
	image->Cut({ 60, 60 });

	image = RS::LoadImageFromFile(dir.PathToPlusFileName("flyDownLeft.bmp"));
	image->Cut({ 60, 60 });

	image = RS::LoadImageFromFile(dir.PathToPlusFileName("flyDownRight.bmp"));
	image->Cut({ 60, 60 });

	image = RS::LoadImageFromFile(dir.PathToPlusFileName("flyLinkLeft.bmp"));
	image->Cut({ 60, 60 });

	image = RS::LoadImageFromFile(dir.PathToPlusFileName("flyLinkRight.bmp"));
	image->Cut({ 60, 60 });

	image = RS::LoadImageFromFile(dir.PathToPlusFileName("idleLeft.bmp"));
	image->Cut({ 60, 60 });

	image = RS::LoadImageFromFile(dir.PathToPlusFileName("idleRight.bmp"));
	image->Cut({ 60, 60 });
}

GameEngineImageFile* RS::LoadImageFromFile(const std::string& _path)
{
	size_t fileNameStartIndex = _path.rfind("\\") + 1;
	std::string fileName = _path.substr(fileNameStartIndex, _path.size() - fileNameStartIndex);

	return GameEngineImage::GetInst().LoadGameImage(fileName, _path);
}
