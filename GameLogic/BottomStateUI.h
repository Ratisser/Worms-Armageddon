#pragma once
#include <GameEngineActor.h>

// 분류 : 
// 용도 : 
// 설명 : 
class Worm;
class UIController;
class GameEngineRenderer;
class BottomStateUI : public GameEngineActor
{
private:	// member Var
	Worm* ParentWorm_;
	UIController* ParentUI_;

private:
	int WormIndex_;
	int PlayerColorIndex_;
	int PrevHP_;
	int CurHP_;

private:
	GameEngineRenderer* FlagRenderer_;
	GameEngineRenderer* NameRenderer_;
	GameEngineRenderer* HPBarRenderer_;

public:
	BottomStateUI(); // default constructer 디폴트 생성자
	~BottomStateUI(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	BottomStateUI(const BottomStateUI& _other) = delete; // default Copy constructer 디폴트 복사생성자
	BottomStateUI(BottomStateUI&& _other) noexcept = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	BottomStateUI& operator=(const BottomStateUI& _other) = delete; // default Copy operator 디폴트 대입 연산자
	BottomStateUI& operator=(const BottomStateUI&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	virtual void Start() override;
	virtual void UpdateBefore() override;
	virtual void Update() override;
	virtual void UpdateAfter() override;
	virtual void Render() override;

public:
	int GetWormIndex();

public:
	void SetParentWorm(Worm* _Parent);
	void SetParentUIController(UIController* _ParentUI);

public:
	void GameStartInit(int _WormIndex);

public:
	void SettingRenderer();
	void SetFlag();
	void SetPlayerName();
	void SetPlayerHPBar();

public:
	void SettingRendererPos();
	void SetFlagPos();
	void SetNamePos();
	void SetHPBarPos();
};

