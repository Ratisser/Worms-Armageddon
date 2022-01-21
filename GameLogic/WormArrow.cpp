#include "WormArrow.h"
#include <GameEngineRenderer.h>
#include "Worm.h"
#include <GameEngineTime.h>
#include <GameEngineInput.h>
WormArrow::WormArrow() // default constructer ����Ʈ ������
{
	
}

WormArrow::~WormArrow() // default destructer ����Ʈ �Ҹ���
{

}

WormArrow::WormArrow(WormArrow&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
{
	SetRenderOrder(static_cast<int>(RenderOrder::Worm));
}

void WormArrow::Start()
{
	mainRender_ = CreateRenderer("arrowdnp");
	mainRender_->CreateAnimation("arrowdnp", "arrowdnp", 0, 29, true, 0.022f);
	mainRender_->ChangeAnimation("arrowdnp");
}
void WormArrow::UpdateBefore()
{

}
void WormArrow::Update()
{
	if (true == parent_->isFocused())
	{
		SetPos({ parent_->GetPos().x, (parent_->GetPos().y - 50.0f) });
		SetRenderOrder(static_cast<int>(RenderOrder::Worm));
	}

	if (false == parent_->isFocused())
	{
		SetMove(float4::UP * 600.0f * GameEngineTime::GetInst().GetDeltaTime());
	}
}

void WormArrow::UpdateAfter()
{
	if (-500.0f >= GetPos().y)
	{
		SetRenderOrder(0);
	}
}

void WormArrow::Render()
{
	mainRender_->AnimationUpdate();
}