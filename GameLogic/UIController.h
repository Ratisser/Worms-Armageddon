#pragma once
#include <map>
#include <GameEngineActor.h>

// 기본구조 : 플레이어가 UIController를 객체로 가지며 해당 객체에 아이템목록을 넘겨주면
//                   해당 UIController가 해당 목록을 WeaponSheet에 넘기며
//                   수신한 WeaponSheet가 WeaponIcon 목록을 만들어서 관리한다.
//                   
class Worm;
class WeaponSheet;
class Weapon;
class UIController : public GameEngineActor
{
private:	// member Var
	Worm* curplayer_;	// 현재 해당 제어관리자를 사용하는 객체

private:	// 관리하는 모든 UI

	// Weapon Sheet 관련
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
	void SetCurItemList(const std::map<std::string, Weapon*>& _WeaponList);

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

};

