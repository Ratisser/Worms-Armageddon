#pragma once
#include <GameEngineActor.h>
// �з� : 
// �뵵 : 
// ���� : 
class Worm;
class GameController;
class WormArrow : public GameEngineActor
{
private:	// member Var
	GameEngineRenderer* mainRender_;
	Worm* parent_;
	GameController* controller_;

	bool isGoingUp_;

public:
	WormArrow(); // default constructer ����Ʈ ������
	~WormArrow(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	WormArrow(const WormArrow& _other) = delete; // default Copy constructer ����Ʈ ���������
	WormArrow(WormArrow&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	WormArrow& operator=(const WormArrow& _other) = delete; // default Copy operator ����Ʈ ���� ������
	WormArrow& operator=(const WormArrow&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	void SetParent(Worm* _parent)
	{
		parent_ = _parent;
	}

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;
};

