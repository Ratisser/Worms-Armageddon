#pragma once
#include <string>
#include "eItemList.h"

// �з� : ���� ����
// �뵵 : 
// ���� : 
class Weapon
{
private:	// member Var
	std::string itemname_;	// ���� �̸�
	eItemList itemtype;			// ���� Ÿ��
	int remaincnt_;				// ���� ��������
	bool active_;					// ���� Ȱ��ȭ/��Ȱ��ȭ����

public:
	Weapon();
	~Weapon();

public:
	void SetItemSpec(const std::string& _Name, eItemList _ItemType, int _Cnt, bool _Active);
	void WeaponUse();
};

