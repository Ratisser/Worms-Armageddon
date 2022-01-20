#include "MouseObject.h"
#include "eCollisionGroup.h"
#include "Worm.h"
#include "UIController.h"
#include "WeaponSheet.h"
#include "WeaponIcon.h"

#include <GameEngineLevel.h>
#include <GameEngineRenderer.h>
#include <GameEngineCollision.h>
#include <EngineEnum.h>

#include <GameEngineWindow.h>
#include <GameEngineTime.h>
#include <GameEngineInput.h>

MouseObject::MouseObject() :
	mainrenderer_(nullptr),
	maincollision_(nullptr),
	finalpos_(float4::ZERO),
	startrange_(float4::ZERO),
	endrange_(float4::ZERO)
{
}

MouseObject::~MouseObject() // default destructer ����Ʈ �Ҹ���
{

}

MouseObject::MouseObject(MouseObject&& _other) noexcept :
	mainrenderer_(_other.mainrenderer_),
	maincollision_(_other.maincollision_),
	finalpos_(_other.finalpos_),
	startrange_(_other.startrange_),
	endrange_(_other.endrange_)
{

}

GameEngineCollision* MouseObject::GetMouseCol()
{
	return maincollision_;
}

void MouseObject::SetMoveRange(const float4& _Start, const float4& _End)
{
	startrange_ = _Start;
	endrange_ = _End;
}

void MouseObject::SetFinalPos(const float4& _FinalPos)
{
	finalpos_ = _FinalPos;
}

void MouseObject::MoveMousePos(bool _Flag)
{
	if (true == _Flag)
	{
		int x = finalpos_.ix();
		int y = finalpos_.iy();

		GameEngineWindow::GetInst().SetMousePos(x, y);
	}
}

void MouseObject::Start()
{
	SetRenderOrder(static_cast<int>(RenderOrder::Mouse));
	mainrenderer_ = CreateRenderer("Cursor");
	mainrenderer_->SetRenderSize(float4(32.f, 32.f));
	mainrenderer_->SetCameraEffectOff();

	maincollision_ = CreateCollision(static_cast<int>(eCollisionGroup::MOUSE), CollisionCheckType::POINT);

	rendersize_ = mainrenderer_->GetImageSize();

	//ShowCursor(false);
}

void MouseObject::UpdateBefore()
{
	// ����â Ȱ��ȭ�Ǿ����� ��������ܰ� �浹�����϶�
	// ���콺���ʹ�ư Ŭ���� �ش� ���� ���������Ǵ��Ͽ� ����ä�ù��⸦ �����ϰ�
	// ����â�� ��Ȱ��ȭ��Ų��.
	GameEngineCollision* ColUI = maincollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::UI));
	if (nullptr != ColUI)
	{
		WeaponIcon* CollisionWeapon = dynamic_cast<WeaponIcon*>(ColUI->GetActor());
		if (nullptr != CollisionWeapon)
		{
			// ���콺���ʹ�ưŬ���̶��
			if (true == GameEngineInput::GetInst().IsDown("Boom"))
			{
				if (true == CollisionWeapon->GetParentSheet()->IsActive())
				{
					Worm* CurPlayer = CollisionWeapon->GetParentSheet()->GetParentController()->GetCurPlayer();
					if (nullptr != CurPlayer)
					{
						// ���� �浹�� �������� Ȱ��ȭ �����϶��� ���ð���
						if (true == CollisionWeapon->IsMainrendererOn())
						{
							// ���� �÷��̾� ���繫�� ����
							CurPlayer->SetCurWeapon(CollisionWeapon->GetWeaponType());

							// ���� �÷��̾��� ����â ��Ȱ��ȭ
							CurPlayer->GetCurUIController()->GetCurWeaponSheet()->WeaponSheetActive();
						}
					}
				}
			}
		}
	}
}

void MouseObject::Update()
{
	// ��ġ ����(��, �̵������� ����� ���ž���)
	float4 MousePos = GameEngineWindow::GetInst().GetMousePos();

	// ����â�� Ȱ��ȭ�Ǹ� �����ȹ��� ������ Ŀ�� �̵��Ұ�
	// ����â�� ��Ȱ��ȭ�� �����Ӱ� �̵�
	if (true == WeaponSheet::isweaponsheet())
	{
		// ���������� ���ִٸ�
		if (MousePos.x >= startrange_.x && MousePos.x <= endrange_.x &&
			MousePos.y >= startrange_.y && MousePos.y <= endrange_.y)
		{
			SetPos(MousePos);
		}

		if (MousePos.y <= startrange_.y)
		{
			if (MousePos.x <= startrange_.x)
			{
				SetPos(float4(startrange_.x, startrange_.y));
			}
			else if (MousePos.x >= endrange_.x)
			{
				SetPos(float4(endrange_.x, endrange_.y));
			}
			else
			{
				SetPos(float4(MousePos.x, startrange_.y));
			}
		}

		if (MousePos.y >= endrange_.y)
		{
			if (MousePos.x <= startrange_.x)
			{
				SetPos(float4(startrange_.x, endrange_.y));
			}
			else if (MousePos.x >= endrange_.x)
			{
				SetPos(float4(endrange_.x, endrange_.y));
			}
			else
			{
				SetPos(float4(MousePos.x, endrange_.y));
			}
		}

		if (MousePos.x <= startrange_.x)
		{
			if (MousePos.y <= startrange_.y)
			{
				SetPos(float4(startrange_.x, startrange_.y));
			}
			else if (MousePos.y >= endrange_.y)
			{
				SetPos(float4(startrange_.x, endrange_.y));
			}
			else
			{
				SetPos(float4(startrange_.x, MousePos.y));
			}
		}

		if (MousePos.x >= endrange_.x)
		{
			if (MousePos.y <= startrange_.y)
			{
				SetPos(float4(endrange_.x, startrange_.y));
			}
			else if (MousePos.y >= endrange_.y)
			{
				SetPos(float4(endrange_.x, endrange_.y));
			}
			else
			{
				SetPos(float4(endrange_.x, MousePos.y));
			}
		}
	}
	else
	{
		SetPos(MousePos);
	}
}

void MouseObject::UpdateAfter()
{

}

void MouseObject::Render()
{
	mainrenderer_->Render();
}
