#include "Explosion.h"
#include "EffectCircle.h"
#include "EffectElipse.h"
#include "EffectSmklt.h"
#include "EffectSmkdrk.h"
#include "EffectFlame.h"
#include "GameEngineLevel.h"

// Size25

EffectBundle::Explosion::Size25::Size25()
{
}

EffectBundle::Explosion::Size25::~Size25()
{
}

EffectBundle::Explosion::Size25::Size25(Size25&& _other) noexcept
{
}

void EffectBundle::Explosion::Size25::Start()
{
}

void EffectBundle::Explosion::Size25::UpdateBefore()
{
}

void EffectBundle::Explosion::Size25::Update()
{
	EffectBundleActor::Update();
}

void EffectBundle::Explosion::Size25::UpdateAfter()
{
}

void EffectBundle::Explosion::Size25::Render()
{
}

// Size50

EffectBundle::Explosion::Size50::Size50()
{
}

EffectBundle::Explosion::Size50::~Size50()
{
}

EffectBundle::Explosion::Size50::Size50(Size50&& _other) noexcept
{
}

void EffectBundle::Explosion::Size50::Start()
{
}

void EffectBundle::Explosion::Size50::UpdateBefore()
{
}

void EffectBundle::Explosion::Size50::Update()
{
	EffectBundleActor::Update();
}

void EffectBundle::Explosion::Size50::UpdateAfter()
{
}

void EffectBundle::Explosion::Size50::Render()
{
}

// Size75

EffectBundle::Explosion::Size75::Size75()
{
}

EffectBundle::Explosion::Size75::~Size75()
{
}

EffectBundle::Explosion::Size75::Size75(Size75&& _other) noexcept
{
}

void EffectBundle::Explosion::Size75::Start()
{
}

void EffectBundle::Explosion::Size75::UpdateBefore()
{
}

void EffectBundle::Explosion::Size75::Update()
{
	EffectBundleActor::Update();
}

void EffectBundle::Explosion::Size75::UpdateAfter()
{
}

void EffectBundle::Explosion::Size75::Render()
{
}

// Size100

EffectBundle::Explosion::Size100::Size100()
{
}

EffectBundle::Explosion::Size100::~Size100()
{
}

EffectBundle::Explosion::Size100::Size100(Size100&& _other) noexcept
{
}

void EffectBundle::Explosion::Size100::Start()
{
	/*
	���� ����Ʈ

	100������ ��Ŭ
	100������ ������
	smklt100 ������ �뷫 10��
	�÷��� 6���� ����ٴϴ� smkdrk40

	*/
	EffectActor* Effect;

	Effect = GetLevel()->CreateActor<Effect::Circle100>();
	Effect->SetPos(pos_);
	EffectActorList.push_back(Effect);

	Effect = GetLevel()->CreateActor<Effect::Elipse100>();
	Effect->SetPos(pos_);
	EffectActorList.push_back(Effect);

	float4 OwnerPos;
	GameEngineMath::Random random;
	float RandomFloat;
	float degree;
	float4 RandomRot = { 1.f,0.f,0.f };
	//float semidiameter = 50.f;


	//������ 10~40 ���� ���������� 36�� �������� 10�� ���� �ǵ��� ����,
	for (int i = 0; i < 9; ++i)
	{
		// �ʱ�ȭ
		OwnerPos = pos_; // �� �������� �ʱ�ȭ
		RandomRot = { 1.f,0.f,0.f }; //�ʱ�ȭ

		//������
		RandomFloat = random.RandomFloat(10.f, 40.f);// 10~40 ���� ������ ��, ���� �������� �ɰ�
		degree = i * 36.f;

		//����
		RandomRot= RandomRot.DegreeTofloat2(degree); // ���� 1�� ���� ���� 0~360�� ������ ����	
		RandomRot.x *= RandomFloat; // ���� ������ ������ ���� ���ϱ�
		RandomRot.y *= RandomFloat;

		OwnerPos += RandomRot;

		Effect = GetLevel()->CreateActor<Effect::Smklt100>();
		Effect->SetPos(OwnerPos);
		EffectActorList.push_back(Effect);
	}

	// Flame �߽� pos ���� +- 15�� ���� �������� �����Բ� ���� ����
	{
		// �ѱ��� ���� ������ �����ϱ� ����, ���� -25 ���� 25����  ������, ���� +- 5�� �ֱ�
		/*
		-25
		-15
		-5
		5
		15
		25
		*/
		RandomFloat = random.RandomFloat(-5.f, 5.f);

		for (int i = 0; i < 2; ++i)
		{
			OwnerPos = pos_; // �� �������� �ʱ�ȭ
			OwnerPos = float4(); // ��ġ�� �°� ���� //�̿ϼ�
			Effect = GetLevel()->CreateActor<Effect::Flame1>();
			Effect->SetPos(OwnerPos);
			EffectActorList.push_back(Effect);
		}
		for (int i = 0; i < 2; ++i)
		{
			OwnerPos = pos_; // �� �������� �ʱ�ȭ
			OwnerPos = float4(); // ��ġ�� �°� ����
			Effect = GetLevel()->CreateActor<Effect::Flame2>();
			Effect->SetPos(OwnerPos);
			EffectActorList.push_back(Effect);
		}
	}

	EffectBundleActor::Start();
}

void EffectBundle::Explosion::Size100::UpdateBefore()
{
}

void EffectBundle::Explosion::Size100::Update()
{
	EffectBundleActor::Update();
}

void EffectBundle::Explosion::Size100::UpdateAfter()
{
}

void EffectBundle::Explosion::Size100::Render()
{
}
