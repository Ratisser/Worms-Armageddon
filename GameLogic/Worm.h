#pragma once

#include <GameEngineActor.h>
class GameEngineRenderer;
class Worm : public GameEngineActor
{
public:
	Worm();
	~Worm();

	Worm(const Worm& _other) = delete; // default Copy constructer 디폴트 복사생성자
	Worm(Worm&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

	Worm& operator=(const Worm& _other) = delete; // default Copy operator 디폴트 대입 연산자
	Worm& operator=(const Worm&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

private:
	GameEngineRenderer* mainRender_;

};

