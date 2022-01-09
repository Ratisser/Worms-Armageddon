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

// �����Ҷ� ��Ģ
class PlayerSaveData 
{
public:
	int Hp;
};

void AppResourcesInit() 
{
	{
		GameEngineDirectroy Dir = GameEngineDirectroy();
		Dir.MoveParent("API38");

		GameEngineFile NewFile = Dir.PathToCreateFile("MyData.Data");

		NewFile.Open("wb");

		std::string Text = "������ ȣȣȣ ������";
		std::string Text1 = "������ ������ ������";
		NewFile.Write(Text);
		NewFile.Write(Text1);

		PlayerSaveData Data;
		Data.Hp = 100;
		NewFile.Write(&Data, sizeof(PlayerSaveData));

		std::vector<std::string> TestVector;
		TestVector.push_back("Test1");
		TestVector.push_back("Test2");

		NewFile.Write(TestVector);


		// std::list<std::string>::iterator
		std::list<std::string> TestList;
		TestList.push_back("Test1");
		TestList.push_back("Test2");

		NewFile.Write(TestList);

		std::map<int, std::string> TestMap;
		TestMap.insert(std::map < int, std::string>::value_type(1, "Test1"));
		TestMap.insert(std::map < int, std::string>::value_type(2, "Test2"));

		NewFile.Write(TestMap);
	}

	{
		GameEngineDirectroy Dir = GameEngineDirectroy();
		Dir.MoveParent("API38");

		// Dir.PathToCreateFile("MyData.Data"); �̰� ���ؼ��� �ؾߵ�
		GameEngineFile NewFile = Dir.PathToGetFile("MyData.Data");
		NewFile.Open("rb");

		std::string Text;
		std::string Text1;

		NewFile.Read(Text);
		NewFile.Read(Text1);

		PlayerSaveData Data;
		NewFile.Read(&Data, sizeof(PlayerSaveData), sizeof(PlayerSaveData));

		std::vector<std::string> TestVector;
		NewFile.Read(TestVector);
		std::list<std::string> TestList;
		NewFile.Read(TestList);
		std::map<int, std::string> TestMap;
		NewFile.Read(TestMap);


	}

	{
		GameEngineDirectroy Dir = GameEngineDirectroy();
		Dir.MoveParent("API38");

		if (false == Dir.MoveChild("\\Resources\\Image\\"))
		{
			GameEngineDebug::AssertFalse();
			return;
		}

		// ���� ���
		GameEngineImage::GetInst().LoadGameImage("TEST.bmp"
			, Dir.PathToPlusFileName("TEST.bmp"));

		GameEngineImage::GetInst().LoadGameImage("TEST1.bmp"
			, Dir.PathToPlusFileName("TEST1.bmp"));

		GameEngineImage::GetInst().LoadGameImage("Title.bmp"
			, Dir.PathToPlusFileName("Title.bmp"));

		GameEngineImageFile* Image = GameEngineImage::GetInst().LoadGameImage("knuckles.bmp"
			, Dir.PathToPlusFileName("knuckles.bmp"));

		Image->Cut({ 128, 128 });

		GameEngineImage::GetInst().LoadGameImage("knucklesMask.bmp"
			, Dir.PathToPlusFileName("knucklesMask.bmp"));

		GameEngineImage::GetInst().LoadGameImage("BackGround.bmp"
			, Dir.PathToPlusFileName("BackGround.bmp"));

		GameEngineImage::GetInst().LoadGameImage("hpbar.bmp"
			, Dir.PathToPlusFileName("hpbar.bmp"));

		GameEngineImage::GetInst().LoadGameImage("PlayBack.bmp"
			, Dir.PathToPlusFileName("PlayBack.bmp"));

		GameEngineImage::GetInst().LoadGameImage("DungeonMap.bmp"
			, Dir.PathToPlusFileName("DungeonMap.bmp"));
	}

	{
		GameEngineDirectroy Dir = GameEngineDirectroy();
		Dir.MoveParent("API38");

		if (false == Dir.MoveChild("\\Resources\\Sound\\"))
		{
			GameEngineDebug::AssertFalse();
			return;
		}

		GameEngineSound::GetInst().LoadSound("Bgm.mp3"
			, Dir.PathToPlusFileName("Bgm.mp3"));

		GameEngineSound::GetInst().LoadSound("vo_shk.mp3"
			, Dir.PathToPlusFileName("vo_shk.mp3"));
	}
}

void AppRelease() 
{
	GameEngineDebugExtension::Release();
	// �޸� ���� ����
	GameEngineLevelManager::Destroy();


	// ���� �������� ������.
	// ���� �ٲ��� ������.
	GameEngineImage::Destroy();


	// �����쿡���� ����� �̹����� �������� �ʰڽ��ϴ�.
	GameEngineSound::Destroy();
	GameEngineInput::Destroy();
	GameEngineWindow::Destroy();
	GameEngineTime::Destroy();
}