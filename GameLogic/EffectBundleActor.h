#pragma once
#include <GameEngineActor.h>

// 분류 : GameEngineActor
// 용도 : 이펙트 묶음(번들) 부모 클레스
// 설명 : 이펙트 클레스의 묶음 클레스로 여러 이펙트 클레스를 하나로 묶어서 하나의 이펙트 묶음(번들)로 사용함

class EffectBundleActor : public GameEngineActor
{

protected:	// member Var
	std::list<GameEngineActor*> EffectActorList;
	class GameEngineLevel* GameLevel_;

public:
	EffectBundleActor(); // default constructer 디폴트 생성자
	~EffectBundleActor(); // default destructer 디폴트 소멸자
protected:		// delete constructer
	EffectBundleActor(const EffectBundleActor& _other) = delete; // default Copy constructer 디폴트 복사생성자
	EffectBundleActor(EffectBundleActor&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자
private:		//delete operator
	EffectBundleActor& operator=(const EffectBundleActor& _other) = delete; // default Copy operator 디폴트 대입 연산자
	EffectBundleActor& operator=(const EffectBundleActor&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자
public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

protected:
	void SetGameLevel(GameEngineLevel* GameLevel);
};

