#include "GameEngineCollision.h"
#include <GameEngineDebug.h>
#include "GameEngineImage.h"
#include "GameEngineActor.h"
#include "GameEngineLevel.h"
#include "GameEngineImageFile.h"


// constructer destructer
GameEngineCollision::GameEngineCollision()
	: colType_(CollisionCheckType::MAX)
	, groupIndex_(0)
	, isCamEffect_(true)
	, actor_(nullptr)
	, imageptr_(nullptr)
{
}

GameEngineCollision::~GameEngineCollision()
{
}

float4 GameEngineCollision::GetCollisionPos() 
{
	return actor_->GetPos() + Pivot_;
}

GameEngineCollision::GameEngineCollision(GameEngineCollision&& _other) noexcept
	: colType_(CollisionCheckType::MAX)
	, groupIndex_(0)
	, isCamEffect_(true)
	, actor_(nullptr)
	, imageptr_(nullptr)
{
}

//member Func

bool GameEngineCollision::CollisionCheck(GameEngineCollision* _other) 
{
	if (nullptr == this)
	{
		GameEngineDebug::AssertFalse();
		return false;
	}

	if (nullptr == _other)
	{
		GameEngineDebug::AssertFalse();
		return false;
	}

	if (nullptr == _other)
	{
		GameEngineDebug::AssertFalse();
		return false;
	}

	if (nullptr == arrFunc_[GetTypeToIndex()][_other->GetTypeToIndex()])
	{
		GameEngineDebug::MsgBoxError("�������� ���� �浹�Լ��� �̿��Ϸ��� �մϴ�.");
		return false;
	}

	return arrFunc_[GetTypeToIndex()][_other->GetTypeToIndex()](this, _other);
}

void GameEngineCollision::SetImage(std::string _ImageName) 
{
	GameEngineImageFile* ImagePtr = GameEngineImage::GetInst().FindGameImage(_ImageName);

	if (nullptr == ImagePtr)
	{
		GameEngineDebug::AssertFalse();
		return;
	}

	imageptr_ = ImagePtr;
}

GameEngineCollision* GameEngineCollision::CollisionGroupCheckOne(int _otherIndex)
{
	// ��� �׷��� ���;� �ϴ� ������ �����Ҽ� �ִ�.
	if (nullptr == this)
	{
		GameEngineDebug::AssertFalse();
		return nullptr;
	}

	if (nullptr == actor_)
	{
		GameEngineDebug::AssertFalse();
		return nullptr;
	}

	if (nullptr == actor_->GetLevel())
	{
		GameEngineDebug::AssertFalse();
		return nullptr;
	}

	// ����ȭ
	std::list<GameEngineCollision*>& GroupList = actor_->GetLevel()->GetCollisionList(_otherIndex);

	if (true == GroupList.empty())
	{
		return nullptr;
	}

	std::list<GameEngineCollision*>::iterator StartIter = GroupList.begin();
	std::list<GameEngineCollision*>::iterator EndIter = GroupList.end();
	for (; StartIter != EndIter; ++StartIter)
	{
		if (true == CollisionCheck(*StartIter))
		{
			return *StartIter;
		}
	}
	
	return nullptr;
}


// ���� xxx�׷쿡 ���� �浹ü�ε�. ��� xxx �׷�� ���δ� �浹�� ���� ������ ���ø� �˴ϴ�.
std::list<GameEngineCollision*> GameEngineCollision::CollisionGroupCheck(int _otherIndex)
{
	std::list<GameEngineCollision*> ReturnList;

	// ��� �׷��� ���;� �ϴ� ������ �����Ҽ� �ִ�.
	if (nullptr == this)
	{
		GameEngineDebug::AssertFalse();
		return ReturnList;
	}

	if (nullptr == actor_)
	{
		GameEngineDebug::AssertFalse();
		return ReturnList;
	}

	if (nullptr == actor_->GetLevel())
	{
		GameEngineDebug::AssertFalse();
		return ReturnList;
	}

	// ����ȭ
	std::list<GameEngineCollision*>& GroupList = actor_->GetLevel()->GetCollisionList(_otherIndex);

	if (true == GroupList.empty())
	{
		return ReturnList;
	}

	std::list<GameEngineCollision*>::iterator StartIter = GroupList.begin();
	std::list<GameEngineCollision*>::iterator EndIter = GroupList.end();
	for (; StartIter != EndIter; ++StartIter)
	{
		if (true == CollisionCheck(*StartIter))
		{
			ReturnList.push_back(*StartIter);
		}
	}

	return ReturnList;
}

void GameEngineCollision::DebugRender() 
{
	GameEngineImageFile* BackBufferImage = GameEngineImage::GetInst().GetBackBufferImage();

	float4 RenderPos = GetDebugRenderPos();

	switch (colType_)
	{
	case CollisionCheckType::IMAGE:
		break;
	case CollisionCheckType::POINT:
	{
		Rectangle(BackBufferImage->GetDC(),
			RenderPos.ix() - 5,
			RenderPos.iy() - 5,
			RenderPos.ix() + 5,
			RenderPos.iy() + 5);
	}
		break;
	case CollisionCheckType::RECT:
	{
		Rectangle(BackBufferImage->GetDC(),
			RenderPos.ix() - size_.ihx(),
			RenderPos.iy() - size_.ihy(),
			RenderPos.ix() + size_.ihx(),
			RenderPos.iy() + size_.ihy());
		break;
	}
	case CollisionCheckType::LINE:
		break;
	case CollisionCheckType::CIRCLE:
		break;
	case CollisionCheckType::POLYGON2D:
		break;
	case CollisionCheckType::AABBBOX:
		break;
	case CollisionCheckType::OBBBOX:
		break;
	case CollisionCheckType::SPHERE:
		break;
	case CollisionCheckType::POLYGON3D:
		break;
	case CollisionCheckType::MAX:
		break;
	default:
		break;
	}
}

Figure GameEngineCollision::GetFigure() 
{
	return { actor_->GetPos() + Pivot_, size_ };
}

float4 GameEngineCollision::GetDebugRenderPos() 
{
	if (false == isCamEffect_)
	{
		return actor_->GetPos() + Pivot_;
	}

	return actor_->GetCamEffectPos() + Pivot_;
}