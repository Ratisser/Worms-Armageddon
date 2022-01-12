#pragma once
#include <string>
#include <GameEngineImageFile.h>

void AppRelease();
void AppResourcesInit();


// �ε� �̹��� Ŀ�� �浹 ������ �Լ� ���� - ������ 
void LoadingImageInit();

// UI �̹��� Ŀ�� �浹 ������ �Լ� ���� - ������
void UIImageInit();

// 2022-01-12 ������ : 
namespace RS
{
	GameEngineImageFile* LoadImageFromFile(const std::string& path);
}
void CharactorImageInit();