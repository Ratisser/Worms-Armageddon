#pragma once

// �з� : UI ���� ������
class GameEngineActor;
class UIController
{
private:	// member Var
	GameEngineActor* curactor_;	// ���� �ش� ��������ڸ� ����ϴ� ��ü

private:	// �����ϴ� ��� UI


public:
	UIController(); // default constructer ����Ʈ ������
	~UIController(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	UIController(const UIController& _other) = delete; // default Copy constructer ����Ʈ ���������
	UIController(UIController&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	UIController& operator=(const UIController& _other) = delete; // default Copy operator ����Ʈ ���� ������
	UIController& operator=(const UIController&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:

};

