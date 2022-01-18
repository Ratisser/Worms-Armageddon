#pragma once
#include <GameEngineLevel.h>
#include "WaterLevel.h"
#include "MapGround.h"
// �з� : 
// �뵵 : 
// ���� : 

class FadeObject;
class WindController;
class PlayLevel : public GameEngineLevel
{
private:	// member Var
	class MapTrain* Train_;
	class MapGround* Ground_;
	class Bazooka* Bazooka_;
	class Worm* Worm_[8];
	int FocusWormNumber_;
	bool IsCameraMove_;
	bool isDebugOn_;
	float4 CameraPos_;

private:
	GameEngineMath::Random randomGenerator_;
	bool isWormLanded_;
	bool isFadeIn_;
	static FadeObject* fadeObject_;
	float fadeInterTime_;

public:
	PlayLevel(); // default constructer ����Ʈ ������
	~PlayLevel(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	PlayLevel(const PlayLevel& _other) = delete; // default Copy constructer ����Ʈ ���������
	PlayLevel(PlayLevel&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	PlayLevel& operator=(const PlayLevel& _other) = delete; // default Copy operator ����Ʈ ���� ������
	PlayLevel& operator=(const PlayLevel&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	void Loading() override;
	void LevelUpdate() override;
	void LevelUpdateBefore() override;


	void Testfunc(); // �׽�Ʈ��, �׽�Ʈ�� �Լ� ����
	void TestUpdate();
public:
	WaterLevel* WaterLevel_; // ���� ������ - ����
	WindController* windController_;

public:
	void MakeWaterLevel();
	void CreateGimmickObject();
	void CreateExplosion(); //test
	void AJYGround(float4 _pos);

private:
	void AJYLoading();
	void AJYLevelUpdate();
	void PJWLevelUpdate();
private:
	void RandomWormArrange(float _minX, float _maxX);
};

