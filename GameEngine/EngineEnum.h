#pragma once

enum class CollisionCheckType
{
	IMAGE,
	POINT,
	RECT,
	LINE,
	CIRCLE,
	POLYGON2D,
	AABBBOX, // 회전안하는 박스
	OBBBOX, // 회전하는 박스
	SPHERE,
	POLYGON3D,
	MAX,
};

enum class RenderOrder
{
	// 각자 추가, 배치하여 사용하길 바람 - 이현
	None,
	BackGround,
	WaterLevel_Back,
	MapBack,
	Map,
	Worm,
	WaterLevel_Front,
	Weapon,
	Effect,
	UI,
	Mouse = 999,
	Max
};
