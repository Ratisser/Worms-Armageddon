#include "PlayBack.h"
#include <GameEngineImage.h>
#include <GameEngineImageFile.h>
#include <GameEngineCollision.h>
#include "LogicEnum.h"


GameEngineCollision* PlayBack::MapCollision = nullptr;

// Static Var
// Static Func

// constructer destructer
PlayBack::PlayBack()
{
}

PlayBack::~PlayBack()
{
}

PlayBack::PlayBack(PlayBack&& _other) noexcept
{
}

//member Func

void PlayBack::Start() 
{
	MapCollision = CreateCollision(ST2GROUP::MAP, CollisionCheckType::IMAGE);
	MapCollision->SetImage("DungeonMap.bmp");
}

void PlayBack::Render() 
{
	{
		GameEngineImageFile* FindImage = GameEngineImage::GetInst().FindGameImage("DungeonMap.bmp");
		GameEngineImageFile* WindowImage = GameEngineImage::GetInst().GetBackBufferImage();
		WindowImage->BitCopyToImageSize(FindImage, GetCamEffectPos());
	}
}