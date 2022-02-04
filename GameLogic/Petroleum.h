#pragma once
#include <GameEngineActor.h>

class Petroleum : public GameEngineActor
{
private:	// member Var
	GameEngineRenderer* mainSpriteRender_;

	GameEngineCollision* groundCollision_; // �ٴ�
	GameEngineCollision* BodyCollision_; // ����

	float4 Dir_;
	float4 prevPos_;

	float degree_;
	float deltaTime_;

	float WindAcc_;
	float WindSpeed_;
	float GravityAcc;
	float GravitySpeed;

	bool Burn_;
	bool Isground_;
	bool CountSecond_[5]; // ������ �ʸ� ���� ���� �迭

	float Cur_LifeTime_;
	float Max_LifeTime_;

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

public:
	void SetDir(float4 _Dir)
	{
		Dir_ = _Dir;
	}

	void SetDir(float _Dirx , float _Diry)
	{
		Dir_.x = _Dirx;
		Dir_.y = _Diry;
		Dir_.z = 0.f;
	}

	void SetWindSpeed(float _WindSpeed)
	{
		WindAcc_ = _WindSpeed / 150.f;
	}

	float tempfuc(float degree)
	{

		degree *= -1;
		degree += 90;


		if (degree < 0)
		{
			degree += 360;
		}

		return degree;
	}

};

