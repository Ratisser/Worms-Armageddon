#include "DrumActor.h"
#include <GameEngineWindow.h>
#include <GameEngineRenderer.h>
#include <GameEngineCollision.h>
#include <GameEngineTime.h>
#include "PlayLevel.h"
#include "WindController.h"

#include "eCollisionGroup.h"
#include "eCollisionCheckColor.h"

#include "Petroleum.h"


DrumActor::DrumActor():
	Phase_(0.f),
	mainSpriteRender_(nullptr),
	groundCollision_(nullptr),
	BodyCollision_(nullptr),
	DrumCollision_(false),
	PetroleumSpeed(150.f),
	deltaTime_(0.f)
	// default constructer 디폴트 생성자
{

}

DrumActor::~DrumActor() // default destructer 디폴트 소멸자
{

}

DrumActor::DrumActor(DrumActor&& _other) noexcept :
	Phase_(0.f),
	mainSpriteRender_(nullptr) , // default RValue Copy constructer 디폴트 RValue 복사생성자
	groundCollision_(nullptr),
	BodyCollision_(nullptr),
	DrumCollision_(false),
	PetroleumSpeed(150.f),
	deltaTime_(0.f)
{

}

void DrumActor::Start()
{
	mainSpriteRender_ = CreateRenderer("oildrum1");

	mainSpriteRender_->CreateAnimation("Phase0", "oildrum1", 0, 19, true, 0.1f);
	mainSpriteRender_->CreateAnimation("Phase1", "oildrum2", 0, 19, true, 0.1f);
	mainSpriteRender_->CreateAnimation("Phase2", "oildrum3", 0, 19, true, 0.1f);
	mainSpriteRender_->CreateAnimation("Phase3", "oildrum4", 0, 19, true, 0.1f);

	mainSpriteRender_->ChangeAnimation("Phase0");

	initCollision();
}

void DrumActor::UpdateBefore()
{

}

void DrumActor::Update()
{
	if (nullptr == groundCollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MAP)))
	{
		SetMove(0.f,100.f* deltaTime_);
	}

	deltaTime_ = GameEngineTime::GetInst().GetDeltaTime();

	if (nullptr != BodyCollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::PETROLEUM)))
	{
		Phase_ += deltaTime_;
		
		if (Phase_ >= 3.f)
		{
			DrumExplode();
		}

		else if (Phase_ > 2.f)
		{
			int cur_frame = mainSpriteRender_->GetCurAnimationFrame();
			mainSpriteRender_->ChangeAnimation("Phase3");
			mainSpriteRender_->SetAnimationCurrentFrame(cur_frame);
		}
		else if (Phase_ > 1.f)
		{
			int cur_frame = mainSpriteRender_->GetCurAnimationFrame();
			mainSpriteRender_->ChangeAnimation("Phase2");
			mainSpriteRender_->SetAnimationCurrentFrame(cur_frame);
		}
		else if (Phase_ > 0.f)
		{
			int cur_frame = mainSpriteRender_->GetCurAnimationFrame();
			mainSpriteRender_->ChangeAnimation("Phase1");
			mainSpriteRender_->SetAnimationCurrentFrame(cur_frame);
		}
	}

	if (nullptr != BodyCollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::WEAPON)))
	{
		DrumExplode();
	}

	if (nullptr != BodyCollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::PLAYER)))
	{
		DrumExplode(); // 위 코드 외에 폭발이 적용될 경우
	}
}

void DrumActor::UpdateAfter()
{
}


void DrumActor::Render()
{
	mainSpriteRender_->AnimationUpdate();
}

void DrumActor::initCollision()
{
	groundCollision_ = CreateCollision(static_cast<int>(eCollisionGroup::DRUM), CollisionCheckType::POINT);
	groundCollision_->SetColorCheck(static_cast<DWORD>(eCollisionCheckColor::MAP));
	groundCollision_->SetPivot({ 10.f, 30.f });

	BodyCollision_ = CreateCollision(static_cast<int>(eCollisionGroup::DRUM), CollisionCheckType::RECT);
	BodyCollision_->SetSize({ 40.f, 40.f });
	BodyCollision_->SetPivot({ 20.f, 20.f });


}

void DrumActor::DrumBoil(float kelvin)
{
	Phase_ += kelvin;
}

void DrumActor::DrumExplode()
{
	GetLevel<PlayLevel>()->CreateExplosion75(pos_);

	GameEngineMath::Random random;
	float RandomFloat;
	float degree;
	float curwind = GetLevel<PlayLevel>()->GetWindController()->GetCurrentWindSpeed();
	float4 RandomRot = { 1.f,0.f,0.f };

	int count = 20;
	for (int i = 0; i < count; ++i)
	{
		RandomRot = { 1.f,0.f,0.f }; //초기화

		RandomFloat = random.RandomFloat(-30.f, 30.f);
		degree = (i * 360.f/(float)count) + RandomFloat;

		RandomRot = RandomRot.DegreeTofloat2(degree); 
		RandomRot.x += curwind;

		Petroleum* _Petroleum = GetLevel<PlayLevel>()->CreateActor<Petroleum>(pos_);
		_Petroleum->SetRenderOrder((int)RenderOrder::Effect);
		_Petroleum->SetDir(RandomRot* PetroleumSpeed);
	}

	Death();
}

void DrumActor::DrumCollision(GameEngineCollision* Collider_)
{
	//if (BodyCollision_->CollisionCheck(Collider_))
	//{
	//	DrumCollision_ = true;
	//}
}



