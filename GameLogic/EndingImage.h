#pragma once
#include <GameEngineActor.h>
#include <GameEngineTimeEventer.h>

// 분류 : 
// 용도 : 
// 설명 : 
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
	EndingImage(); // default constructer 디폴트 생성자
	~EndingImage(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	EndingImage(const EndingImage& _other) = delete; // default Copy constructer 디폴트 복사생성자
	EndingImage(EndingImage&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	EndingImage& operator=(const EndingImage& _other) = delete; // default Copy operator 디폴트 대입 연산자
	EndingImage& operator=(const EndingImage&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

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

