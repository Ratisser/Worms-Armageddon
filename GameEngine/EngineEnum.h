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
