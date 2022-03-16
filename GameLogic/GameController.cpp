#include "GameController.h"

#include <GameEngineMath.h>
#include <GameEngineWindow.h>
#include <GameEngineLevel.h>
#include <GameEngineInput.h>
#include <GameEngineDebugExtension.h>

#include "GameOptionInfo.h"
#include "Worm.h"
#include "DrumActor.h"
#include "UIController.h"
#include "WeaponSheet.h"
#include "WeaponIcon.h"
#include "Weapon.h"
#include "BottomStateUI.h"
#include "WormTopStateUI.h"

#include "WaterLevel.h"
#include "WaterWave.h"
#include "UnderWater.h"

#include "WormArrow.h"
#include "WormHPBlankWindow.h"
#include "BottomHealthBar.h"
#include "BottomFlag.h"
#include "BottomNameTag.h"
#include "WormName.h"
#include "TimerBlankWindow.h"
#include "TimerDigit.h"
#include "WormHPNumber.h"
#include "TopHPText.h"

#include "WindBarBlank.h"
#include "WindBar.h"
#include "WindBarHider.h"
#include "BackgroundScatter.h"
#include "WindController.h"
#include "Cloud.h"

#include "PlayLevel.h"

std::vector<BottomStateUI*> GameController::PlayerHPBarList;
std::queue<BottomStateUI*> GameController::PlayerHPBarSortQueue;
bool GameController::BottomUISortStart = false;
bool GameController::BottomUISortEnd = false;
bool GameController::BottomUIDeath = false;
int GameController::SortStartIndex = -1;
int GameController::SortEndIndex = -1;
float GameController::SortDeltaTime = 0.f;

GameController::GameController() // default constructer 디폴트 생성자
	: currentIndex_(0)
	, currentWorm_(nullptr)
	, prevWorm_(nullptr)
	, cameraMoveSpeed_(10.f)
	, wormIndex_(0)
	, PetroleumCount_(0)
	, prevwormIndex_(MAX_WORM_COUNT)
	, IsCameraMove_(false)
	, WormDeathReady_(false)
	, WormDeathProgressing_(false)
	, cameraPos_(0.f, 0.f)
	, state_(this)
	, currentTurnTime_(0.0f)
	, wormXPosContainer_(0.0f)
	, WormDeathWaitingTime_(0.0f)
	, WaterLevel_(nullptr)
	, settementTime_(0.0f)
	, windController_(nullptr)
	, CurDeathWorm_(nullptr)
	, NextDeathWorm_(nullptr)
{

}

GameController::~GameController() // default destructer 디폴트 소멸자
{

}

void GameController::Start()
{
	WindInit();
	initState();
	MakeWaterLevel();

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
		GameEngineInput::GetInst().CreateKey("TestKey", 0xC0);
	}

	// UI
	if (false == GameEngineInput::GetInst().IsKey("WeaponSheet"))
	{
		GameEngineInput::GetInst().CreateKey("WeaponSheet", VK_RBUTTON);
	}
}

void GameController::UpdateBefore()
{
	// UI
	if (true == GameEngineInput::GetInst().IsDown("WeaponSheet"))
	{
		wormList_[wormIndex_]->GetCurUIController()->GetCurWeaponSheet()->WeaponSheetActive();
		prevwormIndex_ = wormIndex_;
	}

	//if (!PlayerHPBarSortQueue.empty() && false == BottomUISortStart)
	//{
	//	// 선입선출의 개념을 활용하여 그다음 정렬 항목을 빼오며
	//	BottomStateUI* QueueState = PlayerHPBarSortQueue.front();

	//	// 정렬시작하므로 큐에서 제거
	//	PlayerHPBarSortQueue.pop();

	//	// 정렬 시작
	//	BottomStateHPBarSortCheck(QueueState);
	//}
}

