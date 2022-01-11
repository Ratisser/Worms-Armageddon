#pragma once

#include <GameEngineActor.h>
class GameEngineRenderer;
class Worm : public GameEngineActor
{
public:
	Worm();
	~Worm();

	Worm(const Worm& _other) = delete; // default Copy constructer ����Ʈ ���������
	Worm(Worm&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

	Worm& operator=(const Worm& _other) = delete; // default Copy operator ����Ʈ ���� ������
	Worm& operator=(const Worm&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

private:
	GameEngineRenderer* mainRender_;

};

