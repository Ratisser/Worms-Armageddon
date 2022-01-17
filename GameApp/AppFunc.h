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
	GameEngineImageFile* LoadImageFromFile(const std::string& path);
}
void CharactorImageInit();

void MapWaterImageInit();
void GimmickObjectImageInit();
void EffectImageInit();

void LoadSoundInit();