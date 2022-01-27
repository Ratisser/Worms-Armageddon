#pragma once
#include <map>
#include <vector>
#include <GameEngineActor.h>

#include "eItemList.h"

class Worm;
class WeaponSheet;
class BottomNameTag;
class BottomFlag;
class BottomHealthBar;
class Weapon;
class WormName;
class UIController : public GameEngineActor
{
private:	// member Var
	Worm* curplayer_;	// ���� �ش� ��������ڸ� ����ϴ� ��ü

private:	// �����ϴ� ��� UI
	// Weapon Sheet ����
	WeaponSheet* weaponsheet_;
	// ȭ���ϴ� �� �������ͽ� ����
	BottomNameTag* bottomNameTag_;
	BottomFlag* bottomFlag_;
	BottomHealthBar* bottomHealthBar_;

	//
	WormName* curWormName_;


public:
	UIController(); // default constructer ����Ʈ ������
	~UIController(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	UIController(const UIController& _other) = delete; // default Copy constructer ����Ʈ ���������
	UIController(UIController&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	UIController& operator=(const UIController& _other) = delete; // default Copy operator ����Ʈ ���� ������
	UIController& operator=(const UIController&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public: // �÷��̾ ��ü ������ �ݵ�� �����ؾ��ϴ� �׸�
	void SetCurPlayer(Worm* _curplayer);																	// �÷��̾��
	void CreateWeaponList(const std::vector<eItemList>& _weaponlist);			// �������ִ� �����ϼ���(���ʼ�����)
	
public: // �÷��̾ ��Ϳ�����Ʈ ȹ�� �Ǵ� �����ۻ��� �����ؾ��ϴ� �׸�
	void AddWeapon(eItemList _Weapon);																// ��Ϳ�����Ʈ�� ���� ���⸦ ȹ��������
	void UseWeapon(eItemList _Weapon);																// ���⸦ ���������

public:
	Worm* GetCurPlayer() const;
	WeaponSheet* GetCurWeaponSheet() const;
	BottomNameTag* GetCurBottomNameTag() const;
	BottomFlag* GetCurBottomFlag() const;
	BottomHealthBar* GetCurBottomHealthBar();

	WormName* GetCurWormName();


public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

};

