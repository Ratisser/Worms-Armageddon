#pragma once

#include <vector>
#include <GameEngineActor.h>

class GameEngineMath;
class Worm;
class GameController : public GameEngineActor
{
private:	// member Var
	float randomFloatContainer_;

public:
	GameController(); // default constructer ����Ʈ ������
	~GameController(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameController(const GameController& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameController(GameController&& _other) = delete; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameController& operator=(const GameController& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameController& operator=(const GameController&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

	void CreateWorm(const float _minX, const float _maxX);

	std::vector<Worm*> GetWormList() const
	{
		return wormList_;
	}

private:
	const int MAX_WORM_COUNT = 8;

private:
	std::vector<Worm*> wormList_;
	std::vector<float> xPosList_;
	size_t currentIndex_;
	Worm* currentWorm_;
	float cameraMoveSpeed_;
	int wormIndex_;
	bool IsCameraMove_;
};

