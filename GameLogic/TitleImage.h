#pragma once
#include <GameEngineActor.h>
// �з� : 
// �뵵 : 
// ���� : 
class TitleImage : public GameEngineActor
{
private:	// member Var
	GameEngineRenderer* mainSpriteRender_;

public:
	TitleImage(); // default constructer ����Ʈ ������
	~TitleImage(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	TitleImage(const TitleImage& _other) = delete; // default Copy constructer ����Ʈ ���������
	TitleImage(TitleImage&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	TitleImage& operator=(const TitleImage& _other) = delete; // default Copy operator ����Ʈ ���� ������
	TitleImage& operator=(const TitleImage&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;
};

