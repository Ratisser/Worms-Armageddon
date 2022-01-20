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
