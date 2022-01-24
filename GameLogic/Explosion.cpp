#include "Explosion.h"
#include "EffectCircle.h"
#include "EffectElipse.h"
#include "EffectSmklt.h"
#include "EffectSmkdrk.h"
#include "EffectFlame.h"
#include "GameEngineLevel.h"
#include "Petroleum.h"

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
	EffectActor* Effect;
	float4 OwnerPos;
	GameEngineMath::Random random;
	float RandomFloat;
	float degree;
	float4 RandomRot = { 1.f,0.f,0.f };

	Effect = GetLevel()->CreateActor<Effect::Circle25>();
	Effect->SetPos(pos_);
	Effect->SetRenderOrder((int)RenderOrder::Effect);

	Effect = GetLevel()->CreateActor<Effect::Elipse25>();
	Effect->SetPos(pos_);
	Effect->SetRenderOrder((int)RenderOrder::Effect);

	for (int i = 0; i < 9; ++i)
	{
		// 초기화
		OwnerPos = pos_; // 매 생성마다 초기화
		RandomRot = { 1.f,0.f,0.f }; //초기화

		//렌덤값
		RandomFloat = random.RandomFloat(-2.f, 2.f);// 10~40 사이 임의의 값, 임의 반지름이 될것
		degree = i * 36.f;

		//변형
		RandomRot = RandomRot.DegreeTofloat2(degree); // 길이 1의 방향 벡터 0~360도 임의의 각도	
		RandomRot.x *= RandomFloat; // 임의 각도에 반지름 길이 곱하기
		RandomRot.y *= RandomFloat;

		OwnerPos += RandomRot;

		Effect = GetLevel()->CreateActor<Effect::Smklt25>();
		Effect->SetPos(OwnerPos);
		Effect->SetRenderOrder((int)RenderOrder::Effect);
	}

	// Flame 중심 pos 부터 +- 15도 임의 방향으로 나가게끔 임의 생성
	{
		RandomFloat = random.RandomFloat(-10.f, 10.f);

		RandomRot = { 0.f,1.f,0.f }; //초기화

		degree = -30.f + RandomFloat - 90.f;
		RandomRot = RandomRot.DegreeTofloat2(degree);

		Effect::Flame1* Flame1Effect = GetLevel()->CreateActor<Effect::Flame1>();
		Flame1Effect->SetDir(RandomRot);
		Flame1Effect->SetPos(pos_);
		Flame1Effect->SetRenderOrder((int)RenderOrder::Effect);


		RandomFloat = random.RandomFloat(-10.f, 10.f);

		RandomRot = { 0.f,1.f,0.f }; //초기화

		degree = -15.f + RandomFloat - 90.f;
		RandomRot = RandomRot.DegreeTofloat2(degree);

		Effect::Flame2* Flame2Effect = GetLevel()->CreateActor<Effect::Flame2>();
		Flame2Effect->SetDir(RandomRot);
		Flame2Effect->SetPos(pos_);
		Flame2Effect->SetRenderOrder((int)RenderOrder::Effect);



		RandomFloat = random.RandomFloat(-10.f, 10.f);

		RandomRot = { 0.f,1.f,0.f }; //초기화

		degree = 0.f + RandomFloat - 90.f;
		RandomRot = RandomRot.DegreeTofloat2(degree);

		Flame1Effect = GetLevel()->CreateActor<Effect::Flame1>();
		Flame1Effect->SetDir(RandomRot);
		Flame1Effect->SetPos(pos_);
		Flame1Effect->SetRenderOrder((int)RenderOrder::Effect);



		RandomFloat = random.RandomFloat(-10.f, 10.f);

		RandomRot = { 0.f,1.f,0.f }; //초기화

		degree = 15.f + RandomFloat - 90.f;
		RandomRot = RandomRot.DegreeTofloat2(degree);

		Flame2Effect = GetLevel()->CreateActor<Effect::Flame2>();
		Flame2Effect->SetDir(RandomRot);
		Flame2Effect->SetPos(pos_);
		Flame2Effect->SetRenderOrder((int)RenderOrder::Effect);



		RandomFloat = random.RandomFloat(-10.f, 10.f);

		RandomRot = { 0.f,1.f,0.f }; //초기화

		degree = 30.f + RandomFloat - 90.f;
		RandomRot = RandomRot.DegreeTofloat2(degree);

		Flame2Effect = GetLevel()->CreateActor<Effect::Flame2>();
		Flame2Effect->SetDir(RandomRot);
		Flame2Effect->SetPos(pos_);
		Flame2Effect->SetRenderOrder((int)RenderOrder::Effect);
	}
	Death();
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
	EffectActor* Effect;
	float4 OwnerPos;
	GameEngineMath::Random random;
	float RandomFloat;
	float degree;
	float4 RandomRot = { 1.f,0.f,0.f };

	Effect = GetLevel()->CreateActor<Effect::Circle50>();
	Effect->SetPos(pos_);
	Effect->SetRenderOrder((int)RenderOrder::Effect);

	Effect = GetLevel()->CreateActor<Effect::Elipse50>();
	Effect->SetPos(pos_);
	Effect->SetRenderOrder((int)RenderOrder::Effect);

	for (int i = 0; i < 9; ++i)
	{
		// 초기화
		OwnerPos = pos_; // 매 생성마다 초기화
		RandomRot = { 1.f,0.f,0.f }; //초기화

		//렌덤값
		RandomFloat = random.RandomFloat(-10.f, 10.f);// 10~40 사이 임의의 값, 임의 반지름이 될것
		degree = i * 36.f;

		//변형
		RandomRot = RandomRot.DegreeTofloat2(degree); // 길이 1의 방향 벡터 0~360도 임의의 각도	
		RandomRot.x *= RandomFloat; // 임의 각도에 반지름 길이 곱하기
		RandomRot.y *= RandomFloat;

		OwnerPos += RandomRot;

		Effect = GetLevel()->CreateActor<Effect::Smklt50>();
		Effect->SetPos(OwnerPos);
		Effect->SetRenderOrder((int)RenderOrder::Effect);
	}

	// Flame 중심 pos 부터 +- 15도 임의 방향으로 나가게끔 임의 생성
	{
		RandomFloat = random.RandomFloat(-10.f, 10.f);

		RandomRot = { 0.f,1.f,0.f }; //초기화

		degree = -30.f + RandomFloat - 90.f;
		RandomRot = RandomRot.DegreeTofloat2(degree);

		Effect::Flame1* Flame1Effect = GetLevel()->CreateActor<Effect::Flame1>();
		Flame1Effect->SetDir(RandomRot);
		Flame1Effect->SetPos(pos_);
		Flame1Effect->SetRenderOrder((int)RenderOrder::Effect);


		RandomFloat = random.RandomFloat(-10.f, 10.f);

		RandomRot = { 0.f,1.f,0.f }; //초기화

		degree = -15.f + RandomFloat - 90.f;
		RandomRot = RandomRot.DegreeTofloat2(degree);

		Effect::Flame2* Flame2Effect = GetLevel()->CreateActor<Effect::Flame2>();
		Flame2Effect->SetDir(RandomRot);
		Flame2Effect->SetPos(pos_);
		Flame2Effect->SetRenderOrder((int)RenderOrder::Effect);



		RandomFloat = random.RandomFloat(-10.f, 10.f);

		RandomRot = { 0.f,1.f,0.f }; //초기화

		degree = 0.f + RandomFloat - 90.f;
		RandomRot = RandomRot.DegreeTofloat2(degree);

		Flame1Effect = GetLevel()->CreateActor<Effect::Flame1>();
		Flame1Effect->SetDir(RandomRot);
		Flame1Effect->SetPos(pos_);
		Flame1Effect->SetRenderOrder((int)RenderOrder::Effect);



		RandomFloat = random.RandomFloat(-10.f, 10.f);

		RandomRot = { 0.f,1.f,0.f }; //초기화

		degree = 15.f + RandomFloat - 90.f;
		RandomRot = RandomRot.DegreeTofloat2(degree);

		Flame2Effect = GetLevel()->CreateActor<Effect::Flame2>();
		Flame2Effect->SetDir(RandomRot);
		Flame2Effect->SetPos(pos_);
		Flame2Effect->SetRenderOrder((int)RenderOrder::Effect);



		RandomFloat = random.RandomFloat(-10.f, 10.f);

		RandomRot = { 0.f,1.f,0.f }; //초기화

		degree = 30.f + RandomFloat - 90.f;
		RandomRot = RandomRot.DegreeTofloat2(degree);

		Flame2Effect = GetLevel()->CreateActor<Effect::Flame2>();
		Flame2Effect->SetDir(RandomRot);
		Flame2Effect->SetPos(pos_);
		Flame2Effect->SetRenderOrder((int)RenderOrder::Effect);
	}
	Death();
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
	EffectActor* Effect;
	float4 OwnerPos;
	GameEngineMath::Random random;
	float RandomFloat;
	float degree;
	float4 RandomRot = { 1.f,0.f,0.f };

	Effect = GetLevel()->CreateActor<Effect::Circle75>();
	Effect->SetPos(pos_);
	Effect->SetRenderOrder((int)RenderOrder::Effect);

	Effect = GetLevel()->CreateActor<Effect::Elipse75>();
	Effect->SetPos(pos_);
	Effect->SetRenderOrder((int)RenderOrder::Effect);

	for (int i = 0; i < 9; ++i)
	{
		// 초기화
		OwnerPos = pos_; // 매 생성마다 초기화
		RandomRot = { 1.f,0.f,0.f }; //초기화

		//렌덤값
		RandomFloat = random.RandomFloat(-10.f, 10.f);// 10~40 사이 임의의 값, 임의 반지름이 될것
		degree = i * 36.f;

		//변형
		RandomRot = RandomRot.DegreeTofloat2(degree); // 길이 1의 방향 벡터 0~360도 임의의 각도	
		RandomRot.x *= RandomFloat; // 임의 각도에 반지름 길이 곱하기
		RandomRot.y *= RandomFloat;

		OwnerPos += RandomRot;

		Effect = GetLevel()->CreateActor<Effect::Smklt75>();
		Effect->SetPos(OwnerPos);
		Effect->SetRenderOrder((int)RenderOrder::Effect);
	}

	// Flame 중심 pos 부터 +- 15도 임의 방향으로 나가게끔 임의 생성
	{
		RandomFloat = random.RandomFloat(-10.f, 10.f);

		RandomRot = { 0.f,1.f,0.f }; //초기화

		degree = -30.f + RandomFloat - 90.f;
		RandomRot = RandomRot.DegreeTofloat2(degree);

		Effect::Flame1* Flame1Effect = GetLevel()->CreateActor<Effect::Flame1>();
		Flame1Effect->SetDir(RandomRot);
		Flame1Effect->SetPos(pos_);
		Flame1Effect->SetRenderOrder((int)RenderOrder::Effect);


		RandomFloat = random.RandomFloat(-10.f, 10.f);

		RandomRot = { 0.f,1.f,0.f }; //초기화

		degree = -15.f + RandomFloat - 90.f;
		RandomRot = RandomRot.DegreeTofloat2(degree);

		Effect::Flame2* Flame2Effect = GetLevel()->CreateActor<Effect::Flame2>();
		Flame2Effect->SetDir(RandomRot);
		Flame2Effect->SetPos(pos_);
		Flame2Effect->SetRenderOrder((int)RenderOrder::Effect);



		RandomFloat = random.RandomFloat(-10.f, 10.f);

		RandomRot = { 0.f,1.f,0.f }; //초기화

		degree = 0.f + RandomFloat - 90.f;
		RandomRot = RandomRot.DegreeTofloat2(degree);

		Flame1Effect = GetLevel()->CreateActor<Effect::Flame1>();
		Flame1Effect->SetDir(RandomRot);
		Flame1Effect->SetPos(pos_);
		Flame1Effect->SetRenderOrder((int)RenderOrder::Effect);



		RandomFloat = random.RandomFloat(-10.f, 10.f);

		RandomRot = { 0.f,1.f,0.f }; //초기화

		degree = 15.f + RandomFloat - 90.f;
		RandomRot = RandomRot.DegreeTofloat2(degree);

		Flame2Effect = GetLevel()->CreateActor<Effect::Flame2>();
		Flame2Effect->SetDir(RandomRot);
		Flame2Effect->SetPos(pos_);
		Flame2Effect->SetRenderOrder((int)RenderOrder::Effect);



		RandomFloat = random.RandomFloat(-10.f, 10.f);

		RandomRot = { 0.f,1.f,0.f }; //초기화

		degree = 30.f + RandomFloat - 90.f;
		RandomRot = RandomRot.DegreeTofloat2(degree);

		Flame2Effect = GetLevel()->CreateActor<Effect::Flame2>();
		Flame2Effect->SetDir(RandomRot);
		Flame2Effect->SetPos(pos_);
		Flame2Effect->SetRenderOrder((int)RenderOrder::Effect);
	}
	Death();
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
	EffectActor* Effect;

	Effect = GetLevel()->CreateActor<Effect::Circle100>();
	Effect->SetPos(pos_);
	Effect->SetRenderOrder((int)RenderOrder::Effect);

	Effect = GetLevel()->CreateActor<Effect::Elipse100>();
	Effect->SetPos(pos_);
	Effect->SetRenderOrder((int)RenderOrder::Effect);

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
		Effect->SetRenderOrder((int)RenderOrder::Effect);
		Effect->SetDir(RandomRot);
	}

	// Flame 중심 pos 부터 +- 15도 임의 방향으로 나가게끔 임의 생성
	{
		/*
		-22.5
		-7.5
		7.5
		22.5	
		*/

		RandomFloat = random.RandomFloat(-10.f, 10.f);

		RandomRot = { 0.f,1.f,0.f }; //초기화
		
		degree = -30.f + RandomFloat - 90.f;
		RandomRot = RandomRot.DegreeTofloat2(degree);

		Effect::Flame1 * Flame1Effect = GetLevel()->CreateActor<Effect::Flame1>();
		Flame1Effect->SetDir(RandomRot);
		Flame1Effect->SetPos(pos_);
		Flame1Effect->SetRenderOrder((int)RenderOrder::Effect);


		RandomFloat = random.RandomFloat(-10.f, 10.f);

		RandomRot = { 0.f,1.f,0.f }; //초기화

		degree = -15.f + RandomFloat - 90.f;
		RandomRot = RandomRot.DegreeTofloat2(degree); 

		Effect::Flame2* Flame2Effect = GetLevel()->CreateActor<Effect::Flame2>();
		Flame2Effect->SetDir(RandomRot);
		Flame2Effect->SetPos(pos_);
		Flame2Effect->SetRenderOrder((int)RenderOrder::Effect);



		RandomFloat = random.RandomFloat(-10.f, 10.f);

		RandomRot = { 0.f,1.f,0.f }; //초기화

		degree = 0.f + RandomFloat - 90.f;
		RandomRot = RandomRot.DegreeTofloat2(degree); 

		Flame1Effect = GetLevel()->CreateActor<Effect::Flame1>();
		Flame1Effect->SetDir(RandomRot);
		Flame1Effect->SetPos(pos_);
		Flame1Effect->SetRenderOrder((int)RenderOrder::Effect);



		RandomFloat = random.RandomFloat(-10.f, 10.f);

		RandomRot = { 0.f,1.f,0.f }; //초기화

		degree = 15.f + RandomFloat - 90.f;
		RandomRot = RandomRot.DegreeTofloat2(degree); 

		Flame2Effect = GetLevel()->CreateActor<Effect::Flame2>();
		Flame2Effect->SetDir(RandomRot);
		Flame2Effect->SetPos(pos_);
		Flame2Effect->SetRenderOrder((int)RenderOrder::Effect);



		RandomFloat = random.RandomFloat(-10.f, 10.f);

		RandomRot = { 0.f,1.f,0.f }; //초기화

		degree = 30.f + RandomFloat - 90.f;
		RandomRot = RandomRot.DegreeTofloat2(degree);

		Flame2Effect = GetLevel()->CreateActor<Effect::Flame2>();
		Flame2Effect->SetDir(RandomRot);
		Flame2Effect->SetPos(pos_);
		Flame2Effect->SetRenderOrder((int)RenderOrder::Effect);
	}

	Death();
}

void EffectBundle::Explosion::Size100::UpdateBefore()
{
}

void EffectBundle::Explosion::Size100::Update()
{
}

void EffectBundle::Explosion::Size100::UpdateAfter()
{
}

void EffectBundle::Explosion::Size100::Render()
{
}
