#include "MouseObject.h"
#include "eCollisionGroup.h"

#include <GameEngineLevel.h>
#include <GameEngineRenderer.h>
#include <GameEngineCollision.h>

#include <GameEngineWindow.h>
#include <GameEngineTime.h>

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
	SetRenderOrder(10009);
	mainrenderer_ = CreateRenderer("Cursor");
	mainrenderer_->SetRenderSize(float4(32.f, 32.f));
	mainrenderer_->SetCameraEffectOff();

	maincollision_ = CreateCollision(static_cast<int>(eCollisionGroup::MOUSE), CollisionCheckType::POINT);

	rendersize_ = mainrenderer_->GetImageSize();

	ShowCursor(false);
}

void MouseObject::UpdateBefore()
{
}

void MouseObject::Update()
{
	// 위치 갱신(단, 이동범위를 벗어나면 갱신안함)
	float4 MousePos = GameEngineWindow::GetInst().GetMousePos();
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

void MouseObject::UpdateAfter()
{
}

void MouseObject::Render()
{
	mainrenderer_->Render();
}
