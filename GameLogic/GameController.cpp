#include "GameController.h"

#include <GameEngineMath.h>
#include <GameEngineWindow.h>
#include <GameEngineLevel.h>
#include <GameEngineInput.h>
#include <GameEngineDebugExtension.h>

#include "GameOptionInfo.h"
#include "Worm.h"
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

std::vector<BottomStateUI*> GameController::PlayerHPBarList_;
bool GameController::BottomUISortStart = false;
int GameController::SortStartIndex = -1;
float GameController::SortDeltaTime = 0.f;

GameController::GameController() // default constructer 디폴트 생성자
	: currentIndex_(0)
	, currentWorm_(nullptr)
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
}

void GameController::Update()
{
	state_.Update();

	// 220218 SJH Test
	if (true == BottomUISortStart)
	{
		BottomStateHPBarSortStart();
	}

	//int size = wormList_.size();
	//auto iter0 = wormList_.begin();

	//for (int i = 0; i < size; ++i)
	//{	
		/*if (wormList_[i]->GetDeathEnd())
		{
			wormList_[i]->Death();
			wormList_.erase(wormList_.begin() + i);
		}*/
	//}
	//TODO : 웜 삭제 구현
	//}

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

		// 플레이어당 하단 상태 UI
		wormList_[i]->GetCurUIController()->GetCurBottomState()->SetParentWorm(wormList_[i]);
		wormList_[i]->GetCurUIController()->GetCurBottomState()->SetParentUIController(CurUIController);
		wormList_[i]->GetCurUIController()->GetCurBottomState()->GameStartInit(static_cast<int>(i));

		// 플레이어 하단 상태바관련 관리목록에 추가
		PlayerHPBarList_.push_back(wormList_[i]->GetCurUIController()->GetCurBottomState());

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
	}
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
	state_.CreateState("Settlement", &GameController::startSettlement, &GameController::updateSettlement);
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
		wormList_[wormIndex_]->GetCurUIController()->GetCurWeaponSheet()->WeaponSheetTernOff();

		currentTurnTime_ = 0.0f;
	}

	if (currentTurnTime_ < 0 || 0 == currentWorm_->GetActionTokenCount())
	{
		// 턴시간 초과 or 토큰 소진으로 인한 플레이어 전환이 발생하므로 이곳에서
		// 무기창 비활성이 된다.
		wormList_[wormIndex_]->GetCurUIController()->GetCurWeaponSheet()->WeaponSheetTernOff();

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
	//TODO : 게임 컨트롤러에서 모든 웜들의 행동,드럼통 기름 등등이 움직임이 모두 멈춘것을 확인하면 호출하도록 할것

	for (size_t i = 0; i < wormList_.size(); i++)
	{
		if (true == wormList_[i]->isDamagedThisTurn())
		{
			wormList_[i]->GetCurUIController()->GetCurTopState()->SetTextChangeRequest();
		}
	}

	if (true)
	{
		settementTime_ += GameEngineTime::GetInst().GetDeltaTime();
		// 모든 웜이 Idle 상태로 돌아오고, UI 변환이 완료됐을 때 시간이 돌게 설계할 것
	}
	
	////////////////////////// Worm Death 진행 ////////////////////////
	//1. 죽을 얘가 있는지 확인
	// Death를 진행시킬 worm

	if (false == WormDeathReady_)
	{
		CurDeathWorm_ = NextDeathWorm_;
		NextDeathWorm_ = nullptr;
		for (int i = 0; i < wormList_.size(); ++i)
		{
			if (true == wormList_[i]->GetDeathReady_())
			{
				WormDeathReady_ = true; //			(worm)의		Death를		준비중이다.
				WormDeathProgressing_ = true; //	(컨트롤러)가 Death상태	진행중이다.
				// 데미지를 입어 죽게될 worm은 GetDeathReady_()를 통해 bool 값을 전달한다.
				if (nullptr == CurDeathWorm_)
				{
					CurDeathWorm_ = wormList_[i];
					continue;
				}
				else if (nullptr == NextDeathWorm_)
				{
					NextDeathWorm_ = wormList_[i];
					break;
					// 1개체 죽음 완료후, 
					// 죽음이 완료된 worm은 wormList_에서 지워져서 들어와선 안됨
				}				
			}

			if((CurDeathWorm_ == nullptr) && (NextDeathWorm_ == nullptr))
			{
				WormDeathProgressing_ = false; // 죽어야할 worm을 하나도 못 찾았다.
			}
		}

		//TODO : 다음에 죽게될 nextworm을 지정해 주어야함
		// DeathStart가 되어 에니메이션을 재생하고, 재생이 완료, DeathEnd가 된것을 인지하고
		// nextworm state로 넘어가고, 그 nextworm에 다음 죽게될 worm을 넘겨주어야함

		//worm의 죽음 상태 변화를 시작함 만들어줌 // worm의 대기상태와 GameController의 대기상태는 다름
		if (nullptr != CurDeathWorm_)
		{					
			CurDeathWorm_->SetDeathReady(false);
			CurDeathWorm_->SetDeathStart(true);
		}
	}
	//다음 worm 죽이기까지 컨트롤러를 대기시킨다.
	if (true == WormDeathReady_)
	{
		WormDeathWaitingTime_ += GameEngineTime::GetInst().GetDeltaTime();

		if (WormDeathWaitingTime_ > 3.f) // 3초가 지나면 대기가 끝난다.
		{
			WormDeathReady_ = false; // 다시 다음 worm을 찾을 준비가 됬따.
			WormDeathWaitingTime_ = 0.f;
		
			//SetFocusOnlyOneWorm(CurDeathWorm_);
			//CurDeathWorm_ = NextDeathWorm_;
			//NextDeathWorm_ = nullptr;
			//대기가 끝남
		}
	}

	if (false == WormDeathProgressing_) // worm을 죽이는 중도 아니고, 죽일놈도 못찾았으면 다음 차레로 넘어가
										// 다음 웜으로 넘겨준다.
	{
		if (SETTLEMENT_TIME <= settementTime_)
		{
			settementTime_ = 0.0f;
			return "NextWorm";
		}
	}

	return StateInfo();
}

