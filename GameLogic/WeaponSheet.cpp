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

WeaponSheet::~WeaponSheet() // default destructer ����Ʈ �Ҹ���
{

}

WeaponSheet::WeaponSheet(WeaponSheet&& _other) noexcept
{

}

void WeaponSheet::Start()
{
	// ������ ���� �� ī�޶��� ����
	SetRenderOrder(10000);
	MainRenderer_ = CreateRenderer("WeaponSheet");
	MainRenderer_->SetCameraEffectOff();

	// �浹ü ���� �� ī�޶��� ����
	//MainCollision_ = CreateCollision()

	// Ȱ��/��Ȱ�� Ÿ����ġ �ʱ�ȭ
	float4 Resolution = GameEngineWindow::GetInst().GetSize();
	ActiveTargetPos_ = float4(Resolution.x - 100.f, Resolution.y - 240.f);	// Ȱ��ȭ��ġ
	DisableTargetPos_ = float4(Resolution.x + 100.f, Resolution.y - 240.f);	// ��Ȱ��ȭ��ġ
}

void WeaponSheet::UpdateBefore()
{
	// �������� ���콺 ��ġ ����
	MousePos_ = GameEngineWindow::GetInst().GetMousePos();

	// ������ ���콺�� WeaponSheet �浹üũ

	

}

void WeaponSheet::Update()
{
	if (false == Moving_)
	{
		MovePos_ = float4::ZERO;
	}

	// ��򰡷κ��� Ű�Է½� Ȱ��ȭ/��Ȱ��ȭ
	if (true == Active_) // ��Ȱ��ȭ -> Ȱ��ȭ
	{
		// ���� Ȱ��ȭ Ÿ����ġ���� �̵��ߴٸ� �ߴ�
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
	else // Ȱ��ȭ -> ��Ȱ��ȭ
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

