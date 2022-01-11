#pragma once
#include <GameEngineActor.h>
// 분류 : 
// 용도 : 
// 설명 : 
class TitleImage : public GameEngineActor
{
private:	// member Var
	GameEngineRenderer* mainSpriteRender_;

public:
	TitleImage(); // default constructer 디폴트 생성자
	~TitleImage(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	TitleImage(const TitleImage& _other) = delete; // default Copy constructer 디폴트 복사생성자
	TitleImage(TitleImage&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	TitleImage& operator=(const TitleImage& _other) = delete; // default Copy operator 디폴트 대입 연산자
	TitleImage& operator=(const TitleImage&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;
};

