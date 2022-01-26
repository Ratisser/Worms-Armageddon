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

private: // 현재 선택가능한 플레이어 목록
	std::vector<LobbySelectablePlayer*> SelectablePlayerList;

private: // 현재 선택된 플레이어 목록
	

public:
	LobbyCreateTeam(); // default constructer 디폴트 생성자
	~LobbyCreateTeam(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	LobbyCreateTeam(const LobbyCreateTeam& _other) = delete; // default Copy constructer 디폴트 복사생성자
	LobbyCreateTeam(LobbyCreateTeam&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	LobbyCreateTeam& operator=(const LobbyCreateTeam& _other) = delete; // default Copy operator 디폴트 대입 연산자
	LobbyCreateTeam& operator=(const LobbyCreateTeam&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;
};

