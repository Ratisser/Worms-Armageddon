#pragma once
#include <GameEngineActor.h>
// �з� : 
// �뵵 : 
// ���� : 
class MapTrain : public GameEngineActor
{
private:
	bool firstupdate_;

private:	// member Var
	GameEngineRenderer* gradationSpriteRender_;
	GameEngineRenderer* mainSpriteRender_;
	GameEngineRenderer* colSpriteRender_;
	GameEngineRenderer* boomSpriteRender_;
	GameEngineRenderer* boomEdgeSpriteRender_;
	GameEngineCollision* bodyCollision_;

	GameEngineRenderer* boomSpriteRender13_;
	GameEngineRenderer* boomSpriteRender25_;
	GameEngineRenderer* boomSpriteRender50_;
	GameEngineRenderer* boomSpriteRender75_;
	GameEngineRenderer* boomSpriteRender100_;
	GameEngineRenderer* boomEdgeSpriteRender13_;
	GameEngineRenderer* boomEdgeSpriteRender25_;
	GameEngineRenderer* boomEdgeSpriteRender50_;
	GameEngineRenderer* boomEdgeSpriteRender75_;
	GameEngineRenderer* boomEdgeSpriteRender100_;

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
	void GroundUpdate(float4 pos);
	void GroundUpdate13(float4 pos);
	void GroundUpdate25(float4 pos);
	void GroundUpdate50(float4 pos);
	void GroundUpdate75(float4 pos);
	void GroundUpdate100(float4 pos);
	void BuildGirder(float4 pos, GameEngineRenderer* _Image, GameEngineRenderer* _ColImage);
};

