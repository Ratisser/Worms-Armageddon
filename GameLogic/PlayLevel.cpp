#include <GameEngineLevelManager.h>
#include <GameEngineLevel.h>
#include <GameEngineInput.h>
#include <GameEngineWindow.h>

#include "MapTrain.h"
#include "PlayLevel.h"
#include "Worm.h"
#include "UIController.h"

#include "BottomHealthBar.h"
#include "BottomNameTag.h"
#include "BottomFlag.h"

#include "BackgroundScatter.h"

PlayLevel::PlayLevel() // default constructer ����Ʈ ������
{

}

PlayLevel::~PlayLevel() // default destructer ����Ʈ �Ҹ���
{

}

PlayLevel::PlayLevel(PlayLevel&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
{

}

void PlayLevel::Loading()
{
	if (false == GameEngineInput::GetInst().IsKey("Debug_Next"))
	{
		GameEngineInput::GetInst().CreateKey("Debug_Next", 'P');
	}
	CreateActor<MapTrain>();


	if (false == GameEngineInput::GetInst().IsKey("Up"))
	{
		GameEngineInput::GetInst().CreateKey("Up", 'w');
	}
	if (false == GameEngineInput::GetInst().IsKey("Down"))
	{
		GameEngineInput::GetInst().CreateKey("Down", 's');
	}
	if (false == GameEngineInput::GetInst().IsKey("Left"))
	{
		GameEngineInput::GetInst().CreateKey("Left", 'a');
	}
	if (false == GameEngineInput::GetInst().IsKey("Right"))
	{
		GameEngineInput::GetInst().CreateKey("Right", 'd');
	}

	CreateActor<Worm>();

	for (int i = 0; i < 39; i++)
	{
		// ��� �ٶ��� �𳯸��� ���� ����(���� �ڷᱸ���� ���� ����)
		BackgroundScatter* newScatter = CreateActor<BackgroundScatter>();
	}

	{
		// �÷���ȭ�� �ϴ� ü�¹�
		BottomNameTag* p1NameTag = CreateActor<BottomNameTag>();
		p1NameTag->SetPos({ 555, 700 });

		BottomFlag* p1Flag = CreateActor<BottomFlag>();
		p1Flag->SetPos({ 610, 700 });

		BottomHealthBar* p1Health = CreateActor<BottomHealthBar>();
		p1Health->SetPos({ 672, 700 });
	}

	// UI�����ڻ���
	CreateActor<UIController>();
}

void PlayLevel::LevelUpdate()
{
	if (true == GameEngineInput::GetInst().IsDown("Debug_Next"))
	{
		GameEngineLevelManager::GetInst().ChangeLevel("LobbyLevel");
	}

	if (true == GameEngineInput::GetInst().IsPress("Up"))
	{
		GameEngineLevel::SetCamMove(float4::UP);
	}
	if (true == GameEngineInput::GetInst().IsPress("Down"))
	{
		GameEngineLevel::SetCamMove(float4::DOWN);
	}
	if (true == GameEngineInput::GetInst().IsPress("Left"))
	{
		GameEngineLevel::SetCamMove(float4::LEFT);
	}
	if (true == GameEngineInput::GetInst().IsPress("Right"))
	{
		GameEngineLevel::SetCamMove(float4::RIGHT);
	}
}