
#pragma once

#include <GameEngineActor.h>
#include <GameEngineFSM.h>

class GameEngineRenderer;
class GameEngineCollision;
class MapGround : public GameEngineActor
{
public:
	MapGround();
	~MapGround();

	MapGround(const MapGround& _other) = delete;
	MapGround(MapGround&& _other) = delete;

	MapGround& operator=(const MapGround& _other) = delete;
	MapGround& operator=(const MapGround&& _other) = delete;

	// GameEngineActor을(를) 통해 상속됨
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

private:
	GameEngineRenderer* mainRenderer_;
	GameEngineCollision* bodyCollision_;
	GameEngineRenderer* boomSpriteRender_;

public:
	void GroundUpdate(float4 pos);
};

