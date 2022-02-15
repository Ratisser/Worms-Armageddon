#include "EndingLevel.h"

#include "EndingImage.h"
#include "EndingText.h"

EndingLevel::EndingLevel()
{

}

EndingLevel::~EndingLevel()
{

}

EndingLevel::EndingLevel(EndingLevel&& _other) noexcept
{

}

void EndingLevel::Loading()
{
	CreateActor<EndingImage>();

	// 팀이름
	EndingText* TeamName = CreateActor<EndingText>();
	TeamName->EndingTextInit("WTeam", float4(800.f, 300.f), float4(300.f, 300.f));

	// 크레딧
	//EndingText* CreditText = CreateActor<EndingText>();
	//CreditText->EndingTextInit("CREDIT", float4(500.f, 500.f), float4(300.f, 300.f));

	// 제작자
	//EndingText* SHINJONGHA = CreateActor<EndingText>();
	//SHINJONGHA->EndingTextInit("shin jong ha", float4(500.f, 500.f), float4(300.f, 300.f));

	// 감사합니다
	EndingText* ThankYou = CreateActor<EndingText>();
	ThankYou->EndingTextInit("TANK YOU", float4(700.f, 600.f), float4(300.f, 300.f));
}

void EndingLevel::LevelUpdate()
{
}

