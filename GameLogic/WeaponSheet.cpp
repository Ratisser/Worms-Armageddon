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

WeaponSheet::~WeaponSheet() // default destructer 디폴트 소멸자
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
	// 렌더러 생성 및 카메라영향 제거
	SetRenderOrder(9999);
	mainrenderer = CreateRenderer("WeaponSheet");
	mainrenderer->SetCameraEffectOff();

	// 충돌체 생성
	//maincollision_ = CreateCollision(static_cast<int>(eCollisionGroup::UI), CollisionCheckType::RECT);

	// 활성/비활성 타겟위치 초기화
	float4 Resolution = GameEngineWindow::GetInst().GetSize();
	activetargetpos_ = float4(Resolution.x - 100.f, Resolution.y - 240.f);	// 활성화위치
	disabletargetpos_ = float4(Resolution.x + 100.f, Resolution.y - 240.f);	// 비활성화위치

	// 마우스 저장
	float4 MouseRange = float4(activetargetpos_.x - (mainrenderer->GetImageSize().x * 0.5f), activetargetpos_.y - (mainrenderer->GetImageSize().y * 0.5f));

	mouseobject_ = GetLevel()->CreateActor<MouseObject>();
	mouseobject_->SetMoveRange(MouseRange, MouseRange + mainrenderer->GetImageSize());
	mouseobject_->SetFinalPos(MouseRange); // 초기위치
	mouseobject_->SetPos(MouseRange);
	mouseobject_->Off();
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
	// 렌더링전 마우스와 WeaponSheet 충돌체크
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
	// 플레이어로부터 받은 아이템목록을 이용하여 활성화된 아이템아이콘을 생성하며 위치계산을 하여 초기 위치를 설정
	std::map<std::string, Weapon*> CurWeaponList = _WeaponList;

	std::map<std::string, Weapon*>::iterator ListStart = CurWeaponList.begin();
	std::map<std::string, Weapon*>::iterator ListEnd = CurWeaponList.end();
	for (; ListStart != ListEnd; ++ListStart)
	{
		// 아이템 명




	}

	



}

