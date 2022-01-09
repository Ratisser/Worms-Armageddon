#include "PlayLevel.h"
#include <GameEngineImage.h>
#include "PlayBack.h"
#include "Player.h"
#include "Monster.h"
#include <GameEngineImageFile.h>
#include <GameEngineDirectroy.h>
#include <GameEngineSound.h>
#include <GameEngineInput.h>
#include <GameEngineSoundPlayer.h>
#include <GameEngineDebugExtension.h>
#include "FadeObject.h"


FadeObject* PlayLevel::FadeActor = nullptr;

// Static Var
// Static Func

// constructer destructer
PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
}

PlayLevel::PlayLevel(PlayLevel&& _other) noexcept
{
}

//member Func

void PlayLevel::LevelUpdate() 
{
	if (true == GameEngineInput::GetInst().IsDown("TestKey0"))
	{
		// BgmPlayer->Play("vo_shk.mp3", -1);
		// FadeActor->FadeIn();
		Reset();
	}

	if (true == GameEngineInput::GetInst().IsDown("TestKey1"))
	{
		// FadeActor->FadeOut();
	}
}

void PlayLevel::Loading() 
{

	if (false == GameEngineInput::GetInst().IsKey("TestKey0"))
	{
		GameEngineInput::GetInst().CreateKey("TestKey0", 'k');
		GameEngineInput::GetInst().CreateKey("TestKey1", 'l');
	}


	FadeActor = CreateActor<FadeObject>();
	CreateActor<PlayBack>();
	CreateActor<Player>();
	CreateActor<Monster>();

	BgmPlayer = GameEngineSound::GetInst().CreateSoundPlayer();

	// GameEngineSound::GetInst().PlaySoundOneShot("Bgm.mp3");
}

void PlayLevel::LevelUpdateAfter()
{
	if (true == GameEngineInput::GetInst().IsPress("TestKey1"))
	{
		// GameEngineMath::Random 

		float4 CamSPos = { RandomGen.RandomFloat(-10, 10), RandomGen.RandomFloat(-10, 10) };
		float4 CamCurPos = GetCamPos();

		// 플레이어가 내가 키를 안누르면 어차피 플레이어가 다시 원점으로 돌려준다 자기 중심으로
		// 그걸 믿고 여기서는 그냥 마음대로
		SetCamPos(CamCurPos + CamSPos);
	}

	GameEngineDebugExtension::PrintDebugWindowText("aaaaaaaaaa");

	GameEngineDebugExtension::PrintDebugWindowTextTrim(10000, 500000, 1.32112f);
}