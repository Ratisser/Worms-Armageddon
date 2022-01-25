#pragma once
#include <string>
#include <GameEngineImageFile.h>

void AppRelease();
void AppResourcesInit();


// �ε� �̹��� Ŀ�� �浹 ������ �Լ� ���� - ������ 
void ResourceInitPJW();

// UI �̹��� Ŀ�� �浹 ������ �Լ� ���� - ������
void UIImageInit();

// ���Ǿ� �̹��� �ε� - ������
void LobbyImageInit();

// 2022-01-12 ������ : 
namespace RS
{
	GameEngineImageFile* LoadImageFromFile(const std::string& _path);
	void LoadImageFromFileAndCut(const std::string& _path, const float4& _cutSize);
}
void CharactorImageInit();
void WeaponImageInit();

void MapWaterImageInit();
void GimmickObjectImageInit();
void EffectImageInit();

void LoadSoundInit();
void TitleLevelInit();
void MenuSelectInit();