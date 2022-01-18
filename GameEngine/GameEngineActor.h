#pragma once
#include <list>
#include <GameEngineMath.h>
#include <GameEngineNameBase.h>
#include <GameEngineDebug.h>
#include "EngineEnum.h"

// �з� : ��� ȭ��ȿ��� �����̴� ��ҵ��� �⺻ ����
// �뵵 : �÷��̾� ���� ����... ȭ�鿡 �����ϴ� 
//        ��� ��ҵ鿡 �⺻ ����� �����մϴ�.
// ���� :
class GameEngineLevel;
class GameEngineRenderer;
class GameEngineCollision;
class GameEngineActor : public GameEngineNameBase
{
	// ��Ʈ��Ʈ�����Ϳ����� ����ϴ�
	// �Ҵп����� ����ϴ�
	// �����ۿ����� ����ϴ� ���𰡰� ���� ���� �ǳ��� �ȵǳ���?

private:
	friend GameEngineLevel;

private:
	GameEngineLevel* parentLevel_;
	int UpdateOrder;
	int RenderOrder;

	float cameraEffectScale_;

	// private�� �ƴϸ� �ƹ��� �� �Ҽ� �ְ�
	// ���õ� ������ nullptr�� ������� �ٲܼ��� �ִٴ� �̾߱Ⱑ �˴ϴ�.
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
	GameEngineActor(); // default constructer ����Ʈ ������
	~GameEngineActor() override; // default destructer ����Ʈ �Ҹ���

public:		// delete constructer
	GameEngineActor(const GameEngineActor& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineActor(GameEngineActor&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

public:		//delete operator
	GameEngineActor& operator=(const GameEngineActor& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineActor& operator=(const GameEngineActor&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����


private:		//member Func
	// ����������� �ѹ� ����Ǵ� �Լ�
	virtual void Start() = 0;

	// ������Ʈ �Լ�.
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

