#include "TitleLogo.h"
#include <GameEngineWindow.h>
#include <GameEngineTime.h>
#include <GameEngineImageFile.h>
#include <GameEngineImage.h>
#include <GameEngineInput.h>
#include <GameEngineLevelManager.h>


// Static Var
// Static Func

// constructer destructer
TitleLogo::TitleLogo()
{
	SetPos(GameEngineWindow::GetInst().GetSize().halffloat4());
	SetRenderOrder(200);
}

TitleLogo::~TitleLogo()
{
}

TitleLogo::TitleLogo(TitleLogo&& _other) noexcept
{
}


void TitleLogo::Start() 
{
	if (false == GameEngineInput::GetInst().IsKey("LevelChange"))
	{
		GameEngineInput::GetInst().CreateKey("LevelChange", 'P');
	}
}

void TitleLogo::Update() 
{
	if (true == GameEngineInput::GetInst().IsDown("LevelChange"))
	{
		GameEngineLevelManager::GetInst().ChangeLevel("Play");

		// OutputDebugStringA("Down\n");
	}

	//if (true == GameEngineInput::GetInst().IsPress("Test"))
	//{
	//	OutputDebugStringA("press\n");
	//}

	//if (true == GameEngineInput::GetInst().IsUp("Test"))
	//{
	//	OutputDebugStringA("Up\n");
	//}

	// SetMove(float4::RIGHT * GameEngineTime::GetInst().GetDeltaTime() * 100.0f);
}
//member Func

void TitleLogo::Render()
{
	{
		GameEngineImageFile* FindImage = GameEngineImage::GetInst().FindGameImage("Title.bmp");
		GameEngineImageFile* WindowImage = GameEngineImage::GetInst().GetBackBufferImage ();
		// WindowImage->BitCopyToImageSize(FindImage, float4::ZERO);
		WindowImage->BitCopyToImageSizeToCenter(FindImage, GetPos());
	}

	//{
	//	GameEngineImage* FindImage = ResourcesManager::GetInst().FindGameImage("knuckles.bmp");
	//	GameEngineImage* WindowImage = ResourcesManager::GetInst().GetBackBufferImage();
	//	WindowImage->BitCopy(FindImage, GetPos() - float4(50.0f, 50.0f) + float4(0.0f, 150.0f), { 40.0f, 60.0f });
	//}
}