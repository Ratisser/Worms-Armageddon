#include "Petroleum.h"
#include <GameEngineWindow.h>
#include <GameEngineRenderer.h>
#include <GameEngineCollision.h>
#include <GameEngineTime.h>

#include "eCollisionGroup.h"
#include "eCollisionCheckColor.h"

#include "PlayLevel.h"

#include "Worm.h"
#include "PetroleumManager.h"

// 메모 : 간혹 폭발 후 소환이 안돼는 문제가 있음
// 원인 파악중

Petroleum::Petroleum() :
	Max_LifeTime_(5.f),
	Cur_LifeTime_(0.f),
	GravitySpeed(0.f),
	GravityAcc(0.f),
	WindAcc_(0.f),
	degree_(0.f),
	WindSpeed_(0.f),
	mainSpriteRender_(nullptr),
	groundCollision_(nullptr),
	BodyCollision_(nullptr),
	Burn_(false),
	Isground_(false),
	isLive_(true),
	CountSecond_{}
{

}

Petroleum::~Petroleum() // default destructer 디폴트 소멸자
{

}

Petroleum::Petroleum(Petroleum&& _other) noexcept :
	Max_LifeTime_(5.f),
	Cur_LifeTime_(0.f),
	GravitySpeed(0.f),
	GravityAcc(0.f),
	WindAcc_(0.f),
	degree_(0.f),
	WindSpeed_(0.f),
	mainSpriteRender_(nullptr),
	groundCollision_(nullptr),
	BodyCollision_(nullptr),
	Burn_(false),
	Isground_(false),
	CountSecond_{}
{

}

void Petroleum::Start()
{
	GravityAcc = 6.f;

	mainSpriteRender_ = CreateRenderer("petrol-1");

	mainSpriteRender_->CreateAnimation("petrol60", "petrol60", 0, 19, true, 0.05f);
	mainSpriteRender_->CreateAnimation("petrol50", "petrol50", 0, 19, true, 0.05f);
	mainSpriteRender_->CreateAnimation("petrol40", "petrol40", 0, 19, true, 0.05f);
	mainSpriteRender_->CreateAnimation("petrol30", "petrol30", 0, 19, true, 0.05f);
	mainSpriteRender_->CreateAnimation("petrol20", "petrol20", 0, 19, true, 0.05f);

	mainSpriteRender_->CreateAnimation("petrol-1", "petrol-1", 0, 63, true, 100.f);
	mainSpriteRender_->CreateAnimation("petrol-2", "petrol-2", 0, 63, true, 100.f);
	mainSpriteRender_->CreateAnimation("petrol-3", "petrol-3", 0, 63, true, 100.f);
	mainSpriteRender_->CreateAnimation("petrol-4", "petrol-4", 0, 63, true, 100.f);

	mainSpriteRender_->ChangeAnimation("petrol-1");

	initCollision();
}

void Petroleum::UpdateBefore()
{
}

