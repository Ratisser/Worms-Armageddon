#pragma once

// �з� : 
// �뵵 : 
// ���� : 
class PlayLevel
{
private:	// member Var

public:
	PlayLevel(); // default constructer ����Ʈ ������
	~PlayLevel(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	PlayLevel(const PlayLevel& _other) = delete; // default Copy constructer ����Ʈ ���������
	PlayLevel(PlayLevel&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	PlayLevel& operator=(const PlayLevel& _other) = delete; // default Copy operator ����Ʈ ���� ������
	PlayLevel& operator=(const PlayLevel&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:

};

