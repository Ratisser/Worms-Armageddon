#pragma once
#include <GameEngineActor.h>
// �з� :
// �뵵 :
// ���� :
class PlayBack : public GameEngineActor
{
public:	// member Var
	static GameEngineCollision* MapCollision;

public:		
	PlayBack(); // default constructer ����Ʈ ������
	~PlayBack(); // default destructer ����Ʈ �Ҹ���

public:		// delete constructer
	PlayBack(const PlayBack& _other) = delete; // default Copy constructer ����Ʈ ���������
	PlayBack(PlayBack&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

public:		//delete operator
	PlayBack& operator=(const PlayBack& _other) = delete; // default Copy operator ����Ʈ ���� ������
	PlayBack& operator=(const PlayBack&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:		//member Func
	void Start();
	void Render();
};

