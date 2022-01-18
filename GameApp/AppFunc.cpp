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

#include <GlobalValue.h>

void AppResourcesInit() 
{
	// 맵 최소, 최대값 초기화
	{
		GlobalValue::MapMinMaxInfo.insert(std::pair<std::string, float4>("MapTrain", { 800.f, 3300.f }));
	}

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

		// 맵 종류

		// 맵
		GameEngineImage::GetInst().LoadGameImage("MapTrain", Dir.PathToPlusFileName("MapTrain.bmp"));
		GameEngineImage::GetInst().LoadGameImage("MapBooks", Dir.PathToPlusFileName("MapBooks.bmp"));
		GameEngineImage::GetInst().LoadGameImage("MapCars", Dir.PathToPlusFileName("MapCars.bmp"));
		GameEngineImage::GetInst().LoadGameImage("MapCity", Dir.PathToPlusFileName("MapCity.bmp"));

		// 충돌맵
		GameEngineImage::GetInst().LoadGameImage("MapTrain_Ground", Dir.PathToPlusFileName("MapTrain_Ground.bmp"));
		GameEngineImage::GetInst().LoadGameImage("MapBooks_Ground", Dir.PathToPlusFileName("MapBooks_Ground.bmp"));
		GameEngineImage::GetInst().LoadGameImage("MapCars_Ground", Dir.PathToPlusFileName("MapCars_Ground.bmp"));
		GameEngineImage::GetInst().LoadGameImage("MapCity_Ground", Dir.PathToPlusFileName("MapCity_Ground.bmp"));

		GameEngineImage::GetInst().LoadGameImage("Ground", Dir.PathToPlusFileName("Ground.bmp"));
		GameEngineImage::GetInst().LoadGameImage("Boom", Dir.PathToPlusFileName("Boom.bmp"));
		GameEngineImage::GetInst().LoadGameImage("Bazooka", Dir.PathToPlusFileName("Bazooka.bmp"));
		
		ResourceInitPJW();
		CharactorImageInit();
		UIImageInit();
		MapWaterImageInit();
		GimmickObjectImageInit();
		EffectImageInit();
		LobbyImageInit();
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
	GameEngineImage::GetInst().LoadGameImage("Midground", Dir.PathToPlusFileName("Midground.bmp"));

	if (false == Dir.MoveChild("\\Misc\\"))
	{
		GameEngineDebug::AssertFalse();
		return;
	}

	GameEngineImage::GetInst().LoadGameImage("ScatterStar", Dir.PathToPlusFileName("ScatterStar.bmp"));
	GameEngineImage::GetInst().LoadGameImage("ScatterSnow", Dir.PathToPlusFileName("ScatterSnow.bmp"));
	GameEngineImage::GetInst().LoadGameImage("windGauge", Dir.PathToPlusFileName("windGauge.bmp"));
	GameEngineImage::GetInst().LoadGameImage("windBarHider", Dir.PathToPlusFileName("windBarHider.bmp"));
	GameEngineImageFile* windBarSprites = GameEngineImage::GetInst().LoadGameImage("windBar", Dir.PathToPlusFileName("windBar.bmp"));
	windBarSprites->Cut({87,13});
	GameEngineImageFile* leafSprites = GameEngineImage::GetInst().LoadGameImage("ScatterLeaf", Dir.PathToPlusFileName("ScatterLeaf.bmp"));
	leafSprites->Cut({32,32});
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

	// 무기선택박스
	GameEngineImage::GetInst().LoadGameImage("WeaponSelector", Dir.PathToPlusFileName("WeaponSelector.bmp"));

	// 무기창의 무기목록
	// Weapon Sheet Utile Line
	GameEngineImage::GetInst().LoadGameImage("jetpack", Dir.PathToPlusFileName("jetpack.bmp"));
	GameEngineImage::GetInst().LoadGameImage("gravity", Dir.PathToPlusFileName("gravity.bmp"));
	GameEngineImage::GetInst().LoadGameImage("speed", Dir.PathToPlusFileName("speed.bmp"));
	GameEngineImage::GetInst().LoadGameImage("laser", Dir.PathToPlusFileName("laser.bmp"));
	GameEngineImage::GetInst().LoadGameImage("invisibl", Dir.PathToPlusFileName("invisibl.bmp"));

	// Weapon Sheet F1 Line
	GameEngineImage::GetInst().LoadGameImage("bazooka", Dir.PathToPlusFileName("bazooka.bmp"));
	GameEngineImage::GetInst().LoadGameImage("hmissile", Dir.PathToPlusFileName("hmissile.bmp"));
	GameEngineImage::GetInst().LoadGameImage("mortar", Dir.PathToPlusFileName("mortar.bmp"));
	GameEngineImage::GetInst().LoadGameImage("pigeon", Dir.PathToPlusFileName("pigeon.bmp"));
	GameEngineImage::GetInst().LoadGameImage("launch", Dir.PathToPlusFileName("launch.bmp"));

	// Weapon Sheet F2 Line
	GameEngineImage::GetInst().LoadGameImage("grenade", Dir.PathToPlusFileName("grenade.bmp"));
	GameEngineImage::GetInst().LoadGameImage("cluster", Dir.PathToPlusFileName("cluster.bmp"));
	GameEngineImage::GetInst().LoadGameImage("banana", Dir.PathToPlusFileName("banana.bmp"));
	GameEngineImage::GetInst().LoadGameImage("axe", Dir.PathToPlusFileName("axe.bmp"));
	GameEngineImage::GetInst().LoadGameImage("quake", Dir.PathToPlusFileName("quake.bmp"));

	// Weapon Sheet F3 Line
	GameEngineImage::GetInst().LoadGameImage("shotgun", Dir.PathToPlusFileName("shotgun.bmp"));
	GameEngineImage::GetInst().LoadGameImage("handgun", Dir.PathToPlusFileName("handgun.bmp"));
	GameEngineImage::GetInst().LoadGameImage("uzi", Dir.PathToPlusFileName("uzi.bmp"));
	GameEngineImage::GetInst().LoadGameImage("minigun", Dir.PathToPlusFileName("minigun.bmp"));
	GameEngineImage::GetInst().LoadGameImage("longbow", Dir.PathToPlusFileName("longbow.bmp"));

	// Weapon Sheet F4 Line
	GameEngineImage::GetInst().LoadGameImage("firepnch", Dir.PathToPlusFileName("firepnch.bmp"));
	GameEngineImage::GetInst().LoadGameImage("dragball", Dir.PathToPlusFileName("dragball.bmp"));
	GameEngineImage::GetInst().LoadGameImage("kamikaze", Dir.PathToPlusFileName("kamikaze.bmp"));
	GameEngineImage::GetInst().LoadGameImage("suicide", Dir.PathToPlusFileName("suicide.bmp"));
	GameEngineImage::GetInst().LoadGameImage("prod", Dir.PathToPlusFileName("prod.bmp"));

	// Weapon Sheet F5 Line
	GameEngineImage::GetInst().LoadGameImage("dynamite", Dir.PathToPlusFileName("dynamite.bmp"));
	GameEngineImage::GetInst().LoadGameImage("mine", Dir.PathToPlusFileName("mine.bmp"));
	GameEngineImage::GetInst().LoadGameImage("sheep", Dir.PathToPlusFileName("sheep.bmp"));
	GameEngineImage::GetInst().LoadGameImage("aqua", Dir.PathToPlusFileName("aqua.bmp"));
	GameEngineImage::GetInst().LoadGameImage("mole", Dir.PathToPlusFileName("mole.bmp"));

	// Weapon Sheet F6 Line
	GameEngineImage::GetInst().LoadGameImage("airstrke", Dir.PathToPlusFileName("airstrke.bmp"));
	GameEngineImage::GetInst().LoadGameImage("firestrk", Dir.PathToPlusFileName("firestrk.bmp"));
	GameEngineImage::GetInst().LoadGameImage("postal", Dir.PathToPlusFileName("postal.bmp"));
	GameEngineImage::GetInst().LoadGameImage("minestrk", Dir.PathToPlusFileName("minestrk.bmp"));
	GameEngineImage::GetInst().LoadGameImage("molestrk", Dir.PathToPlusFileName("molestrk.bmp"));

	// Weapon Sheet F7 Line
	GameEngineImage::GetInst().LoadGameImage("blwtorch", Dir.PathToPlusFileName("blwtorch.bmp"));
	GameEngineImage::GetInst().LoadGameImage("drill", Dir.PathToPlusFileName("drill.bmp"));
	GameEngineImage::GetInst().LoadGameImage("girder", Dir.PathToPlusFileName("girder.bmp"));
	GameEngineImage::GetInst().LoadGameImage("baseball", Dir.PathToPlusFileName("baseball.bmp"));
	GameEngineImage::GetInst().LoadGameImage("girders", Dir.PathToPlusFileName("girders.bmp"));

	// Weapon Sheet F8 Line
	GameEngineImage::GetInst().LoadGameImage("rope", Dir.PathToPlusFileName("rope.bmp"));
	GameEngineImage::GetInst().LoadGameImage("bungee", Dir.PathToPlusFileName("bungee.bmp"));
	GameEngineImage::GetInst().LoadGameImage("parachut", Dir.PathToPlusFileName("parachut.bmp"));
	GameEngineImage::GetInst().LoadGameImage("teleport", Dir.PathToPlusFileName("teleport.bmp"));
	GameEngineImage::GetInst().LoadGameImage("scales", Dir.PathToPlusFileName("scales.bmp"));

	// Weapon Sheet F9 Line
	GameEngineImage::GetInst().LoadGameImage("sbanana", Dir.PathToPlusFileName("sbanana.bmp"));
	GameEngineImage::GetInst().LoadGameImage("hgrenade", Dir.PathToPlusFileName("hgrenade.bmp"));
	GameEngineImage::GetInst().LoadGameImage("thrower", Dir.PathToPlusFileName("thrower.bmp"));
	GameEngineImage::GetInst().LoadGameImage("tamborin", Dir.PathToPlusFileName("tamborin.bmp"));
	GameEngineImage::GetInst().LoadGameImage("mbbomb", Dir.PathToPlusFileName("mbbomb.bmp"));

	// Weapon Sheet F10 Line
	GameEngineImage::GetInst().LoadGameImage("petrolbm", Dir.PathToPlusFileName("petrolbm.bmp"));
	GameEngineImage::GetInst().LoadGameImage("skunk", Dir.PathToPlusFileName("skunk.bmp"));
	GameEngineImage::GetInst().LoadGameImage("mingvase", Dir.PathToPlusFileName("mingvase.bmp"));
	GameEngineImage::GetInst().LoadGameImage("shpstrke", Dir.PathToPlusFileName("shpstrke.bmp"));
	GameEngineImage::GetInst().LoadGameImage("carpet", Dir.PathToPlusFileName("carpet.bmp"));

	// Weapon Sheet F11 Line
	GameEngineImage::GetInst().LoadGameImage("cow", Dir.PathToPlusFileName("cow.bmp"));
	GameEngineImage::GetInst().LoadGameImage("oldwoman", Dir.PathToPlusFileName("oldwoman.bmp"));
	GameEngineImage::GetInst().LoadGameImage("donkey", Dir.PathToPlusFileName("donkey.bmp"));
	GameEngineImage::GetInst().LoadGameImage("nuke", Dir.PathToPlusFileName("nuke.bmp"));
	GameEngineImage::GetInst().LoadGameImage("armagedn", Dir.PathToPlusFileName("armagedn.bmp"));

	// Weapon Sheet F12 Line
	GameEngineImage::GetInst().LoadGameImage("skipgo", Dir.PathToPlusFileName("skipgo.bmp"));
	GameEngineImage::GetInst().LoadGameImage("surender", Dir.PathToPlusFileName("surender.bmp"));
	GameEngineImage::GetInst().LoadGameImage("select", Dir.PathToPlusFileName("select.bmp"));
	GameEngineImage::GetInst().LoadGameImage("freeze", Dir.PathToPlusFileName("freeze.bmp"));
	GameEngineImage::GetInst().LoadGameImage("bullet", Dir.PathToPlusFileName("bullet.bmp"));
}

