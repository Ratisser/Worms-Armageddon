#pragma once
#include <GameEngineActor.h>

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineRenderer;
class WeaponSheet : public GameEngineActor
{
private:	// member Var
	GameEngineRenderer* MainRenderer_;

public:
	WeaponSheet(); // default constructer ����Ʈ ������
	~WeaponSheet(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	WeaponSheet(const WeaponSheet& _other) = delete; // default Copy constructer ����Ʈ ���������
	WeaponSheet(WeaponSheet&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	WeaponSheet& operator=(const WeaponSheet& _other) = delete; // default Copy operator ����Ʈ ���� ������
	WeaponSheet& operator=(const WeaponSheet&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;
};

