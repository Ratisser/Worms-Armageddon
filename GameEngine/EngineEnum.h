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
	MIN,
	BackGround,
	BackGround1,
	BackGround2,
	MapBack,
	MapBack1,
	MapBack2,
	WaterLevel_Back,
	Map,
	Worm,
	WaterLevel_Front,
	Weapon,
	Effect,
	UI,
	UI1,
	UI2,
	Mouse = 999,
	MAX
};