void LobbyImageInit()
{
	GameEngineDirectroy Dir = GameEngineDirectroy();
	Dir.MoveParent("Worms-Armageddon");
	if (false == Dir.MoveChild("\\Resources\\Image"))
	{
		GameEngineDebug::AssertFalse();
		return;
	}

	GameEngineImage::GetInst().LoadGameImage("Lobby_Backdrop", Dir.PathToPlusFileName("Lobby_Backdrop.bmp"));

	// 선택가능 맵 이미지 로딩
	Dir.MoveParent("Worms-Armageddon");
	if (false == Dir.MoveChild("\\Resources\\Image\\UI\\SelectMap"))
	{
		GameEngineDebug::AssertFalse();
		return;
	}

	GameEngineImage::GetInst().LoadGameImage("LobbyMap_MapTrain", Dir.PathToPlusFileName("LobbyMap_MapTrain.bmp"));
	GameEngineImage::GetInst().LoadGameImage("LobbyMap_MapCars", Dir.PathToPlusFileName("LobbyMap_MapCars.bmp"));
	GameEngineImage::GetInst().LoadGameImage("LobbyMap_MapCity", Dir.PathToPlusFileName("LobbyMap_MapCity.bmp"));
	GameEngineImage::GetInst().LoadGameImage("LobbyMap_MapBooks", Dir.PathToPlusFileName("LobbyMap_MapBooks.bmp"));

}

