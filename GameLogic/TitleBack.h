#pragma once
#include <GameEngineActor.h>
// �з� :
// �뵵 :
// ���� :
class TitleBack : public GameEngineActor
{
private:	// member Var

public:		
	TitleBack(); // default constructer ����Ʈ ������
	~TitleBack(); // default destructer ����Ʈ �Ҹ���

public:		// delete constructer
	TitleBack(const TitleBack& _other) = delete; // default Copy constructer ����Ʈ ���������
	TitleBack(TitleBack&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

public:		//delete operator
	TitleBack& operator=(const TitleBack& _other) = delete; // default Copy operator ����Ʈ ���� ������
	TitleBack& operator=(const TitleBack&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:		//member Func
	void Update() override;
	void Render() override;
};

