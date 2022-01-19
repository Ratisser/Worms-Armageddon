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

GameController::GameController() // default constructer 디폴트 생성자
	: currentIndex_(0)
	, currentWorm_(nullptr)
	, cameraMoveSpeed_(10.f)
	, wormIndex_(MAX_WORM_COUNT)
	, prevwormIndex_(MAX_WORM_COUNT)
	, IsCameraMove_(true)
{

}

GameController::~GameController() // default destructer 디폴트 소멸자
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
			// 이전 플레이어와 현재플레이어가 달라지면
			// 이전플레이어의 무기창이 비활성화되고
			// 현재 플레이어의 무기창이 활성화된다.
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
		GameEngineDebug::MsgBoxError("최대 지렁이 개수를 초과하였습니다.");
		return;
	}

	GameEngineMath::Random randomGenerator;
	std::string name = "Worm";
	name += std::to_string(currentIndex_++);
	Worm* newWorm = parentLevel_->CreateActor<Worm>(name);
	randomFloatContainer_ = randomGenerator.RandomFloat(_minX, _maxX); // 전에 생성한 좌표를 저장

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

		// UI관리자생성
		UIController* CurUIController = parentLevel_->CreateActor<UIController>(Name);
		CurUIController->SetCurPlayer(wormList_[i]);

		// 플레이어당 UIController 지정
		wormList_[i]->SetUIController(CurUIController);
		wormList_[i]->GetCurUIController()->GetCurWeaponSheet()->SetParentController(wormList_[i]->GetCurUIController());

		// 초기 아이템 목록지정
		std::vector<eItemList> ItemListTest;
		ItemListTest.resize(2);
		ItemListTest[0] = eItemList::WEAPON_BAZOOKA;
		ItemListTest[1] = eItemList::WEAPON_HOMINGMISSILE;
		CurUIController->CreateWeaponList(ItemListTest);				// 플레이어가 처음 가지고있는 아이템목록(최초지정)

		// 
		CurUIController->AddWeapon(eItemList::WEAPON_AIRSTRIKE);		// 플레이어가 기믹오브젝트 획득으로 인한 무기획득시 호출(새로운무기추가 또는 기존무기개수증가)
		//CurUIController->UseWeapon(eItemList::WEAPON_AIRSTRIKE);		// 플레이어가 무기사용했을대 호출(가지고있는 무기개수감수)
		ItemListTest.clear();
	}
}
