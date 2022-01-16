#pragma once
#include <string>
#include <GameEngineImageFile.h>

void AppRelease();
void AppResourcesInit();


// 로딩 이미지 커밋 충돌 방지용 함수 묶음 - 박종원 
void ResourceInitPJW();

// UI 이미지 커밋 충돌 방지용 함수 묶음 - 신종하
void UIImageInit();

// 2022-01-12 조규현 : 
namespace RS
{
	GameEngineImageFile* LoadImageFromFile(const std::string& path);
}
void CharactorImageInit();

void MapWaterImageInit();
void GimmickObjectImageInit();
void EffectImageInit();

void LoadSoundInit();