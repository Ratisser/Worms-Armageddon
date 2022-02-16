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

GameController::GameController() // default constructer ����Ʈ ������
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
	, WaterLevel_(nullptr)
	, settementTime_(0.0f)
{

}

GameController::~GameController() // default destructer ����Ʈ �Ҹ���
{

}

void GameController::Start()
{
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

	// TODO : �׽�Ʈ�� ���� �� ����
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
		GameEngineDebug::MsgBoxError("�ִ� ������ ������ �ʰ��Ͽ����ϴ�.");
		return;
	}

	GameEngineMath::Random randomGenerator;
	std::string name = "Worm";
	name += std::to_string(currentIndex_++);
	Worm* newWorm = parentLevel_->CreateActor<Worm>(name);
	wormXPosContainer_ = randomGenerator.RandomFloat(_minX, _maxX); // ���� ������ ��ǥ�� ��������� ����

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

		// UI�����ڻ���
		UIController* CurUIController = parentLevel_->CreateActor<UIController>(Name);
		CurUIController->SetCurPlayer(wormList_[i]);

		// �÷��̾�� UIController ����
		wormList_[i]->SetUIController(CurUIController);
		wormList_[i]->GetCurUIController()->GetCurWeaponSheet()->SetParentController(wormList_[i]->GetCurUIController());

		// �÷��̾�� �ϴ� ���� UI
		wormList_[i]->GetCurUIController()->GetCurBottomState()->SetParentWorm(wormList_[i]);
		wormList_[i]->GetCurUIController()->GetCurBottomState()->SetParentUIController(CurUIController);
		wormList_[i]->GetCurUIController()->GetCurBottomState()->GameStartInit(static_cast<int>(i));

		// �÷��̾�� ��� ���� UI
		//wormList_[i]->GetCurUIController()->GetCurTopState()->SetParentWorm(wormList_[i]);
		//wormList_[i]->GetCurUIController()->GetCurTopState()->SetParentUIController(CurUIController);
		//wormList_[i]->GetCurUIController()->GetCurTopState()->GameStartInit(static_cast<int>(i));

		// �÷��̾�� �� Ÿ�̸� UI ����
		wormList_[i]->GetCurUIController()->GetCurTimerWindow()->RenderColorInit(static_cast<int>(i));
		wormList_[i]->GetCurUIController()->GetCurTimerWindow()->SetParentWorm(wormList_[i]);
		wormList_[i]->GetCurUIController()->GetCurTimerDigitTen()->SetParentWorm(wormList_[i]);
		wormList_[i]->GetCurUIController()->GetCurTimerDigit()->SetParentWorm(wormList_[i]);

		// �÷��̾�� ü��ǥ���ؽ�Ʈ UI ����
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

		// �÷��̾�� ����â ���� �� Ȱ��ȭ ���� ����
		std::string SheetName = wormList_[i]->GetName();
		SheetName += "_WeaponSheet";
		wormList_[i]->GetCurUIController()->GetCurWeaponSheet()->SetName(SheetName);

		// �ʱ� ������ �������
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
		CurUIController->CreateWeaponList(ItemListTest);				// �÷��̾ ó�� �������ִ� �����۸��(��������)

		// ����â ��� �����
		//CurUIController->AddWeapon(eItemList::WEAPON_AIRSTRIKE);		// �÷��̾ ��Ϳ�����Ʈ ȹ������ ���� ����ȹ��� ȣ��(���ο���߰� �Ǵ� �������ⰳ������)
		//CurUIController->UseWeapon(eItemList::WEAPON_AIRSTRIKE);		// �÷��̾ ������������ ȣ��(�������ִ� ���ⰳ������)
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
	state_.CreateState("Settlement", &GameController::startSettlement, &GameController::updateSettlement);
	state_.CreateState("Death", &GameController::startDeath, &GameController::updateDeath);
	state_.CreateState("Victory", &GameController::startVictory, &GameController::updateVictory);
	state_.CreateState("ItemDrop", &GameController::startItemDrop, &GameController::updateItemDrop);

	state_.ChangeState("NextWorm");
}

StateInfo GameController::startNextWorm(StateInfo _state)
{
	GameEngineSoundManager::GetInstance().PlaySoundByName("YESSIR.WAV");

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

	// ���� ��Ÿ�Ӽ��ÿ� ���� ��Ÿ���� �޶��� - 220207 SJH ����
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
	// Ÿ�̸� ������ �� ����ϴ� �κ�
	currentWorm_->GetCurUIController()->GetCurTimerDigitTen()->SetTenDigitTime(currentTurnTime_);
	currentWorm_->GetCurUIController()->GetCurTimerDigit()->SetDigitTime(currentTurnTime_);

	if (GameEngineInput::GetInst().IsDown("TestKey"))
	{
		currentWorm_->SubtractActionToken(1);

		// ������ȯ�������� ����â �� ��������� ��Ȱ��ȭ
		wormList_[wormIndex_]->GetCurUIController()->GetCurWeaponSheet()->WeaponSheetTernOff();

		currentTurnTime_ = 0.0f;
	}

	if (currentTurnTime_ < 0)
	{
		// �Ͻð� �ʰ��� ���� �÷��̾� ��ȯ�� �߻��ϹǷ� �̰�����
		// ����â ��Ȱ���� �ȴ�.
		wormList_[wormIndex_]->GetCurUIController()->GetCurWeaponSheet()->WeaponSheetTernOff();

		// ���Ÿ�� �ʰ� �� �÷��̾� ���ʰ��� ������ ���
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

	currentWorm_ = nullptr;
	return "Settlement";
	// return "NextWorm";
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



	if (true == allSettlementDone_)
	{
		settementTime_ += GameEngineTime::GetInst().GetDeltaTime();
	}

	if (SETTLEMENT_TIME <= settementTime_)
	{
		settementTime_ = 0.0f;
		return "NextWorm";
	}

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

void GameController::MakeWaterLevel(float _WaterLevel)
{
	WaterLevel_ = GetLevel()->CreateActor<WaterLevel>("WaterLevel"); // ��� �ĵ� actor �׷�ȭ
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
