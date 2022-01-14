#include "WeaponSheet.h"
#include "eCollisionGroup.h"

#include "MouseObject.h"
#include "WeaponIcon.h"
#include "Weapon.h"

#include <GameEngineLevel.h>
#include <GameEngineRenderer.h>
#include <GameEngineCollision.h>

#include <GameEngineWindow.h>
#include <GameEngineTime.h>

bool WeaponSheet::weaponsheetactive_ = false;

bool WeaponSheet::isweaponsheet()
{
	return weaponsheetactive_;
}

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

	// ������ �⺻��ġ ���� �� �����ܾ��� ����
	CreateIconDefaultPos();
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
			weaponsheetactive_ = true;
		}
	}
	else // Ȱ��ȭ -> ��Ȱ��ȭ
	{
		// ��Ȱ���ÿ��� �ٷ� ���콺��ġ ���ڸ��ε�����.
		weaponsheetactive_ = false;

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
			mouseobject_->SetFinalPos(mouseobject_->GetPos());
		}
	}

	// �̵����� �ƴҶ� �������¿� ���� ���°� �ٸ��� ó��
	if (false == moving_)
	{
		movepos_ = float4::ZERO;

		if (prevstate_ != active_)
		{
			prevstate_ = active_;
		}
	}
}

void WeaponSheet::UpdateAfter()
{
}

void WeaponSheet::Render()
{
	mainrenderer->Render();
}

void WeaponSheet::WeaponSheetActive()
{
	// ��ü������ Ȱ��ȭ/��Ȱ��ȭ ���� ����
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

	// ���콺 ���ѵ� ��ġ�̵� ���� �� ���콺 ����
	SetMouseObject();
}

void WeaponSheet::SetMouseObject()
{
	// ���콺 ����
	float4 MouseRange = float4(activetargetpos_.x - (mainrenderer->GetImageSize().x * 0.5f), activetargetpos_.y - (mainrenderer->GetImageSize().y * 0.5f));
	mouseobject_ = GetLevel()->CreateActor<MouseObject>();
	mouseobject_->SetMoveRange(MouseRange, MouseRange + mainrenderer->GetImageSize());
	mouseobject_->SetFinalPos(MouseRange); // �ʱ���ġ
	mouseobject_->SetPos(MouseRange);
}

void WeaponSheet::SetIconName()
{
	// Weapon Icon �̸������ �����Ѵ�
	weaponnamelist_.resize(static_cast<int>(eItemList::MAX));
	weaponnamelist_[0] = "bazooka";
	weaponnamelist_[1] = "hmissile";
	weaponnamelist_[2] = "test1";
	weaponnamelist_[3] = "test2";
	weaponnamelist_[4] = "test3";
	weaponnamelist_[5] = "test4";
	weaponnamelist_[6] = "test5";
	weaponnamelist_[7] = "test6";
	weaponnamelist_[8] = "test7";
	weaponnamelist_[9] = "test8";
	weaponnamelist_[10] = "test9";
	weaponnamelist_[11] = "test10";
	weaponnamelist_[12] = "test11";
	weaponnamelist_[13] = "test12";
	weaponnamelist_[14] = "test13";
	weaponnamelist_[15] = "test14";
	weaponnamelist_[16] = "test15";
	weaponnamelist_[17] = "test16";
	weaponnamelist_[18] = "test17";
	weaponnamelist_[19] = "test18";
	weaponnamelist_[20] = "test19";
	weaponnamelist_[21] = "test20";
	weaponnamelist_[22] = "test21";
	weaponnamelist_[23] = "test22";
	weaponnamelist_[24] = "test23";
	weaponnamelist_[25] = "test24";
	weaponnamelist_[26] = "test25";
	weaponnamelist_[27] = "test26";
	weaponnamelist_[28] = "test27";
	weaponnamelist_[29] = "test28";
	weaponnamelist_[30] = "test29";
	weaponnamelist_[31] = "test30";
}

