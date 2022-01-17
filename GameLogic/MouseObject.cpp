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

MouseObject::~MouseObject() // default destructer 디폴트 소멸자
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
	// 무기창 활성화되었을때 무기아이콘과 충돌상태일때
	// 마우스왼쪽버튼 클릭시 해당 무기 선택으로판단하여 현재채택무기를 변경하고
	// 무기창을 비활성화시킨다.
	GameEngineCollision* ColUI = maincollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::UI));
	if (nullptr != ColUI)
	{
		WeaponIcon* CollisionWeapon = dynamic_cast<WeaponIcon*>(ColUI->GetActor());
		if (nullptr != CollisionWeapon)
		{
			// 해당 아이템이 활성화 상태이고, 남은갯수가 0이 아니면 
			if (true == CollisionWeapon->IsMainrendererOn() /*&& aaa*/)
			{
				// 마우스왼쪽버튼클릭이라면
				if (true == GameEngineInput::GetInst().IsDown("Boom"))
				{
					// 현재 충돌한 무기아이콘이 어떠한 시트에 속하며, 어떠한 UI 제어기에 속한지 찾아내어
					// UI Controller를 생성한 플레이어에게 현재 선택된 무기 타입전달
					eItemList CurWeapon = CollisionWeapon->GetWeaponType();
					Worm* CurPlayer = CollisionWeapon->GetParentSheet()->GetParentController()->GetCurPlayer();
					if (nullptr != CurPlayer)
					{
						// 현재플레이어가 있다면 해당 타입 전달
						//CurPlayer



						int a = 0;
					}

					// 선택완료되었다고 판단하여 무기창을 비활성화한다.
					// 단, 해당 무기창 비활성화는 무기아이콘이 활성화되어있는 상태일때만 가능
					CollisionWeapon->GetParentSheet()->WeaponSheetActive();
				}
			}
		}
	}
}

void MouseObject::Update()
{
	// 위치 갱신(단, 이동범위를 벗어나면 갱신안함)
	float4 MousePos = GameEngineWindow::GetInst().GetMousePos();

	// 무기창이 활성화되면 지정된범위 밖으로 커서 이동불가
	// 무기창이 비활성화면 자유롭게 이동
	if (true == WeaponSheet::isweaponsheet())
	{
		// 범위지정이 되있다면
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
