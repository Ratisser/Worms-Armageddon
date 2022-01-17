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
	폭발 이펙트

	100사이즈 써클
	100사이즈 엘렙스
	smklt100 여러개 대략 10개
	플레임 6개와 따라다니는 smkdrk40

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


	//반지름 10~40 사이 렌덤값으로 36도 간격으로 10개 생성 되도록 조정,
	for (int i = 0; i < 9; ++i)
	{
		// 초기화
		OwnerPos = pos_; // 매 생성마다 초기화
		RandomRot = { 1.f,0.f,0.f }; //초기화

		//렌덤값
		RandomFloat = random.RandomFloat(10.f, 40.f);// 10~40 사이 임의의 값, 임의 반지름이 될것
		degree = i * 36.f;

		//변형
		RandomRot= RandomRot.DegreeTofloat2(degree); // 길이 1의 방향 벡터 0~360도 임의의 각도	
		RandomRot.x *= RandomFloat; // 임의 각도에 반지름 길이 곱하기
		RandomRot.y *= RandomFloat;

		OwnerPos += RandomRot;

		Effect = GetLevel()->CreateActor<Effect::Smklt100>();
		Effect->SetPos(OwnerPos);
		EffectActorList.push_back(Effect);
	}

	// Flame 중심 pos 부터 +- 15도 임의 방향으로 나가게끔 임의 생성
	{
		// 한군데 몰려 생성을 방지하기 위해, 각기 -25 부터 25까지  나누고, 각기 +- 5값 주기
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
			OwnerPos = pos_; // 매 생성마다 초기화
			OwnerPos = float4(); // 위치에 맞게 변형 //미완성
			Effect = GetLevel()->CreateActor<Effect::Flame1>();
			Effect->SetPos(OwnerPos);
			EffectActorList.push_back(Effect);
		}
		for (int i = 0; i < 2; ++i)
		{
			OwnerPos = pos_; // 매 생성마다 초기화
			OwnerPos = float4(); // 위치에 맞게 변형
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
