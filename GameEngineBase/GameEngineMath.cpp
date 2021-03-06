#include "GameEngineMath.h"


const float GameEngineMath::PI = 3.14159265359f;
const float GameEngineMath::PI2 = 3.14159265359f * 2;
const float GameEngineMath::DegreeToRadian = GameEngineMath::PI / 180.0f;
const float GameEngineMath::RadianToDegree = 180.0f / GameEngineMath::PI;

// Static Var
// Static Func

const float4 float4::ZERO = { 0.0f, 0.0f };

const float4 float4::LEFT = {-1.0f, 0.0f};
const float4 float4::RIGHT = { 1.0f, 0.0f };
const float4 float4::UP = { 0.0f, -1.0f };
const float4 float4::DOWN = { 0.0f, 1.0f };