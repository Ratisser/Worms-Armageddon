#pragma once
#include <GameEngineActor.h>
	// 분류 : 
	// 용도 : 
	// 설명 : 
class WaterLevel : public GameEngineActor
{
private:	// member Var
	GameEngineRenderer* mainSpriteRender_;
	float waterLevel_;

public:
	WaterLevel(); // default constructer 디폴트 생성자
	~WaterLevel(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	WaterLevel(const WaterLevel& _other) = delete; // default Copy constructer 디폴트 복사생성자
	WaterLevel(WaterLevel&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	WaterLevel& operator=(const WaterLevel& _other) = delete; // default Copy operator 디폴트 대입 연산자
	WaterLevel& operator=(const WaterLevel&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	std::list<GameEngineActor*> Waterlist;

public:
	void WaterLevelUp(float deltaTime); // 수면 상승
	void WaterLevelDown(float deltaTime); // 수면 하강

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

public:
	const float GetWaterLevel()
	{
		return waterLevel_;
	}

	void SetwaterLevel(float _waterLevel)
	{
		waterLevel_ = _waterLevel;
	}
};