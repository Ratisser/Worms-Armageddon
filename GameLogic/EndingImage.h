#pragma once
#include <GameEngineActor.h>
#include <GameEngineTimeEventer.h>

// �з� : 
// �뵵 : 
// ���� : 
class EndingImage : public GameEngineActor
{
private:	// member Var
	float alpha_;
	unsigned char castalpha_;
	bool fadestop_;

private:
	GameEngineRenderer* fadeBlackSpriteRender_;
	GameEngineRenderer* EndingImageRender_;

private:
	GameEngineTimeEventer<EndingImage> EndingTimer_;

public:
	EndingImage(); // default constructer ����Ʈ ������
	~EndingImage(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	EndingImage(const EndingImage& _other) = delete; // default Copy constructer ����Ʈ ���������
	EndingImage(EndingImage&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	EndingImage& operator=(const EndingImage& _other) = delete; // default Copy operator ����Ʈ ���� ������
	EndingImage& operator=(const EndingImage&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

public:
	void EndingFadeStart();
	void EndingFadeStay();
	bool EndingFadeEnd();
};

