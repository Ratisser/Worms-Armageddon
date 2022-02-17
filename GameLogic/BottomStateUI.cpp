#include "BottomStateUI.h"
#include "GameOptionInfo.h"

#include "Worm.h"
#include "UIController.h"

#include <EngineEnum.h>
#include <GameEngineRenderer.h>

BottomStateUI::BottomStateUI() :
	ParentWorm_(nullptr),
	ParentUI_(nullptr),
	WormIndex_(-1),
	PlayerColorIndex_(-1),
	PrevHP_(0),
	CurHP_(0),
	RenderPos_(float4::ZERO),
	CurDamage_(0.f),
	InitHPBarLen_(0.f),
	CurHPBarLen_(0.f),
	PrevHPBarLen_(0.f),
	TargetHPBarLen_(0.f),
	DecreaseSpeed_(1.f),
	DecreaseHPBar_(false),
	DeltaAccumulate_(0.f),
	FlagRenderer_(nullptr),
	NameRenderer_(nullptr),
	HPBarRenderer_(nullptr)
{
	SetRenderOrder(static_cast<int>(RenderOrder::UI3));
}

BottomStateUI::~BottomStateUI()
{
}

void BottomStateUI::Start()
{
	// ����
	FlagRenderer_ = CreateRenderer("BottomFlagKOR");
	FlagRenderer_->SetCameraEffectOff();

	// �÷��̾��
	NameRenderer_ = CreateRenderer("BottomNameTag");
	NameRenderer_->SetCameraEffectOff();

	// �÷��̾� Worm Total HP Bar
	HPBarRenderer_ = CreateRenderer("BottomHPbarR");
	HPBarRenderer_->SetCameraEffectOff();
}

void BottomStateUI::UpdateBefore()
{
	if (true == DecreaseHPBar_)
	{
		// ��ŸŸ�� ����
		PrevHPBarLen_ -= GameEngineTime::GetInst().GetDeltaTime() * DecreaseSpeed_;
		if (TargetHPBarLen_ >= PrevHPBarLen_)
		{
			if (1.f >= PrevHPBarLen_)
			{
				HPBarRenderer_->SetRenderSize(float4(1.f, 17.f));

				// ������Ʈ�� ȣ���ؼ� HPBar ����



				DecreaseHPBar_ = false;
				return;
			}

			CurHPBarLen_ = PrevHPBarLen_;
			DecreaseHPBar_ = false;

			return;
		}

		// ü�¹� ũ��� 100 x 17
		HPBarRenderer_->SetRenderSize(float4(PrevHPBarLen_, 17.f));
	}
}

void BottomStateUI::Update()
{
}

void BottomStateUI::UpdateAfter()
{

}

void BottomStateUI::Render()
{
	if (nullptr != FlagRenderer_)
	{
		FlagRenderer_->Render();
	}

	if (nullptr != NameRenderer_)
	{
		NameRenderer_->Render();
	}

	if (nullptr != HPBarRenderer_)
	{
		HPBarRenderer_->Render();
	}
}

int BottomStateUI::GetWormIndex()
{
	return WormIndex_;
}

float BottomStateUI::GetHPBarRenderSize() const
{
	// 1.f �����̸� �÷��̾� ������� ó��
	return TargetHPBarLen_;
}

void BottomStateUI::SetParentWorm(Worm* _Parent)
{
	ParentWorm_ = _Parent;
	InitHPBarLen_ = static_cast<float>(ParentWorm_->GetCurHP());
	if (InitHPBarLen_ >= 100.f)
	{
		DecreaseSpeed_ = 50.f;
	}
	else
	{
		DecreaseSpeed_ = 30.f;
	}

	PrevHP_ = CurHP_ = ParentWorm_->GetCurHP();

	PrevHPBarLen_ = CurHPBarLen_ = 100.f;
}

void BottomStateUI::SetParentUIController(UIController* _ParentUI)
{
	ParentUI_ = _ParentUI;
}

void BottomStateUI::GameStartInit(int _WormIndex)
{
	// ���� ������ �ϴܹ��� ������ �������� ����
	WormIndex_ = _WormIndex;

	// �������� �����Ѵ�.
	SettingRenderer();

	// �������� ��ġ�� �����Ѵ�.
	SettingRendererPos();
}

void BottomStateUI::SettingRenderer()
{
	// ���� ������ ����
	SetFlag();

	// �÷��̾� �̸� ������ ����
	SetPlayerName();

	// �÷��̾� Total HP Bar ������ ����
	SetPlayerHPBar();
}