void GameController::Update()
{
	// 남은 플레이어가 1명이므로 승리로 판단
	// 남은 플레이어가 없다면 무승부로 판단
	if (1 == wormList_.size())
	{
		// 남은플레이어를 승리상태로 전환
		wormList_[0]->ChangeState("Win");
		return;
	}
	else if (0 == wormList_.size())
	{
		// 남은 플레이어가 없으므로 FadeIn/Out처리 후 엔딩씬으로 전환
		int a = 0;

		return;
	}

	state_.Update();

	// 플레이어가 사망해서 UI가 지워진상태라면
	// 나머지 하단바에 대한 위치 재조정
	//if (true == BottomUISortEnd)
	//{
	//	BottomUISortEnd = false;

	//	// 여기서 현재 모든 플레이어가 정렬이 종료되었으므로
	//	// 모든 플레이어의 체력상태를 체크한다.
	//	int Size = static_cast<int>(PlayerHPBarList.size());
	//	for (int i = 0; i < Size; ++i)
	//	{
	//		if (0 >= PlayerHPBarList[i]->GetParentWorm()->GetCurHP())
	//		{
	//			if (true == PlayerHPBarList[i]->GetParentWorm()->UIControllerDeath())
	//			{
	//				PlayerHPBarList.erase(PlayerHPBarList.begin() + i);
	//				Size = static_cast<int>(PlayerHPBarList.size());

	//				for (int k = 0; k < Size; ++k)
	//				{
	//					PlayerHPBarList[k]->PositionReadjustment();
	//				}

	//				BottomUIDeath = true;
	//			}
	//		}
	//	}
	//}

	//if (true == BottomUIDeath)
	//{
	//	int size = wormList_.size();
	//	for (int i = 0; i < size; ++i)
	//	{
	//		if (wormList_[i]->GetDeathState() == Worm::DeathState::DeathEnd)
	//		{
	//			if (wormList_[i] == currentWorm_)
	//			{
	//				currentWorm_ = nullptr;
	//			}
	//			wormList_[i]->WormDeath();
	//			wormList_.erase(wormList_.begin() + i);

	//			size = wormList_.size();
	//		}
	//	}
	//	BottomUIDeath = false;
	//	return;
	//}

	//TODO : 죽을 녀석 찾아다가 포커싱 해줘야함

	GameEngineDebugExtension::PrintDebugWindowText("wormIndex : ", wormIndex_);
	GameEngineDebugExtension::PrintDebugWindowText("wormListSize : ", wormList_.size());
}

void GameController::UpdateAfter()
{
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
	currentWorm_ = wormList_[0];
}

void GameController::CreateWormUI()
{
	size_t wormcnt = wormList_.size();
	for (int i = 0; i < wormcnt; ++i)
	{
		std::string Name = wormList_[i]->GetName();
		Name += "_UI";

		// UI관리자생성
		UIController* CurUIController = parentLevel_->CreateActor<UIController>(Name);
		CurUIController->SetCurPlayer(wormList_[i]);

		// 플레이어당 UIController 지정
		wormList_[i]->SetUIController(CurUIController);
		wormList_[i]->GetCurUIController()->GetCurWeaponSheet()->SetParentController(wormList_[i]->GetCurUIController());

		// 플레이어당 상단 상태 UI
		wormList_[i]->GetCurUIController()->GetCurTopState()->SetParentWorm(wormList_[i]);
		wormList_[i]->GetCurUIController()->GetCurTopState()->SetParentUIController(CurUIController);
		wormList_[i]->GetCurUIController()->GetCurTopState()->GameStartInit(static_cast<int>(i));

		// 플레이어당 턴 타이머 UI 지정
		wormList_[i]->GetCurUIController()->GetCurTimerWindow()->RenderColorInit(static_cast<int>(i));
		wormList_[i]->GetCurUIController()->GetCurTimerWindow()->SetParentWorm(wormList_[i]);
		wormList_[i]->GetCurUIController()->GetCurTimerDigitTen()->SetParentWorm(wormList_[i]);
		wormList_[i]->GetCurUIController()->GetCurTimerDigit()->SetParentWorm(wormList_[i]);

		// 플레이어당 체력표시텍스트 UI 지정
		//wormList_[i]->GetCurUIController()->GetCurHPNumberHundred()->SetParentWorm(wormList_[i]);
		//wormList_[i]->GetCurUIController()->GetCurHPNumberHundred()->ColorInit(static_cast<int>(i));
		//wormList_[i]->GetCurUIController()->GetCurHPNumberHundred()->SetDigitToHundred();
		//wormList_[i]->GetCurUIController()->GetCurHPNumberHundred()->HPInit();
		//wormList_[i]->GetCurUIController()->GetCurHPNumberTen()->SetParentWorm(wormList_[i]);
		//wormList_[i]->GetCurUIController()->GetCurHPNumberTen()->ColorInit(static_cast<int>(i));
		//wormList_[i]->GetCurUIController()->GetCurHPNumberTen()->SetDigitToTen();
		//wormList_[i]->GetCurUIController()->GetCurHPNumberTen()->HPInit();
		//wormList_[i]->GetCurUIController()->GetCurHPNumber()->SetParentWorm(wormList_[i]);
		//wormList_[i]->GetCurUIController()->GetCurHPNumber()->ColorInit(static_cast<int>(i));
		//wormList_[i]->GetCurUIController()->GetCurHPNumber()->HPInit();

		// 플레이어당 무기창 지정 및 활성화 무기 지정
		std::string SheetName = wormList_[i]->GetName();
		SheetName += "_WeaponSheet";
		wormList_[i]->GetCurUIController()->GetCurWeaponSheet()->SetName(SheetName);

		// 초기 아이템 목록지정
		std::vector<eItemList> ItemListTest;
		ItemListTest.resize(11);
		ItemListTest[0] = eItemList::WEAPON_BAZOOKA;
		ItemListTest[1] = eItemList::WEAPON_HOMINGMISSILE;
		ItemListTest[2] = eItemList::WEAPON_FIREPUNCH;
		ItemListTest[3] = eItemList::WEAPON_UZI;
		ItemListTest[4] = eItemList::WEAPON_BATTLEAXE;
		ItemListTest[5] = eItemList::WEAPON_GIRDER;
		ItemListTest[6] = eItemList::WEAPON_SHEEP;
		ItemListTest[7] = eItemList::WEAPON_SUPERSHEEP;
		ItemListTest[8] = eItemList::WEAPON_BLOWTORCH;
		ItemListTest[9] = eItemList::WEAPON_PNEUMATICDRILL;
		ItemListTest[10] = eItemList::WEAPON_AIRSTRIKE;
		CurUIController->CreateWeaponList(ItemListTest);				// 플레이어가 처음 가지고있는 아이템목록(최초지정)

		// 무기창 기능 참고용
		//CurUIController->AddWeapon(eItemList::WEAPON_AIRSTRIKE);		// 플레이어가 기믹오브젝트 획득으로 인한 무기획득시 호출(새로운무기추가 또는 기존무기개수증가)
		//CurUIController->UseWeapon(eItemList::WEAPON_AIRSTRIKE);		// 플레이어가 무기사용했을대 호출(가지고있는 무기개수감수)
		ItemListTest.clear();

		// 플레이어당 하단 상태 UI
		wormList_[i]->GetCurUIController()->GetCurBottomState()->SetParentWorm(wormList_[i]);
		wormList_[i]->GetCurUIController()->GetCurBottomState()->SetParentUIController(CurUIController);
		wormList_[i]->GetCurUIController()->GetCurBottomState()->GameStartInit(static_cast<int>(i));

		// 플레이어 하단 상태바관련 관리목록에 추가
		PlayerHPBarList.push_back(wormList_[i]->GetCurUIController()->GetCurBottomState());
	}
}

