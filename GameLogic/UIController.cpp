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

void UIController::Start()
{
	float4 Resolution = GameEngineWindow::GetInst().GetSize();

	// UI별 액터 생성
	// Weapon Sheet 생성
	float4 ActivePos = float4({ Resolution.x - 100.f, Resolution.y - 240.f });		// WeaponSheet ActivePos(활성화위치)
	float4 DisablePos = float4({ Resolution.x + 100.f, Resolution.y - 240.f });	// WeaponSheet DisablePos(비활성화위치)
	weaponsheet_ = GetLevel()->CreateActor<WeaponSheet>();						// WeaponSheet 생성
	weaponsheet_->SetRenderPos(ActivePos, DisablePos);									// 활성화/비활성화 위치 설정
	weaponsheet_->SetParentController(this);														// 해당 WeaponSheet를 생성한 UIController 저장

	// ...



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

