#pragma once

// �з� : 
// �뵵 : 
// ���� : 
class WindController
{
private:	// member Var

public:
	WindController(); // default constructer ����Ʈ ������
	~WindController(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	WindController(const WindController& _other) = delete; // default Copy constructer ����Ʈ ���������
	WindController(WindController&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	WindController& operator=(const WindController& _other) = delete; // default Copy operator ����Ʈ ���� ������
	WindController& operator=(const WindController&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
};