void BottomStateUI::SetFlag()
{
	switch (WormIndex_)
	{
		case 0:
		{
			FlagRenderer_ = CreateRenderer("BottomFlagRUS");
			break;
		}
		case 1:
		{
			FlagRenderer_ = CreateRenderer("BottomFlagBRA");
			break;
		}
		case 2:
		{
			FlagRenderer_ = CreateRenderer("BottomFlagKOR");
			break;
		}
		case 3:
		{
			FlagRenderer_ = CreateRenderer("BottomFlagUSA");
			break;
		}
		case 4:
		{
			FlagRenderer_ = CreateRenderer("BottomFlagGER");
			break;
		}
		case 5:
		{
			FlagRenderer_ = CreateRenderer("BottomFlagJPN");
			break;
		}
		default:
		{
			FlagRenderer_ = CreateRenderer("BottomFlagRUS");
			break;
		}
	}
}

void BottomStateUI::SetPlayerName()
{
	// ���� ���õ� �÷��̾� �̸����� �÷��̾� ���� �˾Ƴ���.
	std::string CurPlayerName = GameOptionInfo::CurPlayerName[WormIndex_];
	char PlayerIndex = CurPlayerName[0];
	int PlayerNumber = (static_cast<int>(PlayerIndex) - '0');
	PlayerNumber -= 1;
	PlayerColorIndex_ = PlayerNumber;
	switch (PlayerColorIndex_)
	{
		case 0:
		{
			NameRenderer_ = CreateRenderer("BottomNameTag");
			break;
		}
		case 1:
		{
			NameRenderer_ = CreateRenderer("BottomNameTag2");
			break;
		}
		case 2:
		{
			NameRenderer_ = CreateRenderer("BottomNameTag3");
			break;
		}
		case 3:
		{
			NameRenderer_ = CreateRenderer("BottomNameTag4");
			break;
		}
		case 4:
		{
			NameRenderer_ = CreateRenderer("BottomNameTag5");
			break;
		}
		case 5:
		{
			NameRenderer_ = CreateRenderer("BottomNameTag6");
			break;
		}
		default:
		{
			NameRenderer_ = CreateRenderer("BottomNameTag");
			break;
		}
	}
}

void BottomStateUI::SetPlayerHPBar()
{
	switch (PlayerColorIndex_)
	{
		case 0:
		{
			HPBarRenderer_ = CreateRenderer("BottomHPbarR");
			break;
		}
		case 1:
		{
			HPBarRenderer_ = CreateRenderer("BottomHPbarB");
			break;
		}
		case 2:
		{
			HPBarRenderer_ = CreateRenderer("BottomHPbarG");
			break;
		}
		case 3:
		{
			HPBarRenderer_ = CreateRenderer("BottomHPbarY");
			break;
		}
		case 4:
		{
			HPBarRenderer_ = CreateRenderer("BottomHPbarP");
			break;
		}
		case 5:
		{
			HPBarRenderer_ = CreateRenderer("BottomHPbarS");
			break;
		}
		default:
		{
			HPBarRenderer_ = CreateRenderer("BottomHPbarR");
			break;
		}
	}
}

void BottomStateUI::SettingRendererPos()
{
	// ���� ������ ��ġ ����
	SetFlagPos();

	// �÷��̾� �̸� ������ ��ġ ����
	SetNamePos();

	// �÷��̾� Total HPBar ��ġ ����
	SetHPBarPos();
}

void BottomStateUI::SetFlagPos()
{
	int MaxWormCnt = GameOptionInfo::CurWormCnt;
	if (0 != MaxWormCnt)
	{
		// ���� ������ �÷��̾��� ������ �̿��Ͽ� ������ġ�� �����Ѵ�.
		float4 StartPos = float4::ZERO;
		--MaxWormCnt;
		switch (MaxWormCnt)
		{
			case 0:
			{
				StartPos = float4(605.f, 710.f);
				break;
			}
			case 1:
			{
				StartPos = float4(605.f, 690.f);
				break;
			}
			case 2:
			{
				StartPos = float4(605.f, 670.f);
				break;
			}
			case 3:
			{
				StartPos = float4(605.f, 650.f);
				break;
			}
			case 4:
			{
				StartPos = float4(605.f, 630.f);
				break;
			}
			case 5:
			{
				StartPos = float4(605.f, 610.f);
				break;
			}
			default:
			{
				StartPos = float4(0.f, 0.f);
				break;
			}
		}
		
		// Worm Index�� �̿��Ͽ� ���� ��ġ������ �ڽ��� ��ġ�� ����Ѵ�.
		StartPos.y += static_cast<float>(WormIndex_ * 20);
		FlagRenderer_->SetPivotPos(StartPos);
		FlagRenderer_->SetCameraEffectOff();
	}
}

