#include "GameController.h"

#include <GameEngineMath.h>
#include <GameEngineWindow.h>
#include <GameEngineLevel.h>
#include <GameEngineInput.h>
#include "Worm.h"
#include "UIController.h"
#include "WeaponSheet.h"
#include "WeaponIcon.h"
#include "Weapon.h"

GameController::GameController() // default constructer ����Ʈ ������
	: currentIndex_(0)
	, currentWorm_(nullptr)
	, cameraMoveSpeed_(10.f)
	, wormIndex_(MAX_WORM_COUNT)
	, prevwormIndex_(MAX_WORM_COUNT)
	, IsCameraMove_(true)
{

}

GameController::~GameController() // default destructer ����Ʈ �Ҹ���
{

}

void GameController::Start()
{
	if (false == GameEngineInput::GetInst().IsKey("Up"))
	{
		GameEngineInput::GetInst().CreateKey("Up", VK_UP);
	}

	if (false == GameEngineInput::GetInst().IsKey("Down"))
	{
		GameEngineInput::GetInst().CreateKey("Down", VK_DOWN);
	}

	if (false == GameEngineInput::GetInst().IsKey("Left"))
	{
		GameEngineInput::GetInst().CreateKey("Left", VK_LEFT);
	}

	if (false == GameEngineInput::GetInst().IsKey("Right"))
	{
		GameEngineInput::GetInst().CreateKey("Right", VK_RIGHT);
	}

	if (false == GameEngineInput::GetInst().IsKey("CameraFocus"))
	{
		GameEngineInput::GetInst().CreateKey("CameraFocus", 0x31);
	}

	// UI
	if (false == GameEngineInput::GetInst().IsKey("WeaponSheet"))
	{
		GameEngineInput::GetInst().CreateKey("WeaponSheet", VK_RBUTTON);
	}
}

void GameController::UpdateBefore()
{
}

void GameController::Update()
{
	if (true == GameEngineInput::GetInst().IsPress("Up"))
	{
		GetLevel()->SetCamMove(float4::UP * cameraMoveSpeed_);
	}

	if (true == GameEngineInput::GetInst().IsPress("Down"))
	{
		GetLevel()->SetCamMove(float4::DOWN * cameraMoveSpeed_);
	}

	if (true == GameEngineInput::GetInst().IsPress("Left"))
	{
		GetLevel()->SetCamMove(float4::LEFT * cameraMoveSpeed_);
	}

	if (true == GameEngineInput::GetInst().IsPress("Right"))
	{
		GetLevel()->SetCamMove(float4::RIGHT * cameraMoveSpeed_);
	}

	if (true == GameEngineInput::GetInst().IsDown("CameraFocus"))
	{
		prevwormIndex_ = wormIndex_;

		++wormIndex_;

		if (true == IsCameraMove_)
		{
			wormIndex_ = 0;
			IsCameraMove_ = false;
		}	

		if (false == IsCameraMove_)
		{
			for (int i = 0; i < MAX_WORM_COUNT; i++)
			{
				if (i == wormIndex_)
				{
					wormList_[wormIndex_]->SetFocus(true);
				}
				else
				{
					wormList_[i]->SetFocus(false);
				}
			}
		}
	}

	if (wormIndex_ == MAX_WORM_COUNT)
	{
		IsCameraMove_ = true;

		for (int i = 0; i < MAX_WORM_COUNT; ++i)
		{
			wormList_[i]->SetFocus(false);
		}
	}
	else
	{
		GetLevel()->SetCamPos(wormList_[wormIndex_]->GetPos() - GameEngineWindow::GetInst().GetSize().halffloat4());
	}

	// UI
	if (true == GameEngineInput::GetInst().IsDown("WeaponSheet"))
	{
		if (wormIndex_ != MAX_WORM_COUNT)
		{
			// ���� �÷��̾�� �����÷��̾ �޶�����
			// �����÷��̾��� ����â�� ��Ȱ��ȭ�ǰ�
			// ���� �÷��̾��� ����â�� Ȱ��ȭ�ȴ�.
			if (prevwormIndex_ != wormIndex_ && prevwormIndex_ != MAX_WORM_COUNT &&
				true == wormList_[prevwormIndex_]->GetCurUIController()->GetCurWeaponSheet()->IsActive())
			{
				wormList_[prevwormIndex_]->GetCurUIController()->GetCurWeaponSheet()->WeaponSheetActive();
				wormList_[wormIndex_]->GetCurUIController()->GetCurWeaponSheet()->WeaponSheetActive();

				prevwormIndex_ = wormIndex_;
			}
			else
			{
				wormList_[wormIndex_]->GetCurUIController()->GetCurWeaponSheet()->WeaponSheetActive();
			}
		}
	}
}

void GameController::UpdateAfter()
{
}

void GameController::Render()
{
}

void GameController::CreateWorm(const float _minX, const float _maxX)
{
	if (wormList_.size() >= MAX_WORM_COUNT)
	{
		GameEngineDebug::MsgBoxError("�ִ� ������ ������ �ʰ��Ͽ����ϴ�.");
		return;
	}

	GameEngineMath::Random randomGenerator;
	std::string name = "Worm";
	name += std::to_string(currentIndex_++);
	Worm* newWorm = parentLevel_->CreateActor<Worm>(name);
	randomFloatContainer_ = randomGenerator.RandomFloat(_minX, _maxX); // ���� ������ ��ǥ�� ����

	std::vector<float>::iterator startIter = xPosList_.begin();
	std::vector<float>::iterator endIter = xPosList_.end();
	for (; startIter != endIter; startIter++)
	{
		if (randomFloatContainer_ >= *startIter - 50.0f && randomFloatContainer_ <= *startIter + 50.0f)
		{
			randomFloatContainer_ = randomGenerator.RandomFloat(_minX, _maxX);
		}
	}
	
	newWorm->SetPos({ randomFloatContainer_ , -500.0f });
	newWorm->SetFocus(false);
	wormList_.push_back(newWorm);
	xPosList_.push_back(randomFloatContainer_);
}

void GameController::CreateWormUI()
{
	size_t wormcnt = wormList_.size();
	for (size_t i = 0; i < wormcnt; ++i)
	{
		std::string Name = wormList_[i]->GetName();
		Name += "_UI";

		// UI�����ڻ���
		UIController* CurUIController = parentLevel_->CreateActor<UIController>(Name);
		CurUIController->SetCurPlayer(wormList_[i]);

		// �÷��̾�� UIController ����
		wormList_[i]->SetUIController(CurUIController);
		wormList_[i]->GetCurUIController()->GetCurWeaponSheet()->SetParentController(wormList_[i]->GetCurUIController());

		// �ʱ� ������ �������
		std::vector<eItemList> ItemListTest;
		ItemListTest.resize(2);
		ItemListTest[0] = eItemList::WEAPON_BAZOOKA;
		ItemListTest[1] = eItemList::WEAPON_HOMINGMISSILE;
		CurUIController->CreateWeaponList(ItemListTest);				// �÷��̾ ó�� �������ִ� �����۸��(��������)

		// 
		CurUIController->AddWeapon(eItemList::WEAPON_AIRSTRIKE);		// �÷��̾ ��Ϳ�����Ʈ ȹ������ ���� ����ȹ��� ȣ��(���ο���߰� �Ǵ� �������ⰳ������)
		//CurUIController->UseWeapon(eItemList::WEAPON_AIRSTRIKE);		// �÷��̾ ������������ ȣ��(�������ִ� ���ⰳ������)
		ItemListTest.clear();
	}
}
