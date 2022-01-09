#pragma once
#include <GameEngineLevel.h>
#include <GameEngineMath.h>

// Is A 해결
//class MyEffectSoundPlayer : public GameEngineSoundPlayer
//{
//
//};

// Has A 해결
//class MyEffectSoundPlayer 
//{
//	GameEngineSoundPlayer* SoundPlayer;
//};


// 분류 :
// 용도 :
// 설명 :
class FadeObject;
class GameEngineSoundPlayer;
class PlayLevel : public GameEngineLevel
{
private:	// member Var
	static FadeObject* FadeActor;

	GameEngineSoundPlayer* BgmPlayer;

	GameEngineMath::Random RandomGen;


public:		
	PlayLevel(); // default constructer 디폴트 생성자
	~PlayLevel(); // default destructer 디폴트 소멸자

public:		// delete constructer
	PlayLevel(const PlayLevel& _other) = delete; // default Copy constructer 디폴트 복사생성자
	PlayLevel(PlayLevel&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

public:		//delete operator
	PlayLevel& operator=(const PlayLevel& _other) = delete; // default Copy operator 디폴트 대입 연산자
	PlayLevel& operator=(const PlayLevel&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:		//member Func
	void Loading() override;
	void LevelUpdate() override;
	void LevelUpdateAfter() override;
};

