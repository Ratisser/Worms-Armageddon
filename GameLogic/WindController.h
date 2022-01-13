#pragma once

// 분류 : 
// 용도 : 
// 설명 : 
class WindController
{
private:	// member Var

public:
	WindController(); // default constructer 디폴트 생성자
	~WindController(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	WindController(const WindController& _other) = delete; // default Copy constructer 디폴트 복사생성자
	WindController(WindController&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	WindController& operator=(const WindController& _other) = delete; // default Copy operator 디폴트 대입 연산자
	WindController& operator=(const WindController&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
};

