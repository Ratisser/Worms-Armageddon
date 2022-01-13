#include "WeaponIcon.h"
#include "eCollisionGroup.h"

#include <GameEngineLevel.h>
#include <GameEngineRenderer.h>
#include <GameEngineCollision.h>

#include <GameEngineWindow.h>
#include <GameEngineTime.h>

WeaponIcon::WeaponIcon() :
	indexX_(-1),
	indexY_(-1),
	active_(false),
	prevstate_(false),
	weapontype_(eItemList::MAX),
	activetargetpos_(float4::ZERO),
	disabletargetpos_(float4::ZERO),
	moving_(false),
	movingspeed(0.9f),
	movepos_(float4::ZERO),
	mainrenderer_(nullptr),
	selectrenderer_(nullptr),
	maincollision_(nullptr)
{\
}

WeaponIcon::~WeaponIcon() // default destructer 디폴트 소멸자
{

}

WeaponIcon::WeaponIcon(WeaponIcon&& _other) noexcept :
	indexX_(_other.indexX_),
	indexY_(_other.indexY_),
	active_(_other.active_),
	prevstate_(_other.prevstate_),
	weapontype_(_other.weapontype_),
	activetargetpos_(_other.activetargetpos_),
	disabletargetpos_(_other.disabletargetpos_),
	moving_(_other.moving_),
	movingspeed(_other.movingspeed),
	movepos_(_other.movepos_),
	mainrenderer_(_other.mainrenderer_),
	selectrenderer_(_other.selectrenderer_),
	maincollision_(_other.maincollision_)
{
}

void WeaponIcon::SetWeaponName(const std::string& _Name)
{
	// 이름이 설정될때 렌더링객체를 지정
	weaponname_ = _Name;

	if (nullptr == mainrenderer_)
	{
		mainrenderer_ = CreateRenderer(weaponname_);
		mainrenderer_->SetCameraEffectOff();
	}
}

void WeaponIcon::SetWeaponType(eItemList _Type)
{
	weapontype_ = _Type;
}

void WeaponIcon::SetWeaponRenderPos(const float4& _DisableRenderPos, const float4& _ActiveRenderPos)
{
	disabletargetpos_ = _DisableRenderPos;
	activetargetpos_ = _ActiveRenderPos;

	// 초기위치(비활성화)
	SetPos(disabletargetpos_);
}

void WeaponIcon::SetWeaponIndex(int _X, int _Y)
{
	if (0 > _X)
	{
		return;
	}
	indexX_ = _X;

	if (0 > _Y)
	{
		return;
	}
	indexY_ = _Y;
}

GameEngineCollision* WeaponIcon::GetCurIconCol() const
{
	return maincollision_;
}

void WeaponIcon::SetActive(bool _Active)
{
	active_ = _Active;
}

void WeaponIcon::Start()
{
	SetRenderOrder(10001);

	// 선택렌더러 생성
	selectrenderer_ = CreateRenderer("SelectBox");
	selectrenderer_->Off();

	// 충돌체 생성
	maincollision_ = CreateCollision(static_cast<int>(eCollisionGroup::UI), CollisionCheckType::RECT);
}

void WeaponIcon::UpdateBefore()
{
}

void WeaponIcon::Update()
{
	if (true == active_) // 비활성화 -> 활성화
	{
		// 만약 활성화 타겟위치까지 이동했다면 중단
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
	else // 활성화 -> 비활성화
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
	}

	if (false == moving_)
	{
		movepos_ = float4::ZERO;

		if (prevstate_ != active_)
		{
			prevstate_ = active_;
		}
	}
}

void WeaponIcon::UpdateAfter()
{
}

void WeaponIcon::Render()
{
	if (nullptr != mainrenderer_)
	{
		mainrenderer_->Render();
	}

	// 마우스와 충돌했을때만 선택상자 렌더링
	if (true == selectrenderer_->IsOn())
	{
		selectrenderer_->Render();
	}
}

