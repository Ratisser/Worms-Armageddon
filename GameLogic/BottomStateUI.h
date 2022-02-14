#pragma once
#include <GameEngineActor.h>

// �з� : 
// �뵵 : 
// ���� : 
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
	BottomStateUI(); // default constructer ����Ʈ ������
	~BottomStateUI(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	BottomStateUI(const BottomStateUI& _other) = delete; // default Copy constructer ����Ʈ ���������
	BottomStateUI(BottomStateUI&& _other) noexcept = delete; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	BottomStateUI& operator=(const BottomStateUI& _other) = delete; // default Copy operator ����Ʈ ���� ������
	BottomStateUI& operator=(const BottomStateUI&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

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

