#include "WeaponSheet.h"
#include "eCollisionGroup.h"

#include "MouseObject.h"

#include <GameEngineLevel.h>
#include <GameEngineRenderer.h>
#include <GameEngineCollision.h>

#include <GameEngineWindow.h>
#include <GameEngineTime.h>

WeaponSheet::WeaponSheet() :
	active_(false),
	prevstate_(false),
	mainrenderer(nullptr),
	maincollision_(nullptr),
	mouseobject_(nullptr),
	activetargetpos_(float4::ZERO),
	disabletargetpos_(float4::ZERO),
	moving_(false),
	movingspeed(0.9f),
	movepos_(float4::ZERO)
{
}

WeaponSheet::~WeaponSheet() // default destructer ����Ʈ �Ҹ���
{

}

WeaponSheet::WeaponSheet(WeaponSheet&& _other) noexcept :
	active_(_other.active_),
	prevstate_(_other.prevstate_),
	mainrenderer(_other.mainrenderer),
	maincollision_(_other.maincollision_),
	mouseobject_(_other.mouseobject_),
	activetargetpos_(_other.activetargetpos_),
	disabletargetpos_(_other.disabletargetpos_),
	moving_(_other.moving_),
	movingspeed(_other.movingspeed),
	movepos_(_other.movepos_)
{

}

void WeaponSheet::Start()
{
	// ������ ���� �� ī�޶��� ����
	SetRenderOrder(9999);
	mainrenderer = CreateRenderer("WeaponSheet");
	mainrenderer->SetCameraEffectOff();

	// �浹ü ����
	//maincollision_ = CreateCollision(static_cast<int>(eCollisionGroup::UI), CollisionCheckType::RECT);

	// Ȱ��/��Ȱ�� Ÿ����ġ �ʱ�ȭ
	float4 Resolution = GameEngineWindow::GetInst().GetSize();
	activetargetpos_ = float4(Resolution.x - 100.f, Resolution.y - 240.f);	// Ȱ��ȭ��ġ
	disabletargetpos_ = float4(Resolution.x + 100.f, Resolution.y - 240.f);	// ��Ȱ��ȭ��ġ

	// ���콺 ����
	float4 MouseRange = float4(activetargetpos_.x - (mainrenderer->GetImageSize().x * 0.5f), activetargetpos_.y - (mainrenderer->GetImageSize().y * 0.5f));

	mouseobject_ = GetLevel()->CreateActor<MouseObject>();
	mouseobject_->SetMoveRange(MouseRange, MouseRange + mainrenderer->GetImageSize());
	mouseobject_->SetFinalPos(MouseRange); // �ʱ���ġ
	mouseobject_->SetPos(MouseRange);
	mouseobject_->Off();
}

void WeaponSheet::UpdateBefore()
{

}

void WeaponSheet::Update()
{
	// ��򰡷κ��� Ű�Է½� Ȱ��ȭ/��Ȱ��ȭ
	if (true == active_) // ��Ȱ��ȭ -> Ȱ��ȭ
	{
		// ���� Ȱ��ȭ Ÿ����ġ���� �̵��ߴٸ� �ߴ�
		if (activetargetpos_.x <= GetPos().x)
		{
			movepos_ += float4::LEFT * GameEngineTime::GetInst().GetDeltaTime();
			SetMove(movepos_ * movingspeed);

			moving_ = true;
		}
		else
		{
			moving_ = false;
		}
	}
	else // Ȱ��ȭ -> ��Ȱ��ȭ
	{
		if (disabletargetpos_.x >= GetPos().x)
		{
			movepos_ += float4::RIGHT * GameEngineTime::GetInst().GetDeltaTime();
			SetMove(movepos_ * movingspeed);

			moving_ = true;
		}
		else
		{
			moving_ = false;
		}

		// ��Ȱ��ȭ�ÿ��� �ٷ� Off��Ŵ
		if (true == prevstate_)
		{
			mouseobject_->Off();
			mouseobject_->SetFinalPos(mouseobject_->GetPos());
		}
	}

	// �̵����� �ƴҶ� �������¿� ���� ���°� �ٸ��� ó��
	if (false == moving_)
	{
		movepos_ = float4::ZERO;

		if (prevstate_ != active_)
		{
			if (true == active_)
			{
				mouseobject_->On();
				mouseobject_->MoveMousePos();
			}

			prevstate_ = active_;
		}
	}
}

void WeaponSheet::UpdateAfter()
{
}

void WeaponSheet::Collision()
{	
	// �������� ���콺�� WeaponSheet �浹üũ
	//if (true == maincollision_->CollisionCheck(mouseobject_->GetMouseCol()))
	//{
	//	int a = 0;
	//}
}

void WeaponSheet::Render()
{
	mainrenderer->Render();
}

void WeaponSheet::CreateWeaponIconList(const std::map<std::string, Weapon*>& _WeaponList)
{
	// �÷��̾�κ��� ���� �����۸���� �̿��Ͽ� Ȱ��ȭ�� �����۾������� �����ϸ� ��ġ����� �Ͽ� �ʱ� ��ġ�� ����
	std::map<std::string, Weapon*> CurWeaponList = _WeaponList;

	std::map<std::string, Weapon*>::iterator ListStart = CurWeaponList.begin();
	std::map<std::string, Weapon*>::iterator ListEnd = CurWeaponList.end();
	for (; ListStart != ListEnd; ++ListStart)
	{
		// ������ ��




	}

	



}

