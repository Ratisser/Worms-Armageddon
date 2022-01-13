#pragma once
#include <map>
#include <GameEngineActor.h>

// �⺻���� : �÷��̾ UIController�� ��ü�� ������ �ش� ��ü�� �����۸���� �Ѱ��ָ�
//                   �ش� UIController�� �ش� ����� WeaponSheet�� �ѱ��
//                   ������ WeaponSheet�� WeaponIcon ����� ���� �����Ѵ�.
//                   
class Worm;
class WeaponSheet;
class Weapon;
class UIController : public GameEngineActor
{
private:	// member Var
	Worm* curplayer_;	// ���� �ش� ��������ڸ� ����ϴ� ��ü

private:	// �����ϴ� ��� UI

	// Weapon Sheet ����
	WeaponSheet* weaponsheet_;

public:
	UIController(); // default constructer ����Ʈ ������
	~UIController(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	UIController(const UIController& _other) = delete; // default Copy constructer ����Ʈ ���������
	UIController(UIController&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	UIController& operator=(const UIController& _other) = delete; // default Copy operator ����Ʈ ���� ������
	UIController& operator=(const UIController&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	void SetCurPlayer(Worm* _curplayer);
	void SetCurItemList(const std::map<std::string, Weapon*>& _WeaponList);

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

};

