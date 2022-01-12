#pragma once
#include <GameEngineActor.h>

// 분류 : UI 제어 관리자
class Worm;
class WeaponSheet;
class UIController : public GameEngineActor
{
private:	// member Var
	Worm* curplayer_;	// 현재 해당 제어관리자를 사용하는 객체

private:	// 관리하는 모든 UI
	WeaponSheet* weaponsheet_;

public:
	UIController(); // default constructer 디폴트 생성자
	~UIController(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	UIController(const UIController& _other) = delete; // default Copy constructer 디폴트 복사생성자
	UIController(UIController&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	UIController& operator=(const UIController& _other) = delete; // default Copy operator 디폴트 대입 연산자
	UIController& operator=(const UIController&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	void SetCurPlayer(Worm* _curplayer);

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

};

