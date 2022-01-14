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
	weaponsheet_->CreateWeaponIconList(_weaponlist);
}

void UIController::Start()
{
	float4 Resolution = GameEngineWindow::GetInst().GetSize();

	// UI�� ���� ����
	weaponsheet_ = GetLevel()->CreateActor<WeaponSheet>();
	float4 ActivePos = float4({ Resolution.x - 100.f, Resolution.y - 240.f });
	float4 DisablePos = float4({ Resolution.x + 100.f, Resolution.y - 240.f });
	weaponsheet_->SetRenderPos(ActivePos, DisablePos);

	// UI�� Ű����
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

