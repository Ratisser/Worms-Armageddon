#pragma once
#include <GameEngineActor.h>

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineRenderer;
class GameEngineCollision;
class MouseObject : public GameEngineActor
{
private:	// member Var
	GameEngineRenderer* mainrenderer_;
	GameEngineCollision* maincollision_;

private:
	float4 finalpos_;	// ���콺�� ��������ġ
	float4 startrange_;	// ���콺 �̵����ѹ��� ������
	float4 endrange_;		// ���콺 �̵����ѹ��� ����

private:
	float4 rendersize_;

public:
	MouseObject(); // default constructer ����Ʈ ������
	~MouseObject(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	MouseObject(const MouseObject& _other) = delete; // default Copy constructer ����Ʈ ���������
	MouseObject(MouseObject&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	MouseObject& operator=(const MouseObject& _other) = delete; // default Copy operator ����Ʈ ���� ������
	MouseObject& operator=(const MouseObject&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	GameEngineCollision* GetMouseCol();
	void SetMoveRange(const float4& _Start, const float4& _End);
	void SetFinalPos(const float4& _FinalPos);
	void MoveMousePos(bool _Flag = true);

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;
};
