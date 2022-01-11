#include "WeaponSheet.h"

#include <GameEngineRenderer.h>
#include <GameEngineCollision.h>
#include <GameEngineTime.h>

WeaponSheet::WeaponSheet() :
	MainRenderer_(nullptr)
{

}

WeaponSheet::~WeaponSheet() // default destructer 디폴트 소멸자
{

}

WeaponSheet::WeaponSheet(WeaponSheet&& _other) noexcept
{

}

void WeaponSheet::Start()
{
	SetRenderOrder(10000);
	MainRenderer_ = CreateRenderer("WeaponSheet");
	MainRenderer_->SetCameraEffectOff();
	//MainRenderer_->Off();

}

void WeaponSheet::UpdateBefore()
{
}

void WeaponSheet::Update()
{
}

void WeaponSheet::UpdateAfter()
{
}

void WeaponSheet::Render()
{
	MainRenderer_->Render();
}