void BottomStateUI::SetNamePos()
{
	int MaxWormCnt = GameOptionInfo::CurWormCnt;
	if (0 != MaxWormCnt)
	{
		// ���� ������ �÷��̾��� ������ �̿��Ͽ� ������ġ�� �����Ѵ�.
		float4 StartPos = float4::ZERO;
		--MaxWormCnt;
		switch (MaxWormCnt)
		{
			case 0:
			{
				StartPos = float4(572.f, 710.f);
				break;
			}
			case 1:
			{
				StartPos = float4(572.f, 690.f);
				break;
			}
			case 2:
			{
				StartPos = float4(572.f, 670.f);
				break;
			}
			case 3:
			{
				StartPos = float4(572.f, 650.f);
				break;
			}
			case 4:
			{
				StartPos = float4(572.f, 630.f);
				break;
			}
			case 5:
			{
				StartPos = float4(572.f, 610.f);
				break;
			}
			default:
			{
				StartPos = float4(0.f, 0.f);
				break;
			}
		}

		// Worm Index�� �̿��Ͽ� ���� ��ġ������ �ڽ��� ��ġ�� ����Ѵ�.
		StartPos.y += static_cast<float>(WormIndex_ * 20);
		NameRenderer_->SetPivotPos(StartPos);
		NameRenderer_->SetCameraEffectOff();
	}
}

void BottomStateUI::SetHPBarPos()
{
	int MaxWormCnt = GameOptionInfo::CurWormCnt;
	if (0 != MaxWormCnt)
	{
		// ���� ������ �÷��̾��� ������ �̿��Ͽ� ������ġ�� �����Ѵ�.
		RenderPos_ = float4::ZERO;
		--MaxWormCnt;
		switch (MaxWormCnt)
		{
			case 0:
			{
				RenderPos_ = float4(672.f, 710.f);
				break;
			}
			case 1:
			{
				RenderPos_ = float4(672.f, 690.f);
				break;
			}
			case 2:
			{
				RenderPos_ = float4(672.f, 670.f);
				break;
			}
			case 3:
			{
				RenderPos_ = float4(672.f, 650.f);
				break;
			}
			case 4:
			{
				RenderPos_ = float4(672.f, 630.f);
				break;
			}
			case 5:
			{
				RenderPos_ = float4(672.f, 610.f);
				break;
			}
			default:
			{
				RenderPos_ = float4(0.f, 0.f);
				break;
			}
		}

		// Worm Index�� �̿��Ͽ� ���� ��ġ������ �ڽ��� ��ġ�� ����Ѵ�.
		RenderPos_.y += static_cast<float>(WormIndex_ * 20);
		HPBarRenderer_->SetPivotPos(RenderPos_);
		HPBarRenderer_->SetCameraEffectOff();
	}
}

void BottomStateUI::DecreaseHPBar()
{
	// �ش� �÷��̾��� ü���� �������� ���� ��ǥġ ��� �� Flag On
	CurHP_ = ParentWorm_->GetCurHP();
	CurDamage_ = static_cast<float>(PrevHP_ - CurHP_);
	if (InitHPBarLen_ == 200.f)
	{
		CurDamage_ *= 0.5f;
	}
	else if (InitHPBarLen_ == 150.f)
	{
		CurDamage_ *= 0.7f;
	}
	else if (InitHPBarLen_ == 50.f)
	{
		CurDamage_ *= 2.f;
	}

	if (0.f >= CurHP_)
	{
		TargetHPBarLen_ = 1.f;
	}
	else
	{
		TargetHPBarLen_ = CurHPBarLen_ - static_cast<float>(CurDamage_);
		if (0.f >= TargetHPBarLen_)
		{
			TargetHPBarLen_ = 1.f;
		}
	}

	DecreaseHPBar_ = true;

	// ������ ����� �Ϸ�Ǿ����Ƿ� ����ü���� ����ü�¿� ����
	PrevHP_ = CurHP_;
}
