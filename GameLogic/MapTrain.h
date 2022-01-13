#pragma once
#include <GameEngineActor.h>
// �з� : 
// �뵵 : 
// ���� : 
class MapTrain : public GameEngineActor
{
private:	// member Var
	GameEngineRenderer* backGroundSpriteRender_;
	GameEngineRenderer* mainSpriteRender_;
	GameEngineRenderer* boomSpriteRender_;

public:
	MapTrain(); // default constructer ����Ʈ ������
	~MapTrain(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	MapTrain(const MapTrain& _other) = delete; // default Copy constructer ����Ʈ ���������
	MapTrain(MapTrain&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	MapTrain& operator=(const MapTrain& _other) = delete; // default Copy operator ����Ʈ ���� ������
	MapTrain& operator=(const MapTrain&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

public:
	void GroundUpdate();
};

