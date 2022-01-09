#pragma once
#include <GameEngineActor.h>

// �з� :
// �뵵 :
// ���� :
class TitleLogo : public GameEngineActor
{
public:
	TitleLogo(); // default constructer ����Ʈ ������
	~TitleLogo(); // default destructer ����Ʈ �Ҹ���

public:		// delete constructer
	TitleLogo(const TitleLogo& _other) = delete; // default Copy constructer ����Ʈ ���������
	TitleLogo(TitleLogo&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

public:		//delete operator
	TitleLogo& operator=(const TitleLogo& _other) = delete; // default Copy operator ����Ʈ ���� ������
	TitleLogo& operator=(const TitleLogo&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:		//member Func
	void Start() override;
	void Update() override;
	void Render() override;
};

