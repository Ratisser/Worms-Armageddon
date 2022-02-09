#include "UIController.h"
#include "WeaponSheet.h"
#include "Weapon.h"

#include "BottomNameTag.h"
#include "BottomFlag.h"
#include "BottomHealthBar.h"
#include "WormName.h"
#include "WormArrow.h"
#include "WormHPBlankWindow.h"
#include "WormHPNumber.h"

#include "TimerBlankWindow.h"
#include "TimerDigit.h"

#include <GameEngineWindow.h>
#include <GameEngineInput.h>
#include <GameEngineLevel.h>


UIController::UIController() :
	weaponsheet_(nullptr),
	bottomNameTag_(nullptr),
	bottomFlag_(nullptr),
	bottomHealthBar_(nullptr),
	curWormName_(nullptr),
	curWormArrow_(nullptr),
	curWormHPWindow_(nullptr),
	curHPNumberHundred_(nullptr),
	curHPNumberTen_(nullptr),
	curHPNumber_(nullptr),
	curTimerWindow_(nullptr),
	curTimerDigitTen_(nullptr),
	curTimerDigit_(nullptr)
{
}

UIController::~UIController()
{
}

void UIController::SetCurPlayer(Worm* _curplayer)
{
	curplayer_ = _curplayer;
}

void UIController::CreateWeaponList(const std::vector<eItemList>& _weaponlist)
{
	// 각각의 플레이어마다의 무기리스트 생성
	weaponsheet_->CreateWeaponIconList(_weaponlist);
}

void UIController::AddWeapon(eItemList _Weapon)
{
	weaponsheet_->AddWeapon(_Weapon);
}

void UIController::UseWeapon(eItemList _Weapon)
{
	weaponsheet_->UseWeapon(_Weapon);
}

Worm* UIController::GetCurPlayer() const
{
	return curplayer_;
}

WeaponSheet* UIController::GetCurWeaponSheet() const
{
	return weaponsheet_;
}

BottomHealthBar* UIController::GetCurBottomHealthBar()
{
	return bottomHealthBar_;
}

BottomNameTag* UIController::GetCurBottomNameTag() const
{
	return bottomNameTag_;
}

BottomFlag* UIController::GetCurBottomFlag() const
{
	return bottomFlag_;
}

WormName* UIController::GetCurWormName()
{
	return curWormName_;
}

WormArrow* UIController::GetCurWormArrow()
{
	return curWormArrow_;
}

TimerBlankWindow* UIController::GetCurTimerWindow()
{
	return curTimerWindow_;
}

TimerDigit* UIController::GetCurTimerDigitTen()
{
	return curTimerDigitTen_;
}

TimerDigit* UIController::GetCurTimerDigit()
{
	return curTimerDigit_;
}

WormHPBlankWindow* UIController::GetCurWormHPWindow()
{
	return curWormHPWindow_;
}

WormHPNumber* UIController::GetCurHPNumberHundred()
{
	return curHPNumberHundred_;
}

WormHPNumber* UIController::GetCurHPNumberTen()
{
	return curHPNumberTen_;
}

WormHPNumber* UIController::GetCurHPNumber()
{
	return curHPNumber_;
}

void UIController::Start()
{
	float4 Resolution = GameEngineWindow::GetInst().GetSize();

	// UI별 액터 생성
	// Weapon Sheet 생성
	float4 ActivePos = float4({ Resolution.x - 100.f, Resolution.y - 240.f });		// WeaponSheet ActivePos(활성화위치)
	float4 DisablePos = float4({ Resolution.x + 100.f, Resolution.y - 240.f });	// WeaponSheet DisablePos(비활성화위치)
	weaponsheet_ = GetLevel()->CreateActor<WeaponSheet>();						// WeaponSheet 생성
	weaponsheet_->SetRenderPos(ActivePos, DisablePos);									// 활성화/비활성화 위치 설정														// 해당 WeaponSheet를 생성한 UIController 저장

	// 플레이어 하단 상태
	bottomNameTag_ = GetLevel()->CreateActor<BottomNameTag>();
	bottomFlag_ = GetLevel()->CreateActor<BottomFlag>();
	bottomHealthBar_ = GetLevel()->CreateActor<BottomHealthBar>();

	// 플레이어 위 UI
	curWormName_ = GetLevel()->CreateActor<WormName>();
	curWormArrow_ = GetLevel()->CreateActor<WormArrow>();
	curWormHPWindow_ = GetLevel()->CreateActor<WormHPBlankWindow>();
	curHPNumberHundred_ = GetLevel()->CreateActor<WormHPNumber>();
	curHPNumberTen_ = GetLevel()->CreateActor<WormHPNumber>();
	curHPNumber_ = GetLevel()->CreateActor<WormHPNumber>();

	// 플레이어 턴타임 UI
	curTimerWindow_ = GetLevel()->CreateActor<TimerBlankWindow>();
	curTimerDigitTen_ = GetLevel()->CreateActor<TimerDigit>();
	curTimerDigitTen_->SetPos({ 28,690 });
	curTimerDigit_ = GetLevel()->CreateActor<TimerDigit>();
	curTimerDigit_->SetPos({ 48,690 });
}

void UIController::UpdateBefore()
{
}

void UIController::Update()
{
}

void UIController::UpdateAfter()
{
}

void UIController::Render()
{
}
