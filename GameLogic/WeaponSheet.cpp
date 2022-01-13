#include "WeaponSheet.h"
#include "eCollisionGroup.h"

#include "MouseObject.h"
#include "WeaponIcon.h"

#include <GameEngineLevel.h>
#include <GameEngineRenderer.h>
#include <GameEngineCollision.h>

#include <GameEngineWindow.h>
#include <GameEngineTime.h>

WeaponSheet::WeaponSheet() :
	active_(false),
	prevstate_(false),
	mainrenderer(nullptr),
	mouseobject_(nullptr),
	activetargetpos_(float4::ZERO),
	disabletargetpos_(float4::ZERO),
	moving_(false),
	movingspeed(0.9f),
	movepos_(float4::ZERO)
{
}

WeaponSheet::~WeaponSheet() // default destructer 디폴트 소멸자
{
}

WeaponSheet::WeaponSheet(WeaponSheet&& _other) noexcept :
	active_(_other.active_),
	prevstate_(_other.prevstate_),
	mainrenderer(_other.mainrenderer),
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
	// 렌더러 생성 및 카메라영향 제거
	SetRenderOrder(9999);
	mainrenderer = CreateRenderer("WeaponSheet");
	mainrenderer->SetCameraEffectOff();
}

void WeaponSheet::UpdateBefore()
{

}

void WeaponSheet::Update()
{
	// 어딘가로부터 키입력시 활성화/비활성화
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

		// 비활성화시에는 바로 Off시킴
		if (true == prevstate_)
		{
			mouseobject_->Off();
			mouseobject_->SetFinalPos(mouseobject_->GetPos());
		}
	}

	// 이동중이 아닐때 이전상태와 현재 상태가 다를때 처리
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

}

void WeaponSheet::Render()
{
	mainrenderer->Render();
}

void WeaponSheet::WeaponSheetActive()
{
	if (false == active_)
	{
		active_ = true;
	}
	else
	{
		active_ = false;
	}

	// 모든 무기아이콘 Active상태 설정
	std::map<std::string, WeaponIcon*>::iterator IconStart = weaponiconlist_.begin();
	std::map<std::string, WeaponIcon*>::iterator IconEnd = weaponiconlist_.end();
	for (; IconStart != IconEnd; ++IconStart)
	{
		IconStart->second->SetActive(active_);
	}
}

void WeaponSheet::SetRenderPos(const float4& _Active, const float4& _Disable)
{
	float4 Resolution = GameEngineWindow::GetInst().GetSize();

	activetargetpos_ = _Active;
	disabletargetpos_ = _Disable;

	SetPos(disabletargetpos_);

	// 마우스 저장
	float4 MouseRange = float4(activetargetpos_.x - (mainrenderer->GetImageSize().x * 0.5f), activetargetpos_.y - (mainrenderer->GetImageSize().y * 0.5f));

	mouseobject_ = GetLevel()->CreateActor<MouseObject>();
	mouseobject_->SetMoveRange(MouseRange, MouseRange + mainrenderer->GetImageSize());
	mouseobject_->SetFinalPos(MouseRange); // 초기위치
	mouseobject_->SetPos(MouseRange);
	mouseobject_->Off();

	// Weapon Icon 이름목록을 생성한다
	weaponnamelist_.resize(static_cast<int>(eItemList::MAX));
	weaponnamelist_[0] = "bazooka";
	weaponnamelist_[1] = "hmissile";

	// Weapon Icon 목록을 생성한다
	float4 PrevActivepos = float4({ Resolution.x - 143.f, Resolution.y - 424.f });

	int Count = 0;
	//for (int x = 0; x < static_cast<int>(weaponnamelist_.size()); ++x)
	for (int x = 0; x < 1; ++x)
	{
		if (4 == x)
		{
			++Count;
		}

		// 신규 아이템아이콘 생성하며 기본 Off상태로설정됨
		WeaponIcon* NewIcon = GetLevel()->CreateActor<WeaponIcon>();
		NewIcon->SetWeaponName(weaponnamelist_[x]);
		NewIcon->SetWeaponType(eItemList::ITEM_BAZOOKAR);
		NewIcon->SetWeaponIndex(x, Count);

		// Weapon Icon의 인덱스에따라 비활성/활성 위치 초기화(위치계산만들어야됨)
		
		float4 ActivePos = float4({ Resolution.x - 143.f + (x * 32.f), Resolution.y - 424.f + (Count * 32.f)});
		
		//float4 disEnablePos = float4({ Resolution.x + ((4 - x) * 32.f) - 143.f, Resolution.y - 424.f + (Count * 32.f) });
		float4 disEnablePos = float4({ PrevActivepos.x + ((6 - x) * 32.f) + 8.f, Resolution.y - 424.f + (Count * 32.f) });
		NewIcon->SetWeaponRenderPos(disEnablePos, ActivePos);

		weaponiconlist_.insert(std::pair<std::string, WeaponIcon*>(weaponnamelist_[x], NewIcon));

		PrevActivepos = ActivePos;
	}
}

void WeaponSheet::CreateWeaponIconList(const std::map<std::string, Weapon*>& _WeaponList)
{
	// 플레이어로부터 받은 아이템목록을 이용하여 활성화된 아이템아이콘을 생성하며 위치계산을 하여 초기 위치를 설정
	std::map<std::string, Weapon*> CurWeaponList = _WeaponList;

	std::map<std::string, Weapon*>::iterator ListStart = CurWeaponList.begin();
	std::map<std::string, Weapon*>::iterator ListEnd = CurWeaponList.end();
	for (; ListStart != ListEnd; ++ListStart)
	{
		// 아이템 명




	}

	



}