void Petroleum::Update()
{
	//deltaTime_ = GameEngineTime::GetInst().GetDeltaTime();

	//if (nullptr == groundCollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MAP)))
	//{	
	//	WindSpeed_ += WindAcc_;
	//	GravitySpeed += GravityAcc;
	//	Isground_ = false;

	//	if (true == Burn_)
	//	{
	//		SetMove((Dir_.x+ WindSpeed_) * deltaTime_, (Dir_.y+ GravitySpeed) * deltaTime_);
	//	}
	//	else
	//	{
	//		prevPos_ = pos_;
	//		SetMove((Dir_.x + WindSpeed_) * deltaTime_, (Dir_.y + GravitySpeed) * deltaTime_);
	//	}
	//}
	//else if(false == Isground_)
	//{
	//	Dir_.y = 0.f;
	//	Dir_.x = 0.f;
	//	GravitySpeed = 0.f;
	//	WindSpeed_ = 0.f;
	//	Burn_ = true;
	//	Isground_ = true;
	//	// x값에 풍향이 적용되게
	//	// 비탈을 만나면 비탈로 슬금슬금
	//	// 
	//}

	//if (false == Burn_)
	//{
	//	Cur_LifeTime_ += deltaTime_;

	//	float4 moveVector = pos_ - prevPos_;
	//	moveVector.Normalize2D();

	//	float theta;

	//	if (pos_.x < prevPos_.x)
	//	{
	//		theta = float4::DOWN.x * moveVector.x + float4::DOWN.y * moveVector.y;
	//	}
	//	else
	//	{
	//		theta = float4::UP.x * moveVector.x + float4::UP.y * moveVector.y;
	//	}

	//	theta = acos(theta);
	//	degree_ = theta * (180.f / 3.14f);

	//	if (pos_.x < prevPos_.x)
	//	{
	//		degree_ += 180.f;
	//	}

	//	degree_ += 2.8125f;

	//	if (degree_ > 360.f)
	//	{
	//		degree_ -= 360.f;
	//	}

	//	int frameIndex = (int)(degree_ / 5.625f);

	//	if (Cur_LifeTime_ < 0.3f)
	//	{
	//		mainSpriteRender_->ChangeAnimation("petrol-2", std::string("petrol-2"));
	//		mainSpriteRender_->SetAnimationCurrentFrame(frameIndex);
	//	}

	//	else if (Cur_LifeTime_ < 0.45f)
	//	{
	//		mainSpriteRender_->ChangeAnimation("petrol-3", std::string("petrol-3"));
	//		mainSpriteRender_->SetAnimationCurrentFrame(frameIndex);
	//	}

	//	else if (Cur_LifeTime_ < 0.6f)
	//	{
	//		mainSpriteRender_->ChangeAnimation("petrol-4", std::string("petrol-4")); 
	//		mainSpriteRender_->SetAnimationCurrentFrame(frameIndex);
	//	}

	//	else if (Cur_LifeTime_ < 0.75f)
	//	{			
	//		mainSpriteRender_->ChangeAnimation("petrol60", std::string("petrol60"));
	//		Burn_ = true;
	//		Cur_LifeTime_ = 0.f;
	//	}
	//}

	//else if(true == Isground_)
	//{
	//	if (Cur_LifeTime_ < 1.5f)
	//	{
	//		mainSpriteRender_->ChangeAnimation("petrol50", std::string("petrol50"));
	//	}
	//	else if (Cur_LifeTime_ < 2.3f)
	//	{
	//		mainSpriteRender_->ChangeAnimation("petrol40", std::string("petrol40"));
	//	}
	//	else if (Cur_LifeTime_ < 3.5f)
	//	{
	//		mainSpriteRender_->ChangeAnimation("petrol30", std::string("petrol30"));
	//	}
	//	else if (Cur_LifeTime_ < Max_LifeTime_)
	//	{
	//		mainSpriteRender_->ChangeAnimation("petrol20", std::string("petrol20"));
	//	}

	//	if (false == CountSecond_[static_cast<int>(Cur_LifeTime_)])
	//	{
	//		if (Cur_LifeTime_ < 2.f)
	//		{
	//			GetLevel<PlayLevel>()->GroundUpdate13(pos_);
	//		}

	//		if (Cur_LifeTime_ < 4.f)
	//		{
	//			GetLevel<PlayLevel>()->GroundUpdate6(pos_);
	//		}

	//		else
	//		{
	//			GetLevel<PlayLevel>()->GroundUpdate4(pos_);
	//		}

	//		CountSecond_[static_cast<int>(Cur_LifeTime_)] = true;
	//	}

	//	{
	//		std::list<GameEngineCollision*> ColList_ = BodyCollision_->CollisionGroupCheck(static_cast<int>(eCollisionGroup::PLAYER_HITBOX));

	//		if (false == ColList_.empty())
	//		{
	//			auto iter0 = ColList_.begin();
	//			auto iter1 = ColList_.end();

	//			for (; iter0 != iter1;)
	//			{
	//			#ifdef _DEBUG
	//				std::string name = (*iter0)->GetActor()->GetName();
	//				name = name.substr(0, 4);

	//				if (name != "Worm")
	//				{
	//					GameEngineDebug::MsgBoxError("Worm이 아닌 충돌체가 eCollisionGroup::PLAYER_HITBOX로 설정되었습니다.");
	//				}
	//			#endif // _DEBUG

	//				float4 Dir = (*iter0)->GetCollisionPoint() - pos_;
	//				Dir.Normalize2D();

	//				dynamic_cast<Worm*>((*iter0)->GetActor())->Damage(10.f, Dir);

	//				++iter0;
	//			}
	//		}
	//	}

	//	Cur_LifeTime_ += deltaTime_;
	//}


	//if (Cur_LifeTime_ >= Max_LifeTime_)
	//{
	//	Death();
	//	return;
	//}
}

void Petroleum::UpdateAfter()
{
}

void Petroleum::Render()
{
#ifdef _DEBUG	
	//if (GetLevel<PlayLevel>()->GetDebug())
	//{
	//	groundCollision_->DebugRender();
	//}
#endif // DEBUG
	mainSpriteRender_->AnimationUpdate();

}

void Petroleum::initCollision()
{
	BodyCollision_ = CreateCollision(static_cast<int>(eCollisionGroup::PETROLEUM_HITBOX), CollisionCheckType::CIRCLE);
	BodyCollision_->SetSize({ 10.f, 10.f });

	groundCollision_ = CreateCollision(static_cast<int>(eCollisionGroup::PETROLEUM), CollisionCheckType::POINT);
	groundCollision_->SetColorCheck(static_cast<DWORD>(eCollisionCheckColor::MAP));
	//groundCollision_->SetSize({ 10.f, 10.f });
	groundCollision_->SetPivot({ 0.f, 1.f });
}

