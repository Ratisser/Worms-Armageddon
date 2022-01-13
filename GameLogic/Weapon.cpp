#include "Weapon.h"

Weapon::Weapon() :
	itemtype(eItemList::MAX),
	remaincnt_(-1),
	active_(false)
{
}

Weapon::~Weapon() // default destructer ����Ʈ �Ҹ���
{

}

void Weapon::SetItemSpec(const std::string& _Name, eItemList _ItemType, int _Cnt, bool _Active)
{
	// �ش� �������� �ʱ�Ӽ� ����
	itemname_ = _Name;
	itemtype = _ItemType;
	remaincnt_ = _Cnt;
	active_ = _Active;
}

void Weapon::WeaponUse()
{
	// �ش� �������� ���������� üũ
	if (0 >= remaincnt_)
	{
		active_ = false;
		remaincnt_ = 0;
		return;
	}

	remaincnt_ -= 1;
}

