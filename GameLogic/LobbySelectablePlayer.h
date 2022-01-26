#pragma once
#include <GameEngineActor.h>

// 분류 : 
// 용도 : 
// 설명 : 
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
	LobbySelectablePlayer(); // default constructer 디폴트 생성자
	~LobbySelectablePlayer(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	LobbySelectablePlayer(const LobbySelectablePlayer& _other) = delete; // default Copy constructer 디폴트 복사생성자
	LobbySelectablePlayer(LobbySelectablePlayer&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	LobbySelectablePlayer& operator=(const LobbySelectablePlayer& _other) = delete; // default Copy operator 디폴트 대입 연산자
	LobbySelectablePlayer& operator=(const LobbySelectablePlayer&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

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