void CharactorImageInit()
{
	GameEngineDirectroy dir = GameEngineDirectroy();
	dir.MoveParent("Worms-Armageddon");
	dir.MoveChild("\\Resources\\Image\\Worms");

	float4 cutSize = float4(60.f, 60.f);

	RS::LoadImageFromFileAndCut(dir.PathToPlusFileName("walkLeft.bmp"), cutSize);
	RS::LoadImageFromFileAndCut(dir.PathToPlusFileName("walkRight.bmp"), cutSize);
	RS::LoadImageFromFileAndCut(dir.PathToPlusFileName("jumpReadyLeft.bmp"), cutSize);
	RS::LoadImageFromFileAndCut(dir.PathToPlusFileName("jumpReadyRight.bmp"), cutSize);
	RS::LoadImageFromFileAndCut(dir.PathToPlusFileName("flyUpLeft.bmp"), cutSize);
	RS::LoadImageFromFileAndCut(dir.PathToPlusFileName("flyUpRight.bmp"), cutSize);
	RS::LoadImageFromFileAndCut(dir.PathToPlusFileName("flyDownLeft.bmp"), cutSize);
	RS::LoadImageFromFileAndCut(dir.PathToPlusFileName("flyDownRight.bmp"), cutSize);
	RS::LoadImageFromFileAndCut(dir.PathToPlusFileName("flyLinkLeft.bmp"), cutSize);
	RS::LoadImageFromFileAndCut(dir.PathToPlusFileName("flyLinkRight.bmp"), cutSize);
	RS::LoadImageFromFileAndCut(dir.PathToPlusFileName("idleLeft.bmp"), cutSize);
	RS::LoadImageFromFileAndCut(dir.PathToPlusFileName("idleRight.bmp"), cutSize);
	RS::LoadImageFromFileAndCut(dir / "bazAimLeft.bmp", cutSize);
	RS::LoadImageFromFileAndCut(dir / "bazAimRight.bmp", cutSize);
	RS::LoadImageFromFileAndCut(dir / "bazOffLeft.bmp", cutSize);
	RS::LoadImageFromFileAndCut(dir / "bazOffRight.bmp", cutSize);
	RS::LoadImageFromFileAndCut(dir / "bazOnLeft.bmp", cutSize);
	RS::LoadImageFromFileAndCut(dir / "bazOnRight.bmp", cutSize);

	{
		GameEngineDirectroy dir = GameEngineDirectroy();
		dir.MoveParent("Worms-Armageddon");
		dir.MoveChild("\\Resources\\Image\\Misc\\Aim_Taget");
		RS::LoadImageFromFileAndCut(dir / "crshairr.bmp", cutSize);
	}
}

