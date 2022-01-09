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
			GetPos(), // 이 위치에서부터
			{30 * 2, 50 * 2 }, // 이만한 크기로 그려라!
			// 거기에 그려야할 이미지의 부분은....
			{ 0, 0 }, // 이미지의 이 위치에서부터
			{ 30, 50 },  // 이미지의 이 위치까지의 그림을
			RGB(255, 0, 255));

		//{ 0, 0 }, // 이미지의 이 위치에서부터
		//{ 30, 50 },  // 이미지의 이 위치까지의 그림을

		// GetPos(), // 화면에 이 위치에서부터
		// { 30 * 2, 50 * 2 }, // 화면에 이만크기로 그려라!

	}
}