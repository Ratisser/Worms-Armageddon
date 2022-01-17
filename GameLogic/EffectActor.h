#pragma once
#include <GameEngineActor.h>
#include <GameEngineLevel.h>

// 분류 : GameEngineActor
// 용도 : 작은 이펙트 부모 클레스
// 설명 : 이펙트 묶음(번들)에 사용될 작은 이펙트의 부모 클레스

class EffectActor : public GameEngineActor
{	
protected:	// member Var
	GameEngineRenderer* mainSpriteRender_;
	bool	Destroy_;

	float4 Dir_; //크기가 반드시 1이여야 하는 방향 단위 벡터

public:
	EffectActor();
	~EffectActor();
protected:		// delete constructer
	EffectActor(const EffectActor& _other) = delete;
	EffectActor(EffectActor&& _other) noexcept;
private:		//delete operator
	EffectActor& operator=(const EffectActor& _other) = delete;
	EffectActor& operator=(const EffectActor&& _other) = delete;
public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

protected:
	void SetDir(float4 Dir)
	{
		Dir_ = Dir;
	}

public:
	void EffectDestroy()
	{
		Destroy_ = true;
	}

	bool IsEffectDestroy()
	{
		return Destroy_;
	}

	float4 GetDir()
	{
		return Dir_;
	}
};
