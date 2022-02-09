#include "GameOptionInfo.h"

//======================= Game Basic Option =======================//

// 턴타임
// TernTime = 무한대이면 랜덤타임적용
float GameOptionInfo::TernTime = 45.f;

// 라운드타임
int GameOptionInfo::RoundTime = 15;

// 승리조건
int GameOptionInfo::WinSreuired = 2;

// Worm 선택조건
// WormSelect = 0 Off
// WormSelect = 1 On
// WormSelect = 2 Random
int GameOptionInfo::WormSelect = 0;

// Worm 기본체력
// WormEnergy = 50 무한대(체력없음)
int GameOptionInfo::WormEnergy = 50;

// 텔레포트 On/Off
bool GameOptionInfo::Teleportin = false;

//======================= Game Basic Option =======================//


