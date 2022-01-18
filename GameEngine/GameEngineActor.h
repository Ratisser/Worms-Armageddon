#pragma once
#include <list>
#include <GameEngineMath.h>
#include <GameEngineNameBase.h>
#include <GameEngineDebug.h>
#include "EngineEnum.h"

// 분류 : 모든 화면안에서 움직이는 요소들의 기본 개념
// 용도 : 플레이어 몬스터 등등등... 화면에 등장하는 
//        모든 요소들에 기본 기능을 제공합니다.
// 설명 :
class GameEngineLevel;
class GameEngineRenderer;
class GameEngineCollision;
class GameEngineActor : public GameEngineNameBase
{
	// 스트리트파이터에서만 사용하는
	// 소닉에서만 사용하는
	// 아이작에서만 사용하는 무언가가 여기 들어가면 되나요 안되나요?

private:
	friend GameEngineLevel;

private:
	GameEngineLevel* parentLevel_;
	int UpdateOrder;
	int RenderOrder;

	float cameraEffectScale_;

	// private이 아니면 아무나 막 할수 있고
	// 세팅된 레벨을 nullptr로 마음대로 바꿀수도 있다는 이야기가 됩니다.
private:
	void SetLevel(GameEngineLevel* _parentLevel)
	{
		parentLevel_ = _parentLevel;
	}


public:
	GameEngineLevel* GetLevel()
	{
		if (nullptr == parentLevel_)
		{
			GameEngineDebug::AssertFalse();
			return nullptr;
		}

		return parentLevel_;
	}

	void SetUpdateOrder(int _UpdateOrder)
	{
		UpdateOrder = _UpdateOrder;
	}

	void SetRenderOrder(int _RenderOrder)
	{
		RenderOrder = _RenderOrder;
	}

	int GetRenderOrder()
	{
		return RenderOrder;
	}

protected:	// member Var
	int ActorType;
	float4 pos_;

public:
	float4 GetPos()
	{
		return pos_;
	}

	float4 GetCamEffectPos();

public:
	void SetPos(float4 _pos)
	{
		pos_ = _pos;
	}

	void SetMove(float4 _pos)
	{
		pos_ += _pos;
	}

	void SetMove(float _posx, float _posy, float _Posz = 0.f)
	{
		pos_.x += _posx;
		pos_.y += _posy;
		pos_.z += _Posz;
	}

protected:
	GameEngineActor(); // default constructer 디폴트 생성자
	~GameEngineActor() override; // default destructer 디폴트 소멸자

public:		// delete constructer
	GameEngineActor(const GameEngineActor& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineActor(GameEngineActor&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

public:		//delete operator
	GameEngineActor& operator=(const GameEngineActor& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineActor& operator=(const GameEngineActor&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자


private:		//member Func
	// 만들어진순간 한번 실행되는 함수
	virtual void Start() = 0;

	// 업데이트 함수.
	virtual void UpdateBefore() = 0;;
	virtual void Update() = 0;
	virtual void UpdateAfter() = 0;
	virtual void Render() = 0;
	virtual void Collision();

private:
	std::list<GameEngineRenderer*> rendererList_;

public:
	///////////////////////////////// Rendering
	GameEngineRenderer* CreateRenderer(std::string _ImageName);

private:
	std::list<GameEngineCollision*> collisionList_;

public:
	template<typename T>
	GameEngineCollision* CreateCollision(T _Group, CollisionCheckType _type)
	{
		return CreateCollision(static_cast<int>(_Group), _type);
	}

	GameEngineCollision* CreateCollision(int _Group, CollisionCheckType _type);
};

