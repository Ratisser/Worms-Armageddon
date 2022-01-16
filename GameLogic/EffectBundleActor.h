#pragma once
#include <GameEngineActor.h>

// �з� : GameEngineActor
// �뵵 : ����Ʈ ����(����) �θ� Ŭ����
// ���� : ����Ʈ Ŭ������ ���� Ŭ������ ���� ����Ʈ Ŭ������ �ϳ��� ��� �ϳ��� ����Ʈ ����(����)�� �����

class EffectBundleActor : public GameEngineActor
{

protected:	// member Var
	std::list<GameEngineActor*> EffectActorList;
	class GameEngineLevel* GameLevel_;

public:
	EffectBundleActor(); // default constructer ����Ʈ ������
	~EffectBundleActor(); // default destructer ����Ʈ �Ҹ���
protected:		// delete constructer
	EffectBundleActor(const EffectBundleActor& _other) = delete; // default Copy constructer ����Ʈ ���������
	EffectBundleActor(EffectBundleActor&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������
private:		//delete operator
	EffectBundleActor& operator=(const EffectBundleActor& _other) = delete; // default Copy operator ����Ʈ ���� ������
	EffectBundleActor& operator=(const EffectBundleActor&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����
public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

protected:
	void SetGameLevel(GameEngineLevel* GameLevel);
};

