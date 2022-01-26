#pragma once
#include <GameEngineActor.h>

class GameEngineRenderer;
class LobbySelectablePlayer;
class LobbyCreateTeam : public GameEngineActor
{
public:
	static void SelectPlayer(const std::string& _PlayerName, int _CurSelPlayerIndex);

private:	// member Var
	GameEngineRenderer* playerselInputSpriteRender_;
	GameEngineRenderer* playerselboxSpriteRender_;
	GameEngineRenderer* playerboxSpriteRender_;

private: // ���� ���ð����� �÷��̾� ���
	std::vector<LobbySelectablePlayer*> SelectablePlayerList;

private: // ���� ���õ� �÷��̾� ���
	

public:
	LobbyCreateTeam(); // default constructer ����Ʈ ������
	~LobbyCreateTeam(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	LobbyCreateTeam(const LobbyCreateTeam& _other) = delete; // default Copy constructer ����Ʈ ���������
	LobbyCreateTeam(LobbyCreateTeam&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	LobbyCreateTeam& operator=(const LobbyCreateTeam& _other) = delete; // default Copy operator ����Ʈ ���� ������
	LobbyCreateTeam& operator=(const LobbyCreateTeam&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;
};

