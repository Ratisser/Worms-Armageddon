#include "DrumActor.h"
#include <GameEngineWindow.h>
#include <GameEngineRenderer.h>
#include <GameEngineCollision.h>
#include <GameEngineTime.h>

#include "eCollisionGroup.h"
#include "eCollisionCheckColor.h"


DrumActor::DrumActor():
	Phase_(0.f),
	mainSpriteRender_(nullptr),
	groundCollision_(nullptr),
	BodyCollision_(nullptr),
	DrumCollision_(false)
	// default constructer ����Ʈ ������
{

}

DrumActor::~DrumActor() // default destructer ����Ʈ �Ҹ���
{

}

DrumActor::DrumActor(DrumActor&& _other) noexcept :
	Phase_(0.f),
	mainSpriteRender_(nullptr) , // default RValue Copy constructer ����Ʈ RValue ���������
	groundCollision_(nullptr),
	BodyCollision_(nullptr),
	DrumCollision_(false)// default RValue Copy constructer ����Ʈ RValue ���������
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
	float deltaTime = GameEngineTime::GetInst().GetDeltaTime();

	if (DrumGroupCollision((int)eCollisionGroup::FLAME)) // �Ҳ�, ������ ��� �浹�� �µ��� �ø���, // ���� �µ� ���޽� ����
	{
		Phase_ += 10.f * deltaTime;

		if (Phase_ >= 100.f)
		{
			DrumExplode();
		}
	}

	if (DrumGroupCollision((int)eCollisionGroup::WEAPON))
	{
		DrumExplode();
	}

	if (true == DrumCollision_)
	{
		DrumExplode();
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
	groundCollision_ = CreateCollision(static_cast<int>(eCollisionGroup::GIMMICK_OBJECT), CollisionCheckType::POINT);
	groundCollision_->SetColorCheck(static_cast<DWORD>(eCollisionCheckColor::MAP));
	groundCollision_->SetPivot({ 0.0f, 30.f });

	BodyCollision_ = CreateCollision(static_cast<int>(eCollisionGroup::GIMMICK_OBJECT), CollisionCheckType::POINT);
	BodyCollision_->SetColorCheck(static_cast<DWORD>(eCollisionCheckColor::MAP));
	BodyCollision_->SetPivot({ 0.0f, 30.f });
}

void DrumActor::DrumBoil(float kelvin)
{
	Phase_ = kelvin;
}

void DrumActor::DrumExplode()
{
	// ��
}

void DrumActor::DrumCollision(GameEngineCollision* Collider_)
{
	if (BodyCollision_->CollisionCheck(Collider_))
	{
		DrumCollision_ = true;
	}
}

bool DrumActor::DrumGroupCollision(int _Group_enum)
{
	std::list<GameEngineCollision*> Clist = BodyCollision_->CollisionGroupCheck(_Group_enum);

	auto iterfirst = Clist.begin();
	auto iterEnd = Clist.end();

	for(; iterfirst != iterEnd; iterfirst++)
	{
		if ((*iterfirst)->CollisionCheck(BodyCollision_))
		{
			DrumCollision_ = true;
			return true;
		}
	}
	return false;
}

