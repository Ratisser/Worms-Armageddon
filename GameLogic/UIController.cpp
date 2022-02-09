#include "UIController.h"
#include "WeaponSheet.h"
#include "Weapon.h"

#include "BottomNameTag.h"
#include "BottomFlag.h"
#include "BottomHealthBar.h"
#include  "WormName.h"
#include  "WormArrow.h"
#include "WormHPBlankWindow.h"
#include "WormHPNumber.h"

#include "TimerBlankWindow.h"
#include "TimerDigit.h"

#include <GameEngineWindow.h>
#include <GameEngineInput.h>
#include <GameEngineLevel.h>


UIController::UIController() :
	curplayer_(nullptr),
	weaponsheet_(nullptr),
	bottomNameTag_(nullptr),
	bottomFlag_(nullptr),
	bottomHealthBar_(nullptr)
{

}

UIController::~UIController()
{
}

UIController::UIController(UIController&& _other) noexcept :
	curplayer_(_other.curplayer_),
	weaponsheet_(_other.weaponsheet_),
	bottomNameTag_(_other.bottomNameTag_),
	bottomFlag_(_other.bottomFlag_),
	bottomHealthBar_(_other.bottomHealthBar_)

{

}

void UIController::SetCurPlayer(Worm* _curplayer)
{
	curplayer_ = _curplayer;
}

void UIController::CreateWeaponList(const std::vector<eItemList>& _weaponlist)
{
	// ������ �÷��̾���� ���⸮��Ʈ ����
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

	// UI�� ���� ����
	// Weapon Sheet ����
	float4 ActivePos = float4({ Resolution.x - 100.f, Resolution.y - 240.f });		// WeaponSheet ActivePos(Ȱ��ȭ��ġ)
	float4 DisablePos = float4({ Resolution.x + 100.f, Resolution.y - 240.f });	// WeaponSheet DisablePos(��Ȱ��ȭ��ġ)
	weaponsheet_ = GetLevel()->CreateActor<WeaponSheet>();						// WeaponSheet ����
	weaponsheet_->SetRenderPos(ActivePos, DisablePos);									// Ȱ��ȭ/��Ȱ��ȭ ��ġ ����														// �ش� WeaponSheet�� ������ UIController ����

	bottomNameTag_ = GetLevel()->CreateActor<BottomNameTag>();
	bottomFlag_ = GetLevel()->CreateActor<BottomFlag>();
	bottomHealthBar_ = GetLevel()->CreateActor<BottomHealthBar>();
	curWormName_ = GetLevel()->CreateActor<WormName>();
	curWormArrow_ = GetLevel()->CreateActor<WormArrow>();
	curWormHPWindow_ = GetLevel()->CreateActor<WormHPBlankWindow>();

	curTimerWindow_ = GetLevel()->CreateActor<TimerBlankWindow>();
	curTimerDigitTen_ = GetLevel()->CreateActor<TimerDigit>();
	curTimerDigitTen_->SetPos({ 28,690 });
	curTimerDigit_ = GetLevel()->CreateActor<TimerDigit>();
	curTimerDigit_->SetPos({ 48,690 });

	curHPNumberHundred_ = GetLevel()->CreateActor<WormHPNumber>();
	curHPNumberTen_ = GetLevel()->CreateActor<WormHPNumber>();
	curHPNumber_ = GetLevel()->CreateActor<WormHPNumber>();
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


