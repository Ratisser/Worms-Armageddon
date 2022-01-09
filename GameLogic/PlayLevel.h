#pragma once
#include <GameEngineLevel.h>
#include <GameEngineMath.h>

// Is A �ذ�
//class MyEffectSoundPlayer : public GameEngineSoundPlayer
//{
//
//};

// Has A �ذ�
//class MyEffectSoundPlayer 
//{
//	GameEngineSoundPlayer* SoundPlayer;
//};


// �з� :
// �뵵 :
// ���� :
class FadeObject;
class GameEngineSoundPlayer;
class PlayLevel : public GameEngineLevel
{
private:	// member Var
	static FadeObject* FadeActor;

	GameEngineSoundPlayer* BgmPlayer;

	GameEngineMath::Random RandomGen;


public:		
	PlayLevel(); // default constructer ����Ʈ ������
	~PlayLevel(); // default destructer ����Ʈ �Ҹ���

public:		// delete constructer
	PlayLevel(const PlayLevel& _other) = delete; // default Copy constructer ����Ʈ ���������
	PlayLevel(PlayLevel&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

public:		//delete operator
	PlayLevel& operator=(const PlayLevel& _other) = delete; // default Copy operator ����Ʈ ���� ������
	PlayLevel& operator=(const PlayLevel&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:		//member Func
	void Loading() override;
	void LevelUpdate() override;
	void LevelUpdateAfter() override;
};

