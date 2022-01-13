#pragma once
#include <GameEngineActor.h>
#include "eItemList.h"

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineRenderer;
class GameEngineCollision;
class WeaponIcon : public GameEngineActor
{
private:	// member Var
	std::string itemname_;
	eItemList itemtype_;
	int indexX_;
	int indexY_;
	int index_;
	float4 renderpos_;

private:
	GameEngineRenderer* mainrenderer_;
	GameEngineCollision* maincollision_;

public:
	WeaponIcon(); // default constructer ����Ʈ ������
	~WeaponIcon(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	WeaponIcon(const WeaponIcon& _other) = delete; // default Copy constructer ����Ʈ ���������
	WeaponIcon(WeaponIcon&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	WeaponIcon& operator=(const WeaponIcon& _other) = delete; // default Copy operator ����Ʈ ���� ������
	WeaponIcon& operator=(const WeaponIcon&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;
};