void WeaponSheet::CreateIconDefaultPos()
{
	float4 Resolution = GameEngineWindow::GetInst().GetSize();

	// Weapon Icon �̸� ����
	SetIconName();

	// Weapon Icon ����� �����Ѵ�
	int Count = 0;
	int Index = 0;
	for (int x = 0; x < static_cast<int>(weaponnamelist_.size()); ++x)
	{
		if (x % 5 == 0 && x != 0)
		{
			++Count;	// 5�� ������ y�� ����
			Index = 0;	// y�� ����Ǹ� �ε��� �ʱ�ȭ
		}

		// �ű� �����۾����� �����ϸ� �⺻ Off���·μ�����
		WeaponIcon* NewIcon = GetLevel()->CreateActor<WeaponIcon>();
		NewIcon->SetWeaponName(weaponnamelist_[x]);
		NewIcon->SetWeaponType(static_cast<eItemList>(x));
		NewIcon->SetWeaponIndex(Index, Count);

		// Weapon Icon�� �ε��������� ��Ȱ��/Ȱ�� ��ġ �ʱ�ȭ
		float4 ActivePos = float4({ Resolution.x - 141.f + ((float)Index * 28.f) + (Index + 1), Resolution.y - 422.f + (Count * 28.f) + (Count + 1) }); // Ȱ��ȭ�Ǿ����� ��ġ���
		float4 disEnablePos = ActivePos;
		disEnablePos.x = ActivePos.x + 200.f;
		NewIcon->SetWeaponRenderPos(disEnablePos, ActivePos);

		weaponiconlist_.insert(std::pair<std::string, WeaponIcon*>(weaponnamelist_[x], NewIcon));

		++Index;
	}
}

void WeaponSheet::CreateWeaponIconList(const std::vector<eItemList>& _WeaponList)
{
	// ������ ����Ȱ��ȭ ���� �ӽ�����
	std::vector<eItemList> ActiveWeapon = _WeaponList;
	size_t ActiveWeaponCnt = ActiveWeapon.size();
	size_t SearchCnt = 0;
	for (size_t i = 0; i < ActiveWeaponCnt; ++i)
	{
		// ��ü�׸��� �ݺ��ؼ� ��� ã�Ҵٸ� �ش� �ݺ��� �ߴ�
		if (SearchCnt >= ActiveWeaponCnt)
		{
			break;
		}

		std::map<std::string, WeaponIcon*>::iterator StartIter = weaponiconlist_.begin();
		std::map<std::string, WeaponIcon*>::iterator EndIter = weaponiconlist_.end();
		for (; StartIter != EndIter; ++StartIter)
		{
			// Ȱ��ȭ�� ������ Ÿ���̰���, �ش� ����������� ��Ȱ��ȭ����(�̹�ã���׸��� �ٽ�ã�°���Ǽ�����)���
			if (ActiveWeapon[i] == StartIter->second->GetWeaponType() && false == StartIter->second->IsMainrendererOn())
			{
				// �ش� ��������� Ȱ��ȭ����
				StartIter->second->SetMainRendererOn();

				// ���� ����������� ����(�ʱ����)
				// ������ ������ �ϴ� 3�� ����
				Weapon* NewWeapon = new Weapon();
				NewWeapon->SetItemSpec(StartIter->first, ActiveWeapon[i], 3, true);
				weapon_.insert(std::pair<eItemList, Weapon*>(ActiveWeapon[i], NewWeapon));

				// Ȱ��ȭ�� ����� ã�Ƴ��� Ȱ��ȭ��Ų��, �ٽ� Ȱ��ȭ����� Ž��
				++SearchCnt;
				i = 0;
				StartIter = weaponiconlist_.begin();
				break;
			}
		}
	}
}

Weapon* WeaponSheet::GetCruWeapon()
{
	return nullptr;
}

