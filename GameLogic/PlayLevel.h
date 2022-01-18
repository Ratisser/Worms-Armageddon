#pragma once
#include <GameEngineLevel.h>
#include "WaterLevel.h"
#include "MapGround.h"
// 분류 : 
// 용도 : 
// 설명 : 

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
	PlayLevel(); // default constructer 디폴트 생성자
	~PlayLevel(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	PlayLevel(const PlayLevel& _other) = delete; // default Copy constructer 디폴트 복사생성자
	PlayLevel(PlayLevel&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	PlayLevel& operator=(const PlayLevel& _other) = delete; // default Copy operator 디폴트 대입 연산자
	PlayLevel& operator=(const PlayLevel&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	void Loading() override;
	void LevelUpdate() override;


public:
	WaterLevel* WaterLevel_; // 수면 조절용 - 이현
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

