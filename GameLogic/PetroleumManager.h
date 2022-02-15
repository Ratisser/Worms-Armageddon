#pragma once
#include <map>
// 분류 : 
// 용도 : 
// 설명 : 
class Petroleum;
class PetroleumManager
{
private:	// member Var

public:
	PetroleumManager(); // default constructer 디폴트 생성자
	~PetroleumManager(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	PetroleumManager(const PetroleumManager& _other) = delete; // default Copy constructer 디폴트 복사생성자
	PetroleumManager(PetroleumManager&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	PetroleumManager& operator=(const PetroleumManager& _other) = delete; // default Copy operator 디폴트 대입 연산자
	PetroleumManager& operator=(const PetroleumManager&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

private:


public:


};