GameEngineImageFile* RS::LoadImageFromFile(const std::string& _path)
{
	size_t fileNameStartIndex = _path.rfind("\\") + 1;
	std::string fileName = _path.substr(fileNameStartIndex, _path.size() - fileNameStartIndex);

	return GameEngineImage::GetInst().LoadGameImage(fileName, _path);
}

void RS::LoadImageFromFileAndCut(const std::string& _path, const float4& _cutSize)
{
	size_t fileNameStartIndex = _path.rfind("\\") + 1;
	std::string fileName = _path.substr(fileNameStartIndex, _path.size() - fileNameStartIndex);

	GameEngineImageFile* image = GameEngineImage::GetInst().LoadGameImage(fileName, _path);
	image->Cut(_cutSize);
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

void EffectImageInit()
{
	GameEngineDirectroy Dir = GameEngineDirectroy();
	Dir.MoveParent("Worms-Armageddon");

	if (false == Dir.MoveChild("\\Resources\\Image\\Effects\\"))
	{
		GameEngineDebug::AssertFalse();
		return;
	}

	GameEngineImageFile* loadingImage = GameEngineImage::GetInst().
		LoadGameImage("circle25", Dir.PathToPlusFileName("circle25.bmp"));
	loadingImage->Cut({ 50,50 });

	loadingImage = GameEngineImage::GetInst().
		LoadGameImage("circle50", Dir.PathToPlusFileName("circle50.bmp"));
	loadingImage->Cut({ 100,100 });

	loadingImage = GameEngineImage::GetInst().
		LoadGameImage("circle75", Dir.PathToPlusFileName("circle75.bmp"));
	loadingImage->Cut({ 150,150 });

	loadingImage = GameEngineImage::GetInst().
		LoadGameImage("circle100", Dir.PathToPlusFileName("circle100.bmp"));
	loadingImage->Cut({ 200,200 });


	loadingImage = GameEngineImage::GetInst().
		LoadGameImage("elipse100", Dir.PathToPlusFileName("elipse100.bmp"));
	loadingImage->Cut({ 300,300 });

	loadingImage = GameEngineImage::GetInst().
		LoadGameImage("elipse75", Dir.PathToPlusFileName("elipse75.bmp"));
	loadingImage->Cut({ 224,224 });

	loadingImage = GameEngineImage::GetInst().
		LoadGameImage("elipse50", Dir.PathToPlusFileName("elipse50.bmp"));
	loadingImage->Cut({ 150,150 });

	loadingImage = GameEngineImage::GetInst().
		LoadGameImage("elipse25", Dir.PathToPlusFileName("elipse25.bmp"));
	loadingImage->Cut({ 74,74 });

	//말풍선 효과음, 아직 사용 안됨

	loadingImage = GameEngineImage::GetInst().
		LoadGameImage("exbiff", Dir.PathToPlusFileName("exbiff.bmp"));
	loadingImage->Cut({60,60 });

	loadingImage = GameEngineImage::GetInst().
		LoadGameImage("exfoom", Dir.PathToPlusFileName("exfoom.bmp"));
	loadingImage->Cut({ 100,100 });

	loadingImage = GameEngineImage::GetInst().
		LoadGameImage("expoot", Dir.PathToPlusFileName("expoot.bmp"));
	loadingImage->Cut({ 70,70 });

	loadingImage = GameEngineImage::GetInst().
		LoadGameImage("expow", Dir.PathToPlusFileName("expow.bmp"));
	loadingImage->Cut({ 60,60 });

	//


	loadingImage = GameEngineImage::GetInst().
		LoadGameImage("flame1", Dir.PathToPlusFileName("flame1.bmp"));
	loadingImage->Cut({ 60,60 });

	loadingImage = GameEngineImage::GetInst().
		LoadGameImage("flame2", Dir.PathToPlusFileName("flame2.bmp"));
	loadingImage->Cut({ 60,60 });


	// 아직 사용 안됨(클레스 없음)
	loadingImage = GameEngineImage::GetInst().
		LoadGameImage("skdsmoke", Dir.PathToPlusFileName("skdsmoke.bmp"));
	loadingImage->Cut({ 20,20 });
	//

	loadingImage = GameEngineImage::GetInst().
		LoadGameImage("smkdrk20", Dir.PathToPlusFileName("smkdrk20.bmp"));
	loadingImage->Cut({ 20,20 });

	loadingImage = GameEngineImage::GetInst().
		LoadGameImage("smkdrk30", Dir.PathToPlusFileName("smkdrk30.bmp"));
	loadingImage->Cut({ 30,30 });

	loadingImage = GameEngineImage::GetInst().
		LoadGameImage("smkdrk40", Dir.PathToPlusFileName("smkdrk40.bmp"));
	loadingImage->Cut({ 40,40 });

	loadingImage = GameEngineImage::GetInst().
		LoadGameImage("smklt25", Dir.PathToPlusFileName("smklt25.bmp"));
	loadingImage->Cut({ 44,44 });

	loadingImage = GameEngineImage::GetInst().
		LoadGameImage("smklt50", Dir.PathToPlusFileName("smklt50.bmp"));
	loadingImage->Cut({ 60,60 });

	loadingImage = GameEngineImage::GetInst().
		LoadGameImage("smklt75", Dir.PathToPlusFileName("smklt75.bmp"));
	loadingImage->Cut({ 90,90 });

	loadingImage = GameEngineImage::GetInst().
		LoadGameImage("smklt100", Dir.PathToPlusFileName("smklt100.bmp"));
	loadingImage->Cut({ 134,134 });

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
