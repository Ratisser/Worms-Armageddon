#pragma once
#include <GameEngineActor.h>

class TimerManager;
class TimerDigit : public GameEngineActor
{
private:	// member Var
	GameEngineRenderer* mainRender_;
	TimerManager* timerManager_;

	float curCount_;

public:
	TimerDigit(); // default constructer ����Ʈ ������
	~TimerDigit(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	TimerDigit(const TimerDigit& _other) = delete; // default Copy constructer ����Ʈ ���������
	TimerDigit(TimerDigit&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	TimerDigit& operator=(const TimerDigit& _other) = delete; // default Copy operator ����Ʈ ���� ������
	TimerDigit& operator=(const TimerDigit&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	void AnimationInit();
	float GetCurTime();

public:

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;
};

