#pragma once

#include <vector>
#include <GameEngineActor.h>
#include <GameEngineFSM.h>

class GameEngineMath;
class Worm;
class GameController : public GameEngineActor
{
public:
	GameController(); // default constructer 디폴트 생성자
	~GameController(); // default destructer 디폴트 소멸자
	GameController(const GameController& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameController(GameController&& _other) = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자
	GameController& operator=(const GameController& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameController& operator=(const GameController&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

public:
	void CreateWorm(const float _minX, const float _maxX);
	void CreateWormUI();

	std::vector<Worm*> GetWormList() const;
	Worm* GetCurWorm() const;

private:
	void initState();

private:
#pragma region States

	StateInfo startNextWorm(StateInfo _state);
	StateInfo updateNextWorm(StateInfo _state);

	StateInfo startAction(StateInfo _state);
	StateInfo updateAction(StateInfo _state);

	StateInfo startActionEnd(StateInfo _state);
	StateInfo updateActionEnd(StateInfo _state);

	StateInfo startSettlement(StateInfo _state); // 턴 넘어가기 직전에 일종의 "결산" 단계입니다.
	StateInfo updateSettlement(StateInfo _state); // 대미지 판정 등을 해 주는 단계라고 생각해주시면 됩니다.

	StateInfo startDeath(StateInfo _state);
	StateInfo updateDeath(StateInfo _state);

	StateInfo startVictory(StateInfo _state);
	StateInfo updateVictory(StateInfo _state);

	StateInfo startItemDrop(StateInfo _state);
	StateInfo updateItemDrop(StateInfo _state);

#pragma endregion
public:
	float4 GetCameraPos() const
	{
		return cameraPos_;
	}

private:
	const int MAX_WORM_COUNT = 8;
	const float DEFAULT_TURN_TIME = 46.f;

private:
	GameEngineFSM<GameController> state_;
	std::vector<Worm*> wormList_;
	std::vector<float> xPosList_;
	size_t currentIndex_;
	Worm* currentWorm_;
	float cameraMoveSpeed_;
	int wormIndex_;
	int prevwormIndex_;
	bool IsCameraMove_;
	float4 cameraPos_;
	float wormXPosContainer_;

	float currentTurnTime_;

};

