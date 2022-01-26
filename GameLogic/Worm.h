#pragma once

#include <GameEngineActor.h>
#include <GameEngineFSM.h>

#include "eItemList.h"

class GameEngineRenderer;
class UIController;
class Worm : public GameEngineActor
{
public:
	Worm();
	~Worm();

	Worm(const Worm& _other) = delete; // default Copy constructer 디폴트 복사생성자
	Worm(Worm&& _other) = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자

	Worm& operator=(const Worm& _other) = delete; // default Copy operator 디폴트 대입 연산자
	Worm& operator=(const Worm&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

public:
	void ChangeState(std::string _stateName);
	void SetFocus(bool _bFocus);
	bool isFocused();
	void SetCurWeapon(eItemList _WeaponType);
	void SetUIController(UIController* _uicontroller);
	UIController* GetCurUIController() const;

	void Damage(int _numDamage);
	bool IsDie() const;

	void AddActionToken(int _numToken);
	void SubtractActionToken(int _numToken);
	void ClearActionToken();
	int GetActionTokenCount() const;

	float4 GetForward() const;

	void BulletFocusOn(GameEngineActor* _actor);
	void BulletFocusOff();

private:
	void initRenderer();
	void initInput();
	void initCollision();
	void initState();

	void addGravity();

	void normalMove();

	int getAimingFrame();

	std::string getWeaponAimState();
	void setAnimationWeaponOn();
	void setAnimationWeaponOff();

	void setAimingForward();

private:
	StateInfo startIdle(StateInfo _state);
	StateInfo updateIdle(StateInfo _state);

	StateInfo startWalk(StateInfo _state);
	StateInfo updateWalk(StateInfo _state);

	StateInfo startJumpReady(StateInfo _state);
	StateInfo updateJumpReady(StateInfo _state);

	StateInfo startJump(StateInfo _state);
	StateInfo updateJump(StateInfo _state);

	StateInfo startWeaponOn(StateInfo _state);
	StateInfo updateWeaponOn(StateInfo _state);

	StateInfo startWeaponOff(StateInfo _state);
	StateInfo updateWeaponOff(StateInfo _state);

	StateInfo startBazookaAim(StateInfo _state);
	StateInfo updateBazookaAim(StateInfo _state);
	StateInfo startBazookaFire(StateInfo _state);
	StateInfo updateBazookaFire(StateInfo _state);
	StateInfo startBazookaWait(StateInfo _state);
	StateInfo updateBazookaWait(StateInfo _state);

	StateInfo startHomingStart(StateInfo _state);
	StateInfo updateHomingStart(StateInfo _state);
	StateInfo startHomingAim(StateInfo _state);
	StateInfo updateHomingAim(StateInfo _state);
	StateInfo startHomingFire(StateInfo _state);
	StateInfo updateHomingFire(StateInfo _state);
	StateInfo startHomingWait(StateInfo _state);
	StateInfo updateHomingWait(StateInfo _state);

	StateInfo startFirepunchReady(StateInfo _state);
	StateInfo updateFirepunchReady(StateInfo _state);
	StateInfo startFirepunchStart(StateInfo _state);
	StateInfo updateFirepunchStart(StateInfo _state);
	StateInfo startFirepunchFly(StateInfo _state);
	StateInfo updateFirepunchFly(StateInfo _state);
	StateInfo startFirepunchEnd(StateInfo _state);
	StateInfo updateFirepunchEnd(StateInfo _state);
	StateInfo startFirepunchLand(StateInfo _state);
	StateInfo updateFirepunchLand(StateInfo _state);
	StateInfo startFirepunchOff(StateInfo _state);
	StateInfo updateFirepunchOff(StateInfo _state);

	StateInfo startUziAim(StateInfo _state);
	StateInfo updateUziAim(StateInfo _state);
	StateInfo startUziFire(StateInfo _state);
	StateInfo updateUziFire(StateInfo _state);
	StateInfo startUziWait(StateInfo _state);
	StateInfo updateUziWait(StateInfo _state);

	StateInfo startSheepAim(StateInfo _state);
	StateInfo updateSheepAim(StateInfo _state);
	StateInfo startSheepFire(StateInfo _state);
	StateInfo updateSheepFire(StateInfo _state);
	StateInfo startSheepWait(StateInfo _state);
	StateInfo updateSheepWait(StateInfo _state);

	StateInfo startSuperSheepAim(StateInfo _state);
	StateInfo updateSuperSheepAim(StateInfo _state);
	StateInfo startSuperSheepFire(StateInfo _state);
	StateInfo updateSuperSheepFire(StateInfo _state);
	StateInfo startSuperSheepWait(StateInfo _state);
	StateInfo updateSuperSheepWait(StateInfo _state);


	StateInfo startBattleAxeOn(StateInfo _state);
	StateInfo updateBattleAxeOn(StateInfo _state);
	StateInfo startBattleAxeFire1(StateInfo _state);
	StateInfo updateBattleAxeFire1(StateInfo _state);
	StateInfo startBattleAxeFire2(StateInfo _state);
	StateInfo updateBattleAxeFire2(StateInfo _state);
	StateInfo startBattleAxeFire3(StateInfo _state);
	StateInfo updateBattleAxeFire3(StateInfo _state);
	StateInfo startBattleAxeOff(StateInfo _state);
	StateInfo updateBattleAxeOff(StateInfo _state);
	StateInfo startBattleAxeWait(StateInfo _state);
	StateInfo updateBattleAxeWait(StateInfo _state);

	StateInfo startGirderOn(StateInfo _state);
	StateInfo updateGirderOn(StateInfo _state);

private:
	const float MOVE_SPEED = 100.f;
	const float GRAVITY_POWER = 600.f;
	const float PLAYER_BOTTOM_PIVOT = 14.f;
	const float JUMP_POWER = 150.f;
	const float WEAPON_EQUIP_DELAY = 0.5f;
	const float AIM_STEP_RADIAN = 0.0986111f; // 180 / 32 * RADIAN -> 조준 스프라이트가 32단계일 때

private:
	GameEngineRenderer* mainRender_;
	GameEngineRenderer* crosshairRender_;
	GameEngineCollision* bottomCenterCollision_;
	GameEngineCollision* groundCheckCollision_;
	GameEngineCollision* leftSideCollision_;
	GameEngineCollision* rightSideCollision_;
	GameEngineCollision* headCollision_;

	GameEngineFSM<Worm> state_;

	float4 accelation_;
	float4 speed_;
	float4 direction_;
	float4 forward_;
	float4 mouseTargetPos_; // 마우스로 위치 클릭해서 발사하는 무기들 마우스 위치 저장용

	bool bLeft_;
	bool bGround_;
	bool bBackJump_;
	bool bFocus_;

	float deltaTime_;
	float weaponEquipDelay_;
	float aimRotation_;
	float currentRotation_;
	float firePower_;


	int hp_;
	int actionToken_;

	eItemList currentWeapon_;

	std::string nextState_;

	UIController* uicontroller_;

	GameEngineActor* bulletFocusActor_;

public:
	eItemList GetCurrentWeapon() const
	{
		return currentWeapon_;
	}
};

