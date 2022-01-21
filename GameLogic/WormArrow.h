#pragma once
#include <GameEngineActor.h>
// 분류 : 
// 용도 : 
// 설명 : 
class Worm;
class GameController;
class WormArrow : public GameEngineActor
{
private:	// member Var
	GameEngineRenderer* mainRender_;
	Worm* parent_;
	GameController* controller_;

	bool isGoingUp_;

public:
	WormArrow(); // default constructer 디폴트 생성자
	~WormArrow(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	WormArrow(const WormArrow& _other) = delete; // default Copy constructer 디폴트 복사생성자
	WormArrow(WormArrow&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	WormArrow& operator=(const WormArrow& _other) = delete; // default Copy operator 디폴트 대입 연산자
	WormArrow& operator=(const WormArrow&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	void SetParent(Worm* _parent)
	{
		parent_ = _parent;
	}

public:
	void SetGoingUp()
	{
		isGoingUp_ = true;
	}

	void SetArrow();

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;
};

