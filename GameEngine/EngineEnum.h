#pragma once

enum class CollisionCheckType
{
	IMAGE,
	POINT,
	RECT,
	LINE,
	CIRCLE,
	POLYGON2D,
	AABBBOX, // ȸ�����ϴ� �ڽ�
	OBBBOX, // ȸ���ϴ� �ڽ�
	SPHERE,
	POLYGON3D,
	MAX,
};

enum class RenderOrder
{
	// ���� �߰�, ��ġ�Ͽ� ����ϱ� �ٶ� - ����
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
	Effect1,
	Effect2,
	Effect3,
	UI,
	UI1,
	UI2,
	UI3,
	Mouse = 999,
	MAX
};
