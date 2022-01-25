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
	None,
	BackGround,
	MapBack,
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
	Mouse = 999,
	Max
};
