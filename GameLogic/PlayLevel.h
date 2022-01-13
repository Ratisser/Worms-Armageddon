#pragma once
#include <GameEngineLevel.h>
#include "WaterLevel.h"
// 분류 : 
// 용도 : 
// 설명 : 
class PlayLevel : public GameEngineLevel
{
private:	// member Var
	class MapTrain* Train_;
	class Worm* Worm_;
	bool IsCameraMove_;

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

	WaterLevel* WaterLevel_; // 수면 조절용 - 이현

public:
	void MakeWaterLevel();

private:
	void AJYLoading();
	void AJYLevelUpdate();
};

