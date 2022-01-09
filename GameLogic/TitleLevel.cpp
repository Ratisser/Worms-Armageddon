#include "TitleLevel.h"
#include "TitleLogo.h"
#include "TitleBack.h"
#include <GameEngineImage.h>
#include <GameEngineImageFile.h>
#include <GameEngineDirectroy.h>


// Static Var
// Static Func

// constructer destructer
TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
}

TitleLevel::TitleLevel(TitleLevel&& _other) noexcept
{
}

//member Func
void TitleLevel::Loading() 
{

	TitleLogo* Logo = CreateActor<TitleLogo>();
	// Logo->SetPos({500, 560});
	CreateActor<TitleBack>();

}

void TitleLevel::LevelUpdate()
{
	int a = 0;
}