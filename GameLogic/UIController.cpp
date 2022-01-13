#include "UIController.h"
#include "WeaponSheet.h"
#include "Weapon.h"

#include <GameEngineWindow.h>
#include <GameEngineInput.h>
#include <GameEngineLevel.h>


UIController::UIController() :
	curplayer_(nullptr),
	weaponsheet_(nullptr)
{

}

UIController::~UIController()
{
}

UIController::UIController(UIController&& _other) noexcept :
	curplayer_(_other.curplayer_),
	weaponsheet_(_other.weaponsheet_)
{

}

void UIController::SetCurPlayer(Worm* _curplayer)
{
	curplayer_ = _curplayer;
}

void UIController::SetCurItemList(const std::map<std::string, Weapon*>& _WeaponList)
{
	// 플레이어로부터 받아온 아이템목록을
	// WeaponSheet에 넘겨준다.
	weaponsheet_->CreateWeaponIconList(_WeaponList);
}

void UIController::Start()
{
	float4 Resolution = GameEngineWindow::GetInst().GetSize();

	// UI별 액터 생성
	weaponsheet_ = GetLevel()->CreateActor<WeaponSheet>();
	weaponsheet_->SetPos({ Resolution.x + 100.f, Resolution.y - 240.f, Resolution.z, Resolution.w });

	// UI별 키생성
	if (false == GameEngineInput::GetInst().IsKey("WeaponSheet"))
	{
		GameEngineInput::GetInst().CreateKey("WeaponSheet", VK_RBUTTON);
	}
}

void UIController::UpdateBefore()
{
}

void UIController::Update()
{
	// Weapon Sheet Active/DisEnable
	if (true == GameEngineInput::GetInst().IsDown("WeaponSheet"))
	{
		weaponsheet_->WeaponSheetActive();
	}
}

void UIController::UpdateAfter()
{
}

void UIController::Render()
{
}

