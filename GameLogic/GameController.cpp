#include "GameController.h"

#include <GameEngineMath.h>
#include <GameEngineWindow.h>
#include <GameEngineLevel.h>
#include <GameEngineInput.h>
#include <GameEngineDebugExtension.h>

#include "Worm.h"
#include "UIController.h"
#include "WeaponSheet.h"
#include "WeaponIcon.h"
#include "Weapon.h"
#include "WormArrow.h"
#include "BottomHealthBar.h"
#include "BottomFlag.h"
#include "BottomNameTag.h"
#include "WormName.h"

GameController::GameController() // default constructer 디폴트 생성자
	: currentIndex_(0)
	, currentWorm_(nullptr)
	, cameraMoveSpeed_(10.f)
	, wormIndex_(0)
	, prevwormIndex_(MAX_WORM_COUNT)
	, IsCameraMove_(false)
	, cameraPos_(0.f, 0.f)
	, state_(this)
	, currentTurnTime_(0.0f)
	, wormXPosContainer_(0.0f)
{

}

GameController::~GameController() // default destructer 디폴트 소멸자
{

}

void GameController::Start()
{
	initState();

	if (false == GameEngineInput::GetInst().IsKey("W"))
	{
		GameEngineInput::GetInst().CreateKey("W", 'W');
	}

	if (false == GameEngineInput::GetInst().IsKey("S"))
	{
		GameEngineInput::GetInst().CreateKey("S", 'S');
	}

	if (false == GameEngineInput::GetInst().IsKey("A"))
	{
		GameEngineInput::GetInst().CreateKey("A", 'A');
	}

	if (false == GameEngineInput::GetInst().IsKey("D"))
	{
		GameEngineInput::GetInst().CreateKey("D", 'D');
	}

	if (false == GameEngineInput::GetInst().IsKey("UpArrow"))
	{
		GameEngineInput::GetInst().CreateKey("UpArrow", VK_UP);
	}
	if (false == GameEngineInput::GetInst().IsKey("DownArrow"))
	{
		GameEngineInput::GetInst().CreateKey("DownArrow", VK_DOWN);
	}
	if (false == GameEngineInput::GetInst().IsKey("LeftArrow"))
	{
		GameEngineInput::GetInst().CreateKey("LeftArrow", VK_LEFT);
	}
	if (false == GameEngineInput::GetInst().IsKey("RightArrow"))
	{
		GameEngineInput::GetInst().CreateKey("RightArrow", VK_RIGHT);
	}

	// TODO : 테스트가 끝난 후 삭제
	if (false == GameEngineInput::GetInst().IsKey("TestKey"))
	{
		GameEngineInput::GetInst().CreateKey("TestKey", '1');
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

				// 마우스커서위치 강제셋팅
				//float4 MousePos = wormList_[wormIndex_]->GetCurUIController()->GetCurWeaponSheet()->GetSheetActivePos();
				//GameEngineWindow::GetInst().SetMousePos(MousePos.ix(), MousePos.iy());

				// 
				prevwormIndex_ = wormIndex_;
			}
			else
			{
				wormList_[wormIndex_]->GetCurUIController()->GetCurWeaponSheet()->WeaponSheetActive();

				// 마우스커서위치 강제셋팅
				//float4 MousePos = wormList_[wormIndex_]->GetCurUIController()->GetCurWeaponSheet()->GetSheetActivePos();
				//GameEngineWindow::GetInst().SetMousePos(MousePos.ix(), MousePos.iy());
			}
		}
	}

	state_.Update();

	GameEngineDebugExtension::PrintDebugWindowText("wormIndex : ", wormIndex_);
	GameEngineDebugExtension::PrintDebugWindowText("wormListSize : ", wormList_.size());
}

