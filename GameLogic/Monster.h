#pragma once
#include <GameEngineActor.h>
#include <GameEngineFSM.h>

// �з� :
// �뵵 :
// ���� :
class GameEngineCollision;
class Monster : public GameEngineActor
{
public:
	GameEngineCollision* MonsterBodyCollision;


public:		
	Monster(); // default constructer ����Ʈ ������
	~Monster(); // default destructer ����Ʈ �Ҹ���

public:		// delete constructer
	Monster(const Monster& _other) = delete; // default Copy constructer ����Ʈ ���������
	Monster(Monster&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

public:		//delete operator
	Monster& operator=(const Monster& _other) = delete; // default Copy operator ����Ʈ ���� ������
	Monster& operator=(const Monster&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:		//member Func
	void Start() override;
	void Collision() override;
	void Render() override; 
};