void Petroleum::PetroleumMoveUpdate(float deltaTime_)
{
	{
		if (nullptr == groundCollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MAP)))
		{
			WindSpeed_ += WindAcc_;
			GravitySpeed += GravityAcc;
			Isground_ = false;

			if (true == Burn_)
			{
				SetMove((Dir_.x + WindSpeed_) * deltaTime_, (Dir_.y + GravitySpeed) * deltaTime_);
			}
			else
			{
				prevPos_ = pos_;
				SetMove((Dir_.x + WindSpeed_) * deltaTime_, (Dir_.y + GravitySpeed) * deltaTime_);
			}
		}
		else if (false == Isground_)
		{
			Dir_.y = 0.f;
			Dir_.x = 0.f;
			GravitySpeed = 0.f;
			WindSpeed_ = 0.f;
			Burn_ = true;
			Isground_ = true;
		}
	}

}

void Petroleum::PetroleumGroundUpdate(float deltaTime_)
{
	if (false == Burn_)
	{
		Cur_LifeTime_ += deltaTime_;

		float4 moveVector = pos_ - prevPos_;
		moveVector.Normalize2D();

		float theta;

		if (pos_.x < prevPos_.x)
		{
			theta = float4::DOWN.x * moveVector.x + float4::DOWN.y * moveVector.y;
		}
		else
		{
			theta = float4::UP.x * moveVector.x + float4::UP.y * moveVector.y;
		}

		theta = acos(theta);
		degree_ = theta * (180.f / 3.14f);

		if (pos_.x < prevPos_.x)
		{
			degree_ += 180.f;
		}

		degree_ += 2.8125f;

		if (degree_ > 360.f)
		{
			degree_ -= 360.f;
		}

		int frameIndex = (int)(degree_ / 5.625f);

		if (Cur_LifeTime_ < 0.3f)
		{
			mainSpriteRender_->ChangeAnimation("petrol-2", std::string("petrol-2"));
			mainSpriteRender_->SetAnimationCurrentFrame(frameIndex);
		}

		else if (Cur_LifeTime_ < 0.45f)
		{
			mainSpriteRender_->ChangeAnimation("petrol-3", std::string("petrol-3"));
			mainSpriteRender_->SetAnimationCurrentFrame(frameIndex);
		}

		else if (Cur_LifeTime_ < 0.6f)
		{
			mainSpriteRender_->ChangeAnimation("petrol-4", std::string("petrol-4"));
			mainSpriteRender_->SetAnimationCurrentFrame(frameIndex);
		}

		else if (Cur_LifeTime_ < 0.75f)
		{
			mainSpriteRender_->ChangeAnimation("petrol60", std::string("petrol60"));
			Burn_ = true;
			Cur_LifeTime_ = 0.f;
		}
	}
	else if (true == Isground_)
	{
		{
			if (Cur_LifeTime_ < 1.5f)
			{
				mainSpriteRender_->ChangeAnimation("petrol50", std::string("petrol50"));
			}
			else if (Cur_LifeTime_ < 2.3f)
			{
				mainSpriteRender_->ChangeAnimation("petrol40", std::string("petrol40"));
			}
			else if (Cur_LifeTime_ < 3.5f)
			{
				mainSpriteRender_->ChangeAnimation("petrol30", std::string("petrol30"));
			}
			else if (Cur_LifeTime_ < Max_LifeTime_)
			{
				mainSpriteRender_->ChangeAnimation("petrol20", std::string("petrol20"));
			}
		}

		if (false == CountSecond_[static_cast<int>(Cur_LifeTime_)])
		{
			if (Cur_LifeTime_ < 2.f)
			{
				GetLevel<PlayLevel>()->GroundUpdate13(pos_);
			}

			if (Cur_LifeTime_ < 4.f)
			{
				GetLevel<PlayLevel>()->GroundUpdate6(pos_);
			}

			else
			{
				GetLevel<PlayLevel>()->GroundUpdate4(pos_);
			}

			CountSecond_[static_cast<int>(Cur_LifeTime_)] = true;
		}

		{
			std::list<GameEngineCollision*> ColList_ = BodyCollision_->CollisionGroupCheck(static_cast<int>(eCollisionGroup::PLAYER_HITBOX));

			if (false == ColList_.empty())
			{
				auto iter0 = ColList_.begin();
				auto iter1 = ColList_.end();

				for (; iter0 != iter1;)
				{
#ifdef _DEBUG
					std::string name = (*iter0)->GetActor()->GetName();
					name = name.substr(0, 4);

					if (name != "Worm")
					{
						GameEngineDebug::MsgBoxError("Worm이 아닌 충돌체가 eCollisionGroup::PLAYER_HITBOX로 설정되었습니다.");
					}
#endif // _DEBUG
					float4 Dir = (*iter0)->GetCollisionPoint() - pos_;
					Dir.Normalize2D();

					dynamic_cast<Worm*>((*iter0)->GetActor())->Damage(10.f, Dir);

					++iter0;
				}
			}
		}

		Cur_LifeTime_ += deltaTime_;
	}

	if (Cur_LifeTime_ >= Max_LifeTime_)
	{
		SetisLive(false);
		return;
	}
}



