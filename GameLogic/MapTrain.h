#pragma once
#include <GameEngineActor.h>
// 분류 : 
// 용도 : 
// 설명 : 
class MapTrain : public GameEngineActor
{
private:	// member Var
	GameEngineRenderer* backGroundSpriteRender_;
	GameEngineRenderer* mainSpriteRender_;
	GameEngineRenderer* boomSpriteRender_;

public:
	MapTrain(); // default constructer 디폴트 생성자
	~MapTrain(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	MapTrain(const MapTrain& _other) = delete; // default Copy constructer 디폴트 복사생성자
	MapTrain(MapTrain&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	MapTrain& operator=(const MapTrain& _other) = delete; // default Copy operator 디폴트 대입 연산자
	MapTrain& operator=(const MapTrain&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

public:
	void GroundUpdate();
};

