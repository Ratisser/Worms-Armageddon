#include "GameEngineCollision.h"
#include <GameEngineDebug.h>
#include "GameEngineImageFile.h"


// Static Var
// Static Func

bool (*GameEngineCollision::arrFunc_[static_cast<int>(CollisionCheckType::MAX)][static_cast<int>(CollisionCheckType::MAX)])(GameEngineCollision* _PointCol, GameEngineCollision* _ImageCol) = { nullptr };

void GameEngineCollision::ColCheckFuncInitialize()
{
	for (size_t y = 0; y < static_cast<int>(CollisionCheckType::MAX); y++)
	{
		for (size_t x = 0; x < static_cast<int>(CollisionCheckType::MAX); x++)
		{
			arrFunc_[y][x] = nullptr;
		}
	}

	arrFunc_[static_cast<int>(CollisionCheckType::IMAGE)][static_cast<int>(CollisionCheckType::POINT)] = &GameEngineCollision::ImageToPoint;

	arrFunc_[static_cast<int>(CollisionCheckType::RECT)][static_cast<int>(CollisionCheckType::RECT)] = &GameEngineCollision::RectToRect;
	arrFunc_[static_cast<int>(CollisionCheckType::RECT)][static_cast<int>(CollisionCheckType::POINT)] = &GameEngineCollision::RectToPoint;

	arrFunc_[static_cast<int>(CollisionCheckType::POINT)][static_cast<int>(CollisionCheckType::IMAGE)] = &GameEngineCollision::PointToImage;
	arrFunc_[static_cast<int>(CollisionCheckType::POINT)][static_cast<int>(CollisionCheckType::RECT)] = &GameEngineCollision::PointToRect;
}

bool GameEngineCollision::PointToImage(GameEngineCollision* _PointCol, GameEngineCollision* _ImageCol)
{
	float4 Pos = _PointCol->GetCollisionPos();

	if (nullptr == _ImageCol->imageptr_)
	{
		GameEngineDebug::AssertFalse();
		return false;
	}

	DWORD Color = _ImageCol->imageptr_->GetColor4Byte(Pos.ix(), Pos.iy());

	return _PointCol->GetColorCheck() == Color;
}

bool GameEngineCollision::ImageToPoint(GameEngineCollision* _ImageCol, GameEngineCollision* _PointCol)
{
	return PointToImage(_PointCol, _ImageCol);
}


bool GameEngineCollision::RectToRect(GameEngineCollision* _left, GameEngineCollision* _right) 
{
	Figure Left = _left->GetFigure();
	Figure Right = _right->GetFigure();

	if (Left.iRight() < Right.iLeft())
	{
		return false;
	}

	if (Left.iLeft() > Right.iRight())
	{
		return false;
	}

	if (Left.iTop() > Right.iBot())
	{
		return false;
	}

	if (Left.iBot() < Right.iTop())
	{
		return false;
	}

	return true;
}

// Point란? size가 zero인 rect라고 볼수가 있다.

bool GameEngineCollision::RectToPoint(GameEngineCollision* _left, GameEngineCollision* _right)
{
	Figure Left = _left->GetFigure();
	float4 Right = _right->GetCollisionPos();

	if (Left.iRight() < Right.ix())
	{
		return false;
	}

	if (Left.iLeft() > Right.ix())
	{
		return false;
	}

	if (Left.iTop() > Right.iy())
	{
		return false;
	}

	if (Left.iBot() < Right.iy())
	{
		return false;
	}

	return true;
}


bool GameEngineCollision::PointToRect(GameEngineCollision* _left, GameEngineCollision* _right)
{
	return RectToPoint(_right, _left);
}