void GameController::CreateDrum(const float _minX, const float _maxX)
{
	GameEngineMath::Random randomGenerator;
	DrumActor* newDrum = parentLevel_->CreateActor<DrumActor>();
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

	newDrum->SetPos({ wormXPosContainer_ , -500.0f });
}

void GameController::SetFocusOnlyOneWorm(Worm* _Worm)
{
	for (int i = 0; i < wormList_.size(); ++i)
	{
		if (_Worm == wormList_[i])
		{
			wormList_[i]->SetFocus(true);
		}
		else
		{
			wormList_[i]->SetFocus(false);
		}
	}
}

void GameController::SetFocusOnlyOneWorm(int _WormIndex)
{
	for (int i = 0; i < wormList_.size(); ++i)
	{
		if (_WormIndex == i)
		{
			wormList_[i]->SetFocus(true);
		}
		else
		{
			wormList_[i]->SetFocus(false);
		}
	}
}

void GameController::SetCurrentWorm(int _WormIndex)
{
	currentWorm_ = wormList_[_WormIndex];
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

	return currentWorm_;
}

void GameController::initState()
{
	state_.CreateState("NextWorm", &GameController::startNextWorm, &GameController::updateNextWorm);
	state_.CreateState("Action", &GameController::startAction, &GameController::updateAction);
	state_.CreateState("ActionEnd", &GameController::startActionEnd, &GameController::updateActionEnd);
	state_.CreateState("Settlement", &GameController::startSettlement, &GameController::updateSettlement);
	state_.CreateState("DeathPhase", &GameController::startDeathPhase, &GameController::updateDeathPhase);
	state_.CreateState("Death", &GameController::startDeath, &GameController::updateDeath);
	state_.CreateState("Victory", &GameController::startVictory, &GameController::updateVictory);
	state_.CreateState("ItemDrop", &GameController::startItemDrop, &GameController::updateItemDrop);

	state_.ChangeState("NextWorm");
}

StateInfo GameController::startNextWorm(StateInfo _state)
{
	GameEngineSoundManager::GetInstance().PlaySoundByName("YESSIR.WAV");

	RandomTurnWind();

	for (size_t i = 0; i < wormList_.size(); i++)
	{
		wormList_[i]->ResetisDamaged();
	}

	return "";
}

