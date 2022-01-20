#pragma once
#include <GameEngineActor.h>

class Petroleum : public GameEngineActor
{
private:	// member Var
	GameEngineRenderer* mainSpriteRender_;

	GameEngineCollision* groundCollision_; // �ٴ�
	GameEngineCollision* BodyCollision_; // ����

	float LifeTime_;

	// �������� ����, Ȥ�� ȭ���� �����ð� ����Ǿ��� ���
	// Phase_ ��ġ�� ���� �巳���� ���ϸ��̼�(������ ����)�� ����ǰ�,
	// ���� �̻��� �Ǹ� ����

public:
	Petroleum(); // default constructer ����Ʈ ������
	~Petroleum(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	Petroleum(const Petroleum& _other) = delete; // default Copy constructer ����Ʈ ���������
	Petroleum(Petroleum&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	Petroleum& operator=(const Petroleum& _other) = delete; // default Copy operator ����Ʈ ���� ������
	Petroleum& operator=(const Petroleum&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

private:
	void initCollision();
};

