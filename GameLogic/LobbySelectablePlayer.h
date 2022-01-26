#pragma once
#include <GameEngineActor.h>

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineRenderer;
class GameEngineCollision;
class LobbySelectablePlayer : public GameEngineActor
{
private:	// member Var
	bool ShowPlayer_;
	int Index_;
	std::string Name_;
	float4 NamePos_;

private:
	GameEngineRenderer* mainrenderer_;
	GameEngineCollision* maincollision_;

public:
	LobbySelectablePlayer(); // default constructer ����Ʈ ������
	~LobbySelectablePlayer(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	LobbySelectablePlayer(const LobbySelectablePlayer& _other) = delete; // default Copy constructer ����Ʈ ���������
	LobbySelectablePlayer(LobbySelectablePlayer&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	LobbySelectablePlayer& operator=(const LobbySelectablePlayer& _other) = delete; // default Copy operator ����Ʈ ���� ������
	LobbySelectablePlayer& operator=(const LobbySelectablePlayer&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

public:
	std::string GetPlayerName() const;
	int GetIndex() const;

public:
	void SetPlayerInfo(const float4& _NamePos, const float4& _RenderPos, const float4& _RenderSize = float4::ZERO);
	void SetPlayerOn();
	void SetPlayerOff();

public:
	void CreatePlayer(const std::string& _PlayerName, int _Index, int _CPUIndex, bool _PlayerAndCPU = true);
};

