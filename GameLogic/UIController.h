#pragma once
#include <GameEngineActor.h>

// �з� : UI ���� ������
class Worm;
class WeaponSheet;
class UIController : public GameEngineActor
{
private:	// member Var
	Worm* curplayer_;	// ���� �ش� ��������ڸ� ����ϴ� ��ü

private:	// �����ϴ� ��� UI
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

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

};

