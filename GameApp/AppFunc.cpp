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

		GameEngineImage::GetInst().LoadGameImage("Ground", Dir.PathToPlusFileName("Ground.bmp"));
		GameEngineImage::GetInst().LoadGameImage("Boom", Dir.PathToPlusFileName("Boom.bmp"));

		ResourceInitPJW();
		CharactorImageInit();
		UIImageInit();
		MapWaterImageInit();
		GimmickObjectImageInit();
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
	if (false == Dir.MoveChild("\\Resources\\Image\\UI"))
	{
		GameEngineDebug::AssertFalse();
		return;
	}

	GameEngineImage::GetInst().LoadGameImage("WeaponSheet", Dir.PathToPlusFileName("WeaponSheet_Temp.bmp"));
	GameEngineImage::GetInst().LoadGameImage("Cursor", Dir.PathToPlusFileName("Cursor.bmp"));

	Dir.MoveParent("Worms-Armageddon");
	if (false == Dir.MoveChild("\\Resources\\Image\\UI\\Weapon Icons"))
	{
		GameEngineDebug::AssertFalse();
		return;
	}

	GameEngineImage::GetInst().LoadGameImage("bazookar", Dir.PathToPlusFileName("bazooka.bmp"));
	GameEngineImage::GetInst().LoadGameImage("hmissile", Dir.PathToPlusFileName("hmissile.bmp"));
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

void MapWaterImageInit() // 바닥 수면 이미지 로드에 사용
{
	GameEngineDirectroy Dir = GameEngineDirectroy();
	Dir.MoveParent("Worms-Armageddon");

	if (false == Dir.MoveChild("\\Resources\\Image\\Map\\"))
	{
		GameEngineDebug::AssertFalse();
		return;
	}

	GameEngineImageFile* loadingImage = GameEngineImage::GetInst().
		LoadGameImage("Water_sprite", Dir.PathToPlusFileName("Water_sprite.bmp"));
	loadingImage->Cut({ 2560,100 });

	loadingImage = GameEngineImage::GetInst().
		LoadGameImage("Water_sprite_surfice", Dir.PathToPlusFileName("Water_sprite_surfice.bmp"));
	loadingImage->Cut({ 2560,100 });

	GameEngineImage::GetInst().
		LoadGameImage("Under_Water", Dir.PathToPlusFileName("Under_Water.bmp"));
}

void GimmickObjectImageInit() // 기믹 오브젝트 로드에 사용
{
	GameEngineDirectroy Dir = GameEngineDirectroy();
	Dir.MoveParent("Worms-Armageddon");

	if (false == Dir.MoveChild("\\Resources\\Image\\Misc\\"))
	{
		GameEngineDebug::AssertFalse();
		return;
	}

	GameEngineImageFile* loadingImage = GameEngineImage::GetInst().
		LoadGameImage("oildrum1", Dir.PathToPlusFileName("oildrum1.bmp"));
	loadingImage->Cut({ 90,90 });

	loadingImage = GameEngineImage::GetInst().
		LoadGameImage("oildrum2", Dir.PathToPlusFileName("oildrum2.bmp"));
	loadingImage->Cut({ 90,90 });

	loadingImage = GameEngineImage::GetInst().
		LoadGameImage("oildrum3", Dir.PathToPlusFileName("oildrum3.bmp"));
	loadingImage->Cut({ 90,90 });

	loadingImage = GameEngineImage::GetInst().
		LoadGameImage("oildrum4", Dir.PathToPlusFileName("oildrum4.bmp"));
	loadingImage->Cut({ 90,90 });
}

void LoadSoundInit()
{
	// 사운드 로드
	{
		GameEngineDirectroy Dir = GameEngineDirectroy();
		Dir.MoveParent("Worms-Armageddon");

		if (false == Dir.MoveChild("\\Resources\\Sound\\BGM"))
		{
			GameEngineDebug::AssertFalse();
			return;
		}

		GameEngineSound::GetInst().LoadSound("01_generic", Dir.PathToPlusFileName("ingame_01_generic.wav"));
		GameEngineSound::GetInst().LoadSound("02_cavern", Dir.PathToPlusFileName("ingame_02_cavern.wav"));
		GameEngineSound::GetInst().LoadSound("03_jungle", Dir.PathToPlusFileName("ingame_03_jungle.wav"));
		GameEngineSound::GetInst().LoadSound("04_battlezone", Dir.PathToPlusFileName("ingame_04_battlezone.wav"));
		GameEngineSound::GetInst().LoadSound("05_forest", Dir.PathToPlusFileName("ingame_05_forest.wav"));
		GameEngineSound::GetInst().LoadSound("06_weird_alien_plan", Dir.PathToPlusFileName("ingame_06_weird_alien_plan.wav"));
		GameEngineSound::GetInst().LoadSound("07_outerspace", Dir.PathToPlusFileName("ingame_07_outerspace.wav"));
		GameEngineSound::GetInst().LoadSound("08_desert", Dir.PathToPlusFileName("ingame_08_desert.wav"));
		GameEngineSound::GetInst().LoadSound("09_hellest", Dir.PathToPlusFileName("ingame_09_hellest.wav"));
		GameEngineSound::GetInst().LoadSound("10_mech_workshop", Dir.PathToPlusFileName("ingame_10_mech_workshop.wav"));
		GameEngineSound::GetInst().LoadSound("11_rain_surf", Dir.PathToPlusFileName("ingame_11_rain_surf.wav"));
		GameEngineSound::GetInst().LoadSound("lose", Dir.PathToPlusFileName("new_lose.wav"));
		GameEngineSound::GetInst().LoadSound("win_bronze", Dir.PathToPlusFileName("new_win_bronze.wav"));
		GameEngineSound::GetInst().LoadSound("win_gold", Dir.PathToPlusFileName("new_win_gold.wav"));
		GameEngineSound::GetInst().LoadSound("win_gold_special", Dir.PathToPlusFileName("new_win_gold_special.wav"));
		GameEngineSound::GetInst().LoadSound("win_silver", Dir.PathToPlusFileName("new_win_silver.wav"));
		GameEngineSound::GetInst().LoadSound("Stats", Dir.PathToPlusFileName("Stats.wav"));
		GameEngineSound::GetInst().LoadSound("suddendeath1_loop", Dir.PathToPlusFileName("suddendeath1_loop.wav"));
		GameEngineSound::GetInst().LoadSound("suddendeath2_loop", Dir.PathToPlusFileName("suddendeath2_loop.wav"));
		GameEngineSound::GetInst().LoadSound("title", Dir.PathToPlusFileName("title.wav"));

		//if (false == Dir.MoveChild("\\Resources\\Sound\\Effects\\"))
		//{
		//	GameEngineDebug::AssertFalse();
		//	return;
		//}

		//if (false == Dir.MoveChild("\\Resources\\Sound\\BGM\\"))
		//{
		//	GameEngineDebug::AssertFalse();
		//	return;
		//}

		//if (false == Dir.MoveChild("\\Resources\\Sound\\English\\"))
		//{
		//	GameEngineDebug::AssertFalse();
		//	return;
		//}
	}
}
