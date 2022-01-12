#pragma once
#include <GameEngineActor.h>
#include <GameEngineMath.h>
// �з� : 
// �뵵 : 
// ���� : 

enum class ScatterState
{
	LEFT,
	RIGHT,
	NONE
};

class BackgroundScatterMaker;
class BackgroundScatter : public GameEngineActor
{
	friend BackgroundScatterMaker;

private:	// member Var
	GameEngineRenderer* mainRender_;

private:
	float windSpeed_;
	float fallSpeed_;
	float4 spawnPos_;
	GameEngineMath::Random randomGenerator_;

public:
	void SetWindSpeed(float _windSpeedFrom, float _windSpeedTo)
	{
		windSpeed_ = randomGenerator_.RandomFloat(_windSpeedFrom, _windSpeedTo);
	}

	void SetFallSpeed(float _fallSpeedFrom, float _fallSpeedTo)
	{
		fallSpeed_ = randomGenerator_.RandomFloat(_fallSpeedFrom, _fallSpeedTo);
	}

public:
	BackgroundScatter(); // default constructer ����Ʈ ������
	~BackgroundScatter(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	BackgroundScatter(const BackgroundScatter& _other) = delete; // default Copy constructer ����Ʈ ���������
	BackgroundScatter(BackgroundScatter&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	BackgroundScatter& operator=(const BackgroundScatter& _other) = delete; // default Copy operator ����Ʈ ���� ������
	BackgroundScatter& operator=(const BackgroundScatter&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

public:
	void ChangeState()
	{

	}
};

