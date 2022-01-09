#include "TitleBack.h"
#include <GameEngineImageFile.h>
#include <GameEngineImage.h>
#include <GameEngineWindow.h>


// Static Var
// Static Func

// constructer destructer
TitleBack::TitleBack()
{
	SetPos(GameEngineWindow::GetInst().GetSize().halffloat4());
	SetRenderOrder(1000);
}

TitleBack::~TitleBack()
{
}

TitleBack::TitleBack(TitleBack&& _other) noexcept
{
}

void TitleBack::Update() 
{

}

void TitleBack::Render() 
{
	{
		GameEngineImageFile* FindImage = GameEngineImage::GetInst().FindGameImage("knuckles.bmp");
		GameEngineImageFile* WindowImage = GameEngineImage::GetInst().GetBackBufferImage();
		WindowImage->TransCopy(FindImage, 
			GetPos(), // �� ��ġ��������
			{30 * 2, 50 * 2 }, // �̸��� ũ��� �׷���!
			// �ű⿡ �׷����� �̹����� �κ���....
			{ 0, 0 }, // �̹����� �� ��ġ��������
			{ 30, 50 },  // �̹����� �� ��ġ������ �׸���
			RGB(255, 0, 255));

		//{ 0, 0 }, // �̹����� �� ��ġ��������
		//{ 30, 50 },  // �̹����� �� ��ġ������ �׸���

		// GetPos(), // ȭ�鿡 �� ��ġ��������
		// { 30 * 2, 50 * 2 }, // ȭ�鿡 �̸�ũ��� �׷���!

	}
}