StateInfo GameController::updateNextWorm(StateInfo _state)
{
	if (currentWorm_ == nullptr)
	{
		//TODO : 이부분 수정이 필요해 보임
		//6마리 웜을 순차적으로 죽이고 마지막 1마리만 남았을때 UpdateAfter에서 문제가 발생했음, 
		//wormlist_ 에는 [0]만 남았는데 인덱스가 1인경우
		// 그냥 웜인덱스 시스템을 없애고 웜 진행 순서를 리스트로 구현해 보는건 어떨까 함

		prevwormIndex_ = wormIndex_;

		++wormIndex_;

		if (wormIndex_ == wormList_.size())
		{
			wormIndex_ = 0;
		}

		SetFocusOnlyOneWorm(wormIndex_);
		SetCurrentWorm(wormIndex_);

		IsCameraMove_ = false;
		return "";
	}

	currentWorm_->AddActionToken(1);

	// 대기실 턴타임셋팅에 따라 턴타임이 달라짐 - 220207 SJH 수정
	currentTurnTime_ = GameOptionInfo::TernTime;
	//currentTurnTime_ = DEFAULT_TURN_TIME;
	return "Action";
}

StateInfo GameController::startAction(StateInfo _state)
{
	return StateInfo();
}

StateInfo GameController::updateAction(StateInfo _state)
{

	currentTurnTime_ -= GameEngineTime::GetInst().GetDeltaTime();
	// 타이머 갱신을 해 줘야하는 부분
	currentWorm_->GetCurUIController()->GetCurTimerDigitTen()->SetTenDigitTime(currentTurnTime_);
	currentWorm_->GetCurUIController()->GetCurTimerDigit()->SetDigitTime(currentTurnTime_);

	if (GameEngineInput::GetInst().IsDown("TestKey"))
	{
		currentWorm_->SubtractActionToken(1);

		// 강제전환으로인한 무기창 및 무기아이콘 비활성화
		currentWorm_->GetCurUIController()->GetCurWeaponSheet()->WeaponSheetTernOff();

		currentTurnTime_ = 0.0f;
	}

	if (currentTurnTime_ < 0 || 0 == currentWorm_->GetActionTokenCount())
	{
		// 턴시간 초과 or 토큰 소진으로 인한 플레이어 전환이 발생하므로 이곳에서
		// 무기창 비활성이 된다.
		currentWorm_->GetCurUIController()->GetCurWeaponSheet()->WeaponSheetTernOff();

		// 라운타임 초과 및 플레이어 턴초과시 물높이 상승
		if (nullptr != WaterLevel_)
		{
			WaterLevel_->TernChangeWaterLevelUp();
		}

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
#ifdef _DEBUG
	if (PetroleumCount_ < 0)
		GameEngineDebug::AssertFalse();
#endif // _DEBUG
	//TODO : 모든 웜들의 행동,드럼통 기름 등등이 움직임이 모두 멈춘것을 확인하면 다음으로 넘김
	// 현재 활성중인 드럼통 기름의 숫자를 체크하고 다음으로 넘김, 
	// 다음으로 넘어갔는데 중간에 드럼통이 터지는 일이 발생하면 존나 골치아플듯
	if (PetroleumCount_ == 0)
	{
		currentWorm_ = nullptr;

		return "Settlement";
	}

	return StateInfo();
}

StateInfo GameController::startSettlement(StateInfo _state)
{
	for (size_t i = 0; i < wormList_.size(); i++)
	{
		if (true == wormList_[i]->isDamagedThisTurn())
		{
			wormList_[i]->GetCurUIController()->GetCurTopState()->SetTextChangeRequest();
		}
	}

	return StateInfo();
}

StateInfo GameController::updateSettlement(StateInfo _state)
{


	// Worm 사망절차
	// 1.   Worm이 사망상태로 넘어가며 애니메이션을 실행한다
	// 2.   Worm이 사망애니메이션종료후 사망한 Worm위치에 묘지액터가 생성 된다. (기존은 애니메이션종료후 바로사망)
	//      -. 문제점 : 
	//                 1) 사망처리중 WORM이 데미지를 입으면 사망상태에서 피격상태로 넘어간다.
	//                     -. Worm이 사망애니메이션을 실행하게되면 충돌체는 제거되어야한다.(HitBoxCollision_ 얘제거해야함)
	//                     -. 묘지액터가 생성하면서 hitbox collision을 생성해서 피격처리해야할듯...
	//                 2) 사망애니메이션이 끝나자마자 WORM을 죽이게되면 UI처리에서 곤란해진다.

	// 결론 : WORM사망애니메이션 실행 -> 종료 -> 렌더링OFF 및 충돌체제거 -> 묘지액터생성(사망한플레이어의 위치)
	//        -> UI관련처리 -> 해당 Worm사망처리 및 UI관련 사망처리 -> GameController에서 관리하는 Worm목록갱신 -> 턴전환

	// Worm Tern전환 절차
	// 1. Worm이 한가지 동작을 실행 또는 턴타임초과시 턴전환 시작
	// 2. Worm과 Next Worm의 전환 중간과정에서 UI관련 처리시작
	// 3. UI관련 처리 완료 후 턴전환

	// 결론 : Cur Worm에서 Next Worm으로 턴전환시 UI관련처리 구간상태가 필요

	bool Damagethisturn = false;
	for (size_t i = 0; i < wormList_.size(); i++)
	{
		if (true == wormList_[i]->isDamagedThisTurn())
		{
			if (true == BottomUISortStart)
			{
				Damagethisturn = true;

				if (true == BottomStateHPBarSort())
				{
					wormList_[i]->ResetisDamaged();
				}
			}

			wormList_[i]->GetCurUIController()->GetCurTopState()->SetTextChangeRequest();

		}
	}

	if (Damagethisturn)
	{
		return StateInfo();
	}

	// if문이 왜걸려있나?
	if (true)
	{
		// 모든 웜이 사망처리가 끝나고 ui처리가 끝나면 턴전환 딜레이 계산
		settementTime_ += GameEngineTime::GetInst().GetDeltaTime();
	}

	////////////////////////// Worm Death 진행 ////////////////////////
	//1. 죽을 얘가 있는지 확인
	// Death를 진행시킬 worm

	//if (false == WormDeathReady_)
	//{		
	//	CurDeathWorm_ = NextDeathWorm_;
	//	
	//	NextDeathWorm_ = nullptr;

	//	for (int i = 0; i < wormList_.size(); ++i)
	//	{
	//		//if (true == wormList_[i]->GetDeathReady_())
	//		if ((wormList_[i]->GetDeathState() == Worm::DeathState::DeathReady))
	//		{
	//			WormDeathReady_ = true; //			(worm)의		Death를		준비중이다.
	//			WormDeathProgressing_ = true; //	(컨트롤러)가 Death상태	진행중이다.
	//			// 데미지를 입어 죽게될 worm은 GetDeathReady_()를 통해 bool 값을 전달한다.
	//			if (nullptr == CurDeathWorm_)
	//			{
	//				CurDeathWorm_ = wormList_[i];
	//				continue;
	//			}
	//			else if (nullptr == NextDeathWorm_)
	//			{
	//				NextDeathWorm_ = wormList_[i];
	//				break;
	//				// 1개체 죽음 완료후, 
	//				// 죽음이 완료된 worm은 wormList_에서 지워져서 들어와선 안됨
	//			}				
	//		}

	//		if((CurDeathWorm_ == nullptr) && (NextDeathWorm_ == nullptr))
	//		{
	//			WormDeathProgressing_ = false; // 죽음 리스트중 마지막 하나 남은 worm이 죽었다.
	//		}
	//	}

	//	//TODO :  Worm::DeathStart가 되어 에니메이션을 재생하고, 재생이 완료 후, bool DeathEnd가 된것을 인지하면
	//	// nextworm state로 넘어가고, 그 nextworm에 다음 죽게될 worm을 넘겨주어야함

	//	//worm의 죽음 상태 변화를 시작함 // worm의 대기상태와 GameController의 대기상태는 다름
	//	if (nullptr != CurDeathWorm_)
	//	{					
	//		CurDeathWorm_->SetDeathState(Worm::DeathState::DeathStart);
	//		//CurDeathWorm_->SetDeathReady(false);
	//		//CurDeathWorm_->SetDeathStart(true);
	//	}
	//}
	////다음 worm 죽이기까지 컨트롤러를 대기시킨다.
	//if (true == WormDeathReady_)
	//{
	//	WormDeathWaitingTime_ += GameEngineTime::GetInst().GetDeltaTime();

	//	if (WormDeathWaitingTime_ > 3.f) // 3초가 지나면 대기가 끝난다.
	//	{
	//		WormDeathReady_ = false; // 다시 다음 worm을 찾을 준비가 됬따.
	//		WormDeathWaitingTime_ = 0.f;
	//	
	//		//CurDeathWorm_ = NextDeathWorm_;
	//		//NextDeathWorm_ = nullptr;
	//		//SetFocusOnlyOneWorm(CurDeathWorm_);
	//		//대기가 끝남
	//	}
	//}
	//if (false == WormDeathProgressing_) // worm을 죽이는 중도 아니고, 죽일놈도 못찾았으면 다음 차레로 넘어가										// 다음 웜으로 넘겨준다.
	//{
	//	// 4.0f
	//	if (SETTLEMENT_TIME <= settementTime_)
	//	{
	//		settementTime_ = 0.0f;
	//		return "NextWorm";
	//	}
	//}


	std::vector<Worm*>::iterator startIter = wormList_.begin();

	while (startIter != wormList_.end())
	{
		Worm* currentWorm = *startIter;
		if (currentWorm->GetDeathState() == Worm::DeathState::DeathReady)
		{
			readyToDeathWorm_.push_back(currentWorm);
			startIter = wormList_.erase(startIter);
		}
		else
		{
			++startIter;
		}
	}

	CurDeathWorm_ = nullptr;
	return "DeathPhase";

	return StateInfo();
}

StateInfo GameController::startDeathPhase(StateInfo _state) // 
{
	return StateInfo();
}

StateInfo GameController::updateDeathPhase(StateInfo _state)
{
	if (0 < readyToDeathWorm_.size())
	{
		CurDeathWorm_ = readyToDeathWorm_.front();
		CurDeathWorm_->SetDeathState(Worm::DeathState::DeathStart);
		CurDeathWorm_->ChangeState("Death");
		readyToDeathWorm_.pop_front();

		return "Death";
	}

	return "NextWorm";
}


StateInfo GameController::startDeath(StateInfo _state)
{
	return StateInfo();
}

StateInfo GameController::updateDeath(StateInfo _state)
{
	if (CurDeathWorm_ != nullptr && CurDeathWorm_->GetDeathState() == Worm::DeathState::DeathEnd)
	{
		auto uiStartIter = PlayerHPBarList.begin();

		while (uiStartIter != PlayerHPBarList.end())
		{
			if ((*uiStartIter)->GetParentWorm() == CurDeathWorm_)
			{
				uiStartIter = PlayerHPBarList.erase(uiStartIter);
			}
			else
			{
				++uiStartIter;
			}
		}
		CurDeathWorm_->WormDeath();
		CurDeathWorm_ = nullptr;
		if (0 < readyToDeathWorm_.size())
		{
			BottomUISortStart = true;
			return "DeathPhase";
		}
		else
		{
			return "NextWorm";
		}
	}

	return StateInfo();
}

StateInfo GameController::startVictory(StateInfo _state)
{
	// 빅토리 스테이트에선 이론상 웜리스트에 웜은 한 마리밖에 없습니다.
	// 유일한 웜에게 카메라가 포커싱되며 해당 웜은 Win 스테이트를 실행합니다.
	return StateInfo();
}

StateInfo GameController::updateVictory(StateInfo _state)
{
	for (size_t i = 0; i < wormList_.size(); i++)
	{
		wormList_[i]->ChangeState("Win");
	}

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

const float GameController::GetWaterLevel()
{
	return WaterLevel_->GetWaterLevel();
}

void GameController::MakeWaterLevel(float _WaterLevel)
{
	WaterLevel_ = GetLevel()->CreateActor<WaterLevel>("WaterLevel"); // 모든 파도 actor 그룹화
	WaterLevel_->SetwaterLevel(_WaterLevel);

	WaterWave* WaterWaveactor = GetLevel()->CreateActor<WaterWave>("WaterWave1");
	WaterWaveactor->SetRenderOrder((int)RenderOrder::WaterLevel_Back);
	WaterWaveactor->SetPos(float4(0.f, _WaterLevel, 0.f));
	WaterLevel_->Waterlist.push_back(WaterWaveactor);

	WaterWaveactor = GetLevel()->CreateActor<WaterWave>("WaterWave2");
	WaterWaveactor->SetRenderOrder((int)RenderOrder::WaterLevel_Back);
	WaterWaveactor->SetPos(float4(0.f, _WaterLevel + 30.f, 0.f));
	WaterWaveactor->SetAnimationCurrentFrame(2);
	WaterLevel_->Waterlist.push_back(WaterWaveactor);

	WaterWaveactor = GetLevel()->CreateActor<WaterWave>("WaterWave3");
	WaterWaveactor->SetRenderOrder((int)RenderOrder::WaterLevel_Front);
	WaterWaveactor->SetPos(float4(0.f, _WaterLevel + 60.f, 0.f));
	WaterWaveactor->SetAnimationCurrentFrame(4);
	WaterLevel_->Waterlist.push_back(WaterWaveactor);

	WaterWaveactor = GetLevel()->CreateActor<WaterWave>("WaterWave4");
	WaterWaveactor->SetRenderOrder((int)RenderOrder::WaterLevel_Front);
	WaterWaveactor->SetPos(float4(0.f, _WaterLevel + 90.f, 0.f));
	WaterWaveactor->SetAnimationCurrentFrame(6);
	WaterLevel_->Waterlist.push_back(WaterWaveactor);

	WaterWaveactor = GetLevel()->CreateActor<WaterWave>("WaterWave5");
	WaterWaveactor->SetRenderOrder((int)RenderOrder::WaterLevel_Front);
	WaterWaveactor->SetPos(float4(0.f, _WaterLevel + 120.f, 0.f));
	WaterWaveactor->SetAnimationCurrentFrame(8);
	WaterLevel_->Waterlist.push_back(WaterWaveactor);

	UnderWater* UnderWaterActor = GetLevel()->CreateActor<UnderWater>("UnderWater");
	UnderWaterActor->SetPos(float4(0.f, _WaterLevel + 680.f, 0.f));
	UnderWaterActor->SetRenderOrder((int)RenderOrder::WaterLevel_Front);
	WaterLevel_->Waterlist.push_back(UnderWaterActor);

	WaterWaveactor = GetLevel()->CreateActor<WaterWave>("WaterWave6");
	WaterWaveactor->SetRenderOrder((int)RenderOrder::WaterLevel_Back);
	WaterWaveactor->SetPos(float4(2560.f, _WaterLevel, 0.f));
	WaterLevel_->Waterlist.push_back(WaterWaveactor);

	WaterWaveactor = GetLevel()->CreateActor<WaterWave>("WaterWave7");
	WaterWaveactor->SetRenderOrder((int)RenderOrder::WaterLevel_Back);
	WaterWaveactor->SetPos(float4(2560.f, _WaterLevel + 30.f, 0.f));
	WaterWaveactor->SetAnimationCurrentFrame(2);
	WaterLevel_->Waterlist.push_back(WaterWaveactor);

	WaterWaveactor = GetLevel()->CreateActor<WaterWave>("WaterWave8");
	WaterWaveactor->SetRenderOrder((int)RenderOrder::WaterLevel_Front);
	WaterWaveactor->SetPos(float4(2560.f, _WaterLevel + 60.f, 0.f));
	WaterWaveactor->SetAnimationCurrentFrame(4);
	WaterLevel_->Waterlist.push_back(WaterWaveactor);

	WaterWaveactor = GetLevel()->CreateActor<WaterWave>("WaterWave9");
	WaterWaveactor->SetRenderOrder((int)RenderOrder::WaterLevel_Front);
	WaterWaveactor->SetPos(float4(2560.f, _WaterLevel + 90.f, 0.f));
	WaterWaveactor->SetAnimationCurrentFrame(6);
	WaterLevel_->Waterlist.push_back(WaterWaveactor);

	WaterWaveactor = GetLevel()->CreateActor<WaterWave>("WaterWave10");
	WaterWaveactor->SetRenderOrder((int)RenderOrder::WaterLevel_Front);
	WaterWaveactor->SetPos(float4(2560.f, _WaterLevel + 120.f, 0.f));
	WaterWaveactor->SetAnimationCurrentFrame(8);
	WaterLevel_->Waterlist.push_back(WaterWaveactor);

	UnderWaterActor = GetLevel()->CreateActor<UnderWater>("UnderWater2");
	UnderWaterActor->SetPos(float4(2560.f, _WaterLevel + 680.f, 0.f));
	UnderWaterActor->SetRenderOrder((int)RenderOrder::WaterLevel_Front);
	WaterLevel_->Waterlist.push_back(UnderWaterActor);
}

void GameController::BottomStateHPBarSortCheck(BottomStateUI* _CurUI)
{
	// 현재 이미 다른 플레이어 Bottom HPBar가 정렬중이라면
	// 대기큐에 해당 플레이어UI저장
	if (true == BottomUISortStart)
	{
		PlayerHPBarSortQueue.push(_CurUI);
	}
	else
	{
		// 현재 플레이어의 체력에 따라 정렬 시작
		int Size = static_cast<int>(PlayerHPBarList.size());
		for (int i = 0; i < Size; ++i)
		{
			if (PlayerHPBarList[i] == _CurUI)
			{
				SortStartIndex = i;
				break;
			}
		}

		for (int i = 0; i < Size; ++i)
		{
			if (1 == Size && PlayerHPBarList[SortStartIndex] == PlayerHPBarList[i])
			{
				// 플레이어가 이미 한마리이므로
				SortEndIndex = SortStartIndex;
				continue;
			}

			if (PlayerHPBarList[i] == _CurUI)
			{
				continue;
			}

			if (SortStartIndex + 1 == Size)
			{
				continue;
			}

			if (PlayerHPBarList[SortStartIndex]->GetCurHP() < PlayerHPBarList[i]->GetCurHP())
			{
				BottomUISortStart = true;
				SortEndIndex = i;
			}
			else if (SortStartIndex == Size - 1) // 이미 가장 낮은 체력의 플레이어
			{
				BottomUISortStart = false;
				SortEndIndex = SortStartIndex;
			}

			if (SortEndIndex < SortStartIndex)
			{
				SortEndIndex = SortStartIndex;
			}
		}
	}
}

bool GameController::BottomStateHPBarSort()
{
	SortDeltaTime += GameEngineTime::GetInst().GetDeltaTime();
	if (0.3f <= SortDeltaTime)
	{
		SortDeltaTime = 0.f;

		int Size = static_cast<int>(PlayerHPBarList.size());
		bool Flag = false;
		for (int i = SortStartIndex; i < SortStartIndex + 1; ++i)
		{
			// 정렬 종료후 정렬대기열에 정렬할 HPBar가 존재한다면
			// 해당 HPBar정렬 시작
			if (SortStartIndex == SortEndIndex && 1 != Size)
			{
				// 마지막 인덱스까지 정렬이 완료되었으면 Flag 해제
				BottomUISortStart = false;

				// 만약 현재 정렬이 종료되고 대기큐에 정렬하려는 플레이어가
				// 존재하지않다면 정렬 완전종료
				if (true == PlayerHPBarSortQueue.empty())
				{
					BottomUISortEnd = true;

					return true;
				}
			}

			for (int j = SortStartIndex + 1; j < Size; ++j)
			{
				if (PlayerHPBarList[i] == PlayerHPBarList[j])
				{
					continue;
				}

				if (PlayerHPBarList[i]->GetCurHP() < PlayerHPBarList[j]->GetCurHP())
				{
					// 실질적인 렌더링 위치를 변경하고
					float CurPlayerYPos = PlayerHPBarList[i]->GetBottomUIYPos();
					float ComparePlayerYPos = PlayerHPBarList[j]->GetBottomUIYPos();
					PlayerHPBarList[i]->SetBottomStateBarRenderPos(ComparePlayerYPos);
					PlayerHPBarList[j]->SetBottomStateBarRenderPos(CurPlayerYPos);

					// PlayerHPBarList_ 순서를 변경
					BottomStateUI* Temp = PlayerHPBarList[i];
					PlayerHPBarList[i] = PlayerHPBarList[j];
					PlayerHPBarList[j] = Temp;

					SortStartIndex = j;

					Flag = true;

					break;
				}
			}

			if (true == Flag)
			{
				Flag = false;
				break;
			}
		}
	}
	return false;
}

void GameController::CurPlayerDeathCheck()
{
	// Worm* 에서 GetDeathEnd로 받아오면 됨 // 이현

	// 현재플레이어가 죽었으므로
	//if (0 >= wormList_[currentIndex_]->GetCurHP())
	//{
		// 현재 플레이어의 상태바는 화면밖으로 내보내며
		// 현재 하단상태바 목록의 존재하는 상태들을 한칸내린다.

	//}

	// 이때 현재 플레이어 목록에 체력이 0인 플레이어가 존재한다면
	// 해당 플레이어도 상태바를 화면밖으로 내보내며 
	// 위의 플레이어목록을 재정렬한다.
	// 없다면 종료

}

void GameController::WindInit()
{
	windController_ = GetLevel()->CreateActor<WindController>();

	for (int i = 0; i < 70; i++)
	{
		BackgroundScatter* newScatter = GetLevel()->CreateActor<BackgroundScatter>();
		newScatter->SetParent(windController_);
		Cloud* newCloud = GetLevel()->CreateActor<Cloud>();
		newCloud->SetParent(windController_);
	}
	// 바람 UI 바 생성
	GetLevel()->CreateActor<WindBarBlank>();
	WindBar* windBar = GetLevel()->CreateActor<WindBar>();
	windBar->SetParentController(windController_);
	WindBarHider* windBarHider = GetLevel()->CreateActor<WindBarHider>();
	windBarHider->SetParentController(windController_);
}

void GameController::RandomTurnWind()
{
	int diceRoll = windDice_.RandomInt(1, 2);
	switch (diceRoll)
	{
	case 1:
		windController_->SetWind(WindDir::TOLEFT, 300.0f);
		break;
	case 2:
		windController_->SetWind(WindDir::TORIGHT, 300.0f);
		break;
	default:
		break;
	}
}