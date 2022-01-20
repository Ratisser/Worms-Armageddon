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

void UIController::Start()
{
	float4 Resolution = GameEngineWindow::GetInst().GetSize();

	// UI�� ���� ����
	// Weapon Sheet ����
	float4 ActivePos = float4({ Resolution.x - 100.f, Resolution.y - 240.f });		// WeaponSheet ActivePos(Ȱ��ȭ��ġ)
	float4 DisablePos = float4({ Resolution.x + 100.f, Resolution.y - 240.f });	// WeaponSheet DisablePos(��Ȱ��ȭ��ġ)
	weaponsheet_ = GetLevel()->CreateActor<WeaponSheet>();						// WeaponSheet ����
	weaponsheet_->SetRenderPos(ActivePos, DisablePos);									// Ȱ��ȭ/��Ȱ��ȭ ��ġ ����														// �ش� WeaponSheet�� ������ UIController ����

	// ...
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

