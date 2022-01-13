#pragma once
#include <GameEngineLevel.h>
#include "WaterLevel.h"
// �з� : 
// �뵵 : 
// ���� : 
class WindController;
class PlayLevel : public GameEngineLevel
{
private:	// member Var
	class MapTrain* Train_;
	class Worm* Worm_;
	bool IsCameraMove_;

public:
	PlayLevel(); // default constructer ����Ʈ ������
	~PlayLevel(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	PlayLevel(const PlayLevel& _other) = delete; // default Copy constructer ����Ʈ ���������
	PlayLevel(PlayLevel&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	PlayLevel& operator=(const PlayLevel& _other) = delete; // default Copy operator ����Ʈ ���� ������
	PlayLevel& operator=(const PlayLevel&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	void Loading() override;
	void LevelUpdate() override;

	WaterLevel* WaterLevel_; // ���� ������ - ����
	
public:
	WindController* windController_;

public:
	void MakeWaterLevel();
	void MakeWind();
	void CreateGimmickObject();

private:
	void AJYLoading();
	void AJYLevelUpdate();
};