void GameController::UpdateAfter()
{
	if (true == GameEngineInput::GetInst().IsPress("W"))
	{
		GetLevel()->SetCamMove(float4::UP * cameraMoveSpeed_);
		IsCameraMove_ = true;
	}

	if (true == GameEngineInput::GetInst().IsPress("S"))
	{
		GetLevel()->SetCamMove(float4::DOWN * cameraMoveSpeed_);
		IsCameraMove_ = true;
	}

	if (true == GameEngineInput::GetInst().IsPress("A"))
	{
		GetLevel()->SetCamMove(float4::LEFT * cameraMoveSpeed_);
		IsCameraMove_ = true;
	}

	if (true == GameEngineInput::GetInst().IsPress("D"))
	{
		GetLevel()->SetCamMove(float4::RIGHT * cameraMoveSpeed_);
		IsCameraMove_ = true;
	}

	if (IsCameraMove_)
	{
		if (GameEngineInput::GetInst().IsPress("UpArrow"))
		{
			IsCameraMove_ = false;
		}
		if (GameEngineInput::GetInst().IsPress("DownArrow"))
		{
			IsCameraMove_ = false;
		}
		if (GameEngineInput::GetInst().IsPress("LeftArrow"))
		{
			IsCameraMove_ = false;
		}
		if (GameEngineInput::GetInst().IsPress("RightArrow"))
		{
			IsCameraMove_ = false;
		}
	}
	else
	{
		cameraPos_ = GetLevel()->GetCamPos();

		float4 cameraMovePos = wormList_[wormIndex_]->GetPos() - GameEngineWindow::GetInst().GetSize().halffloat4();
		float4 MoveVector = cameraMovePos - cameraPos_;

		GetLevel()->SetCamMove(MoveVector * 0.1f);
	}
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
	wormXPosContainer_ = randomGenerator.RandomFloat(_minX, _maxX); // 전에 생성한 좌표를 멤버변수에 저장

	std::vector<float>::iterator startIter = xPosList_.begin();
	std::vector<float>::iterator endIter = xPosList_.end();
	for (; startIter != endIter; startIter++)
	{
		if (wormXPosContainer_ >= *startIter - 25.0f && wormXPosContainer_ <= *startIter + 25.0f) // 
		{
			wormXPosContainer_ = randomGenerator.RandomFloat(_minX, _maxX);
			startIter = xPosList_.begin();
			continue;
		}
	}


	WormArrow* newArrow = GetLevel()->CreateActor<WormArrow>();
	newArrow->SetParent(newWorm);


	newWorm->SetPos({ wormXPosContainer_ , -500.0f });
	newWorm->SetFocus(false);


	wormList_.push_back(newWorm);
	xPosList_.push_back(wormXPosContainer_);
	wormList_[0]->SetFocus(true);
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

		std::string SheetName = wormList_[i]->GetName();
		SheetName += "_WeaponSheet";
		wormList_[i]->GetCurUIController()->GetCurWeaponSheet()->SetName(SheetName);

		wormList_[i]->GetCurUIController()->GetCurBottomHealthBar()->RenderColorInit(i);
		wormList_[i]->GetCurUIController()->GetCurBottomHealthBar()->StartPosInit(i);
		wormList_[i]->GetCurUIController()->GetCurBottomNameTag()->NameInit(i);
		wormList_[i]->GetCurUIController()->GetCurBottomNameTag()->StartPosInit(i);
		wormList_[i]->GetCurUIController()->GetCurBottomFlag()->NationInit(i);
		wormList_[i]->GetCurUIController()->GetCurBottomFlag()->StartPosInit(i);
		
		wormList_[i]->GetCurUIController()->GetCurWormName()->NameInit(i);
		wormList_[i]->GetCurUIController()->GetCurWormName()->SetParentWorm(wormList_[i]);

		// 초기 아이템 목록지정
		std::vector<eItemList> ItemListTest;
		ItemListTest.resize(13);
		ItemListTest[0] = eItemList::WEAPON_BAZOOKA;
		ItemListTest[1] = eItemList::WEAPON_HOMINGMISSILE;
		ItemListTest[2] = eItemList::WEAPON_FIREPUNCH;
		ItemListTest[3] = eItemList::WEAPON_MINE;
		ItemListTest[4] = eItemList::WEAPON_GRENADE;
		ItemListTest[5] = eItemList::WEAPON_CLUSTERBOMB;
		ItemListTest[6] = eItemList::WEAPON_UZI;
		ItemListTest[7] = eItemList::WEAPON_BATTLEAXE;
		ItemListTest[8] = eItemList::WEAPON_GIRDER;
		ItemListTest[9] = eItemList::WEAPON_SHEEP;
		ItemListTest[10] = eItemList::WEAPON_SUPERSHEEP;
		ItemListTest[11] = eItemList::WEAPON_BLOWTORCH;
		ItemListTest[12] = eItemList::WEAPON_PNEUMATICDRILL;
		CurUIController->CreateWeaponList(ItemListTest);				// 플레이어가 처음 가지고있는 아이템목록(최초지정)

		// 
		//CurUIController->AddWeapon(eItemList::WEAPON_AIRSTRIKE);		// 플레이어가 기믹오브젝트 획득으로 인한 무기획득시 호출(새로운무기추가 또는 기존무기개수증가)
		//CurUIController->UseWeapon(eItemList::WEAPON_AIRSTRIKE);		// 플레이어가 무기사용했을대 호출(가지고있는 무기개수감수)
		ItemListTest.clear();
	}
}

