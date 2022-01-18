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


public:
	WaterLevel* WaterLevel_; // ���� ������ - ����
	WindController* windController_;

public:
	void MakeWaterLevel();
	void CreateGimmickObject();
	void AJYGround(float4 _pos);

	void CreateExplosion100(float4 Pos); //test
	void CreateExplosion75(float4 Pos); //test
	void CreateExplosion50(float4 Pos); //test
	void CreateExplosion25(float4 Pos); //test
private:
	void AJYLoading();
	void wormLoading();
	void AJYLevelUpdate();
	void PJWLevelUpdate();
private:
	void RandomWormArrange(float _minX, float _maxX);
};

