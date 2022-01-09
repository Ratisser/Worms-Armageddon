#pragma once
#include <GameEngineActor.h>
// 분류 :
// 용도 :
// 설명 :
class TitleBack : public GameEngineActor
{
private:	// member Var

public:		
	TitleBack(); // default constructer 디폴트 생성자
	~TitleBack(); // default destructer 디폴트 소멸자

public:		// delete constructer
	TitleBack(const TitleBack& _other) = delete; // default Copy constructer 디폴트 복사생성자
	TitleBack(TitleBack&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

public:		//delete operator
	TitleBack& operator=(const TitleBack& _other) = delete; // default Copy operator 디폴트 대입 연산자
	TitleBack& operator=(const TitleBack&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:		//member Func
	void Update() override;
	void Render() override;
};

