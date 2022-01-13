#include "Weapon.h"

Weapon::Weapon() :
	itemtype(eItemList::MAX),
	remaincnt_(-1),
	active_(false)
{
}

Weapon::~Weapon() // default destructer 디폴트 소멸자
{

}

void Weapon::SetItemSpec(const std::string& _Name, eItemList _ItemType, int _Cnt, bool _Active)
{
	// 해당 아이템의 초기속성 설정
	itemname_ = _Name;
	itemtype = _ItemType;
	remaincnt_ = _Cnt;
	active_ = _Active;
}

void Weapon::WeaponUse()
{
	// 해당 아이템의 남은개수를 체크
	if (0 >= remaincnt_)
	{
		active_ = false;
		remaincnt_ = 0;
		return;
	}

	remaincnt_ -= 1;
}

