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

WeaponSheet::~WeaponSheet() // default destructer ����Ʈ �Ҹ���
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
	// ������ ���� �� ī�޶��� ����
	SetRenderOrder(9999);
	mainrenderer = CreateRenderer("WeaponSheet");
	mainrenderer->SetCameraEffectOff();
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

	// ��� ��������� Active���� ����
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

	// ���콺 ����
	float4 MouseRange = float4(activetargetpos_.x - (mainrenderer->GetImageSize().x * 0.5f), activetargetpos_.y - (mainrenderer->GetImageSize().y * 0.5f));

	mouseobject_ = GetLevel()->CreateActor<MouseObject>();
	mouseobject_->SetMoveRange(MouseRange, MouseRange + mainrenderer->GetImageSize());
	mouseobject_->SetFinalPos(MouseRange); // �ʱ���ġ
	mouseobject_->SetPos(MouseRange);
	mouseobject_->Off();

	// Weapon Icon �̸������ �����Ѵ�
	weaponnamelist_.resize(static_cast<int>(eItemList::MAX));
	weaponnamelist_[0] = "bazooka";
	weaponnamelist_[1] = "hmissile";

	// Weapon Icon ����� �����Ѵ�
	float4 PrevActivepos = float4({ Resolution.x - 143.f, Resolution.y - 424.f });

	int Count = 0;
	//for (int x = 0; x < static_cast<int>(weaponnamelist_.size()); ++x)
	for (int x = 0; x < 1; ++x)
	{
		if (4 == x)
		{
			++Count;
		}

		// �ű� �����۾����� �����ϸ� �⺻ Off���·μ�����
		WeaponIcon* NewIcon = GetLevel()->CreateActor<WeaponIcon>();
		NewIcon->SetWeaponName(weaponnamelist_[x]);
		NewIcon->SetWeaponType(eItemList::ITEM_BAZOOKAR);
		NewIcon->SetWeaponIndex(x, Count);

		// Weapon Icon�� �ε��������� ��Ȱ��/Ȱ�� ��ġ �ʱ�ȭ(��ġ��길���ߵ�)
		
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
	// �÷��̾�κ��� ���� �����۸���� �̿��Ͽ� Ȱ��ȭ�� �����۾������� �����ϸ� ��ġ����� �Ͽ� �ʱ� ��ġ�� ����
	std::map<std::string, Weapon*> CurWeaponList = _WeaponList;

	std::map<std::string, Weapon*>::iterator ListStart = CurWeaponList.begin();
	std::map<std::string, Weapon*>::iterator ListEnd = CurWeaponList.end();
	for (; ListStart != ListEnd; ++ListStart)
	{
		// ������ ��




	}

	



}

