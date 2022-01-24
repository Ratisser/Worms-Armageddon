#pragma once

#include <vector>
#include <GameEngineActor.h>
#include <GameEngineFSM.h>

class GameEngineMath;
class Worm;
class GameController : public GameEngineActor
{
public:
	GameController(); // default constructer ����Ʈ ������
	~GameController(); // default destructer ����Ʈ �Ҹ���
	GameController(const GameController& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameController(GameController&& _other) = delete; // default RValue Copy constructer ����Ʈ RValue ���������
	GameController& operator=(const GameController& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameController& operator=(const GameController&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

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

	StateInfo startDeath(StateInfo _state);
	StateInfo updateDeath(StateInfo _state);

	StateInfo startVictory(StateInfo _state);
	StateInfo updateVictory(StateInfo _state);

	StateInfo startItemDrop(StateInfo _state);
	StateInfo updateItemDrop(StateInfo _state);

#pragma endregion


private:
	const int MAX_WORM_COUNT = 8;
	const float DEFAULT_TURN_TIME = 3.f;

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
	float randomFloatContainer_;

	float currentTurnTime_;

};

