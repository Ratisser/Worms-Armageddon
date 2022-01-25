#pragma once

#include <GameEngineActor.h>
#include <GameEngineFSM.h>

class GameEngineCollision;
class SuperSheep : public GameEngineActor
{
public:
	SuperSheep();
	~SuperSheep();

	SuperSheep(const SuperSheep& _other) = delete;
	SuperSheep(SuperSheep&& _other) = delete;

	SuperSheep& operator=(const SuperSheep& _other) = delete;
	SuperSheep& operator=(const SuperSheep&& _other) = delete;

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

private:
	GameEngineFSM<SuperSheep> state_;

	float4 forward_;

	GameEngineCollision* headCollision_;
};

