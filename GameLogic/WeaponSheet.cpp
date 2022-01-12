#include "WeaponSheet.h"

#include <GameEngineLevel.h>
#include <GameEngineRenderer.h>
#include <GameEngineCollision.h>

#include <GameEngineWindow.h>
#include <GameEngineTime.h>

bool WeaponSheet::Active_ = false;

WeaponSheet::WeaponSheet() :
	MainRenderer_(nullptr),
	MainCollision_(nullptr),
	MousePos_(float4::ZERO),
	ActiveTargetPos_(float4::ZERO),
	DisableTargetPos_(float4::ZERO),
	Moving_(false),
	MovingSpeed(0.9f),
	MovePos_(float4::ZERO)
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
	// 렌더러 생성 및 카메라영향 제거
	SetRenderOrder(10000);
	MainRenderer_ = CreateRenderer("WeaponSheet");
	MainRenderer_->SetCameraEffectOff();

	// 충돌체 생성 및 카메라영향 제거
	//MainCollision_ = CreateCollision()

	// 활성/비활성 타겟위치 초기화
	float4 Resolution = GameEngineWindow::GetInst().GetSize();
	ActiveTargetPos_ = float4(Resolution.x - 100.f, Resolution.y - 240.f);	// 활성화위치
	DisableTargetPos_ = float4(Resolution.x + 100.f, Resolution.y - 240.f);	// 비활성화위치
}

void WeaponSheet::UpdateBefore()
{
	// 갱신전에 마우스 위치 갱신
	MousePos_ = GameEngineWindow::GetInst().GetMousePos();

	// 갱신전 마우스와 WeaponSheet 충돌체크

	

}

void WeaponSheet::Update()
{
	if (false == Moving_)
	{
		MovePos_ = float4::ZERO;
	}

	// 어딘가로부터 키입력시 활성화/비활성화
	if (true == Active_) // 비활성화 -> 활성화
	{
		// 만약 활성화 타겟위치까지 이동했다면 중단
		if (ActiveTargetPos_.x <= GetPos().x)
		{
			MovePos_ += float4::LEFT * GameEngineTime::GetInst().GetDeltaTime();
			SetMove(MovePos_ * MovingSpeed);

			Moving_ = true;
		}
		else
		{
			Moving_ = false;
		}
	}
	else // 활성화 -> 비활성화
	{
		if (DisableTargetPos_.x >= GetPos().x)
		{
			MovePos_ += float4::RIGHT * GameEngineTime::GetInst().GetDeltaTime();
			SetMove(MovePos_ * MovingSpeed);

			Moving_ = true;
		}
		else
		{
			Moving_ = false;
		}
	}
}

void WeaponSheet::UpdateAfter()
{
}

void WeaponSheet::Render()
{
	MainRenderer_->Render();
}