StateInfo GameController::startDeathPhase(StateInfo _state)
{
	return StateInfo();
}

StateInfo GameController::updateDeathPhase(StateInfo _state)
{
	//DeathPhase에서 다시 결산 페이즈로 넘어가, 갱신될 수도 있다.
	return "NextWorm";

	return StateInfo();
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
	// 현재 플레이어의 체력에 따라 정렬 시작
	int Size = static_cast<int>(PlayerHPBarList_.size());
	for (int i = 0; i < Size; ++i)
	{
		if (Size == i + 1)
		{
			break;
		}

		if (PlayerHPBarList_[i + 1] == _CurUI)
		{
			continue;
		}

		if (PlayerHPBarList_[i]->GetCurHP() < PlayerHPBarList_[i + 1]->GetCurHP())
		{
			SortStartIndex = i;
			BottomUISortStart = true;
		}
	}
}

void GameController::BottomStateHPBarSortStart()
{
	SortDeltaTime += GameEngineTime::GetInst().GetDeltaTime();
	if (0.3f <= SortDeltaTime)
	{
		SortDeltaTime = 0.f;

		int Size = static_cast<int>(PlayerHPBarList_.size());
		bool Flag = false;
		for (int i = SortStartIndex; i < SortStartIndex + 1; ++i)
		{
			//if (i == Size)
			//{
				// 마지막 인덱스까지 정렬이 완료되었으면 Flag 해제
				//BottomUISortStart = false;
				//return;
			//}

			for (int j = SortStartIndex + 1; j < Size; ++j)
			{
				if (PlayerHPBarList_[i] == PlayerHPBarList_[j])
				{
					continue;
				}

				if (PlayerHPBarList_[i]->GetCurHP() < PlayerHPBarList_[j]->GetCurHP())
				{
					// 실질적인 렌더링 위치를 변경하고
					float CurPlayerYPos = PlayerHPBarList_[i]->GetBottomUIYPos();
					float ComparePlayerYPos = PlayerHPBarList_[j]->GetBottomUIYPos();
					PlayerHPBarList_[i]->SetBottomStateBarRenderPos(ComparePlayerYPos);
					PlayerHPBarList_[j]->SetBottomStateBarRenderPos(CurPlayerYPos);

					// PlayerHPBarList_ 순서를 변경
					BottomStateUI* Temp = PlayerHPBarList_[i];
					PlayerHPBarList_[i] = PlayerHPBarList_[j];
					PlayerHPBarList_[j] = Temp;

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

		// 정렬완료 후 현재 플레이어가 체력이 0이면
		// 화면밖으로 떨어뜨리며 죽인다.
		//CurPlayerDeathCheck();
	}
}

void GameController::CurPlayerDeathCheck()
{
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