std::vector<Worm*> GameController::GetWormList() const
{
	return wormList_;
}

Worm* GameController::GetCurWorm() const
{
	if (wormIndex_ == MAX_WORM_COUNT)
	{
		return nullptr;
	}

	return wormList_[wormIndex_];
}

void GameController::initState()
{
	state_.CreateState("NextWorm", &GameController::startNextWorm, &GameController::updateNextWorm);
	state_.CreateState("Action", &GameController::startAction, &GameController::updateAction);
	state_.CreateState("ActionEnd", &GameController::startActionEnd, &GameController::updateActionEnd);
	state_.CreateState("Death", &GameController::startDeath, &GameController::updateDeath);
	state_.CreateState("Victory", &GameController::startVictory, &GameController::updateVictory);
	state_.CreateState("ItemDrop", &GameController::startItemDrop, &GameController::updateItemDrop);

	state_.ChangeState("NextWorm");
}

StateInfo GameController::startNextWorm(StateInfo _state)
{
	return "";
}

StateInfo GameController::updateNextWorm(StateInfo _state)
{
	if (currentWorm_ == nullptr)
	{
		prevwormIndex_ = wormIndex_;

		++wormIndex_;

		if (wormIndex_ == wormList_.size())
		{
			wormIndex_ = 0;

		}

		size_t size = wormList_.size();
		for (int i = 0; i < size; i++)
		{
			if (i == wormIndex_)
			{
				wormList_[wormIndex_]->SetFocus(true);
				currentWorm_ = wormList_[wormIndex_];

			}
			else
			{
				wormList_[i]->SetFocus(false);
			}
		}
		IsCameraMove_ = false;
		return "";
	}

	currentWorm_->AddActionToken(1);
	currentTurnTime_ = DEFAULT_TURN_TIME;
	return "Action";
}

StateInfo GameController::startAction(StateInfo _state)
{
	return StateInfo();
}

StateInfo GameController::updateAction(StateInfo _state)
{
	currentTurnTime_ -= GameEngineTime::GetInst().GetDeltaTime();

	if (GameEngineInput::GetInst().IsDown("TestKey"))
	{
		currentWorm_->SubtractActionToken(1);
		currentTurnTime_ = 0.0f;
	}

	if (currentTurnTime_ < 0)
	{
		return "ActionEnd";
	}
	return StateInfo();
}

StateInfo GameController::startActionEnd(StateInfo _state)
{
	currentWorm_->ClearActionToken();
	currentWorm_->ChangeState("WeaponOff");
	return StateInfo();
}

StateInfo GameController::updateActionEnd(StateInfo _state)
{
	currentWorm_ = nullptr;
	return "NextWorm";
}

StateInfo GameController::startDeath(StateInfo _state)
{
	return StateInfo();
}

StateInfo GameController::updateDeath(StateInfo _state)
{
	return StateInfo();
}

StateInfo GameController::startVictory(StateInfo _state)
{
	return StateInfo();
}

StateInfo GameController::updateVictory(StateInfo _state)
{
	return StateInfo();
}

StateInfo GameController::startItemDrop(StateInfo _state)
{
	return StateInfo();
}

StateInfo GameController::updateItemDrop(StateInfo _state)
{
	return StateInfo();
}
