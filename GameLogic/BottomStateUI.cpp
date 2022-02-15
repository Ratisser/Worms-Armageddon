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
	FlagRenderer_(nullptr),
	NameRenderer_(nullptr),
	HPBarRenderer_(nullptr)
{
	SetRenderOrder(static_cast<int>(RenderOrder::UI3));
}

BottomStateUI::~BottomStateUI() // default destructer ����Ʈ �Ҹ���
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
}

void BottomStateUI::Update()
{
	// �÷��̾��� HP���¿� ���� �÷��̾� Worm Total HP Bar �̹��� ����
	if (nullptr != ParentWorm_)
	{
		CurHP_ = ParentWorm_->GetCurHP();
		if (PrevHP_ != CurHP_)
		{
			// ���� �÷��̾ �׾������� �ϴ� ���¹ٸ� ���δ�.
			if (0 >= CurHP_)
			{




				return;
			}

			// �ƴ϶�� ü�¹ٷ������� ��������ŭ ��Ƴ���.




			PrevHP_ = CurHP_;
		}
	}
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

void BottomStateUI::SetParentWorm(Worm* _Parent)
{
	ParentWorm_ = _Parent;
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
		float4 StartPos = float4::ZERO;
		--MaxWormCnt;
		switch (MaxWormCnt)
		{
			case 0:
			{
				StartPos = float4(672.f, 710.f);
				break;
			}
			case 1:
			{
				StartPos = float4(672.f, 690.f);
				break;
			}
			case 2:
			{
				StartPos = float4(672.f, 670.f);
				break;
			}
			case 3:
			{
				StartPos = float4(672.f, 650.f);
				break;
			}
			case 4:
			{
				StartPos = float4(672.f, 630.f);
				break;
			}
			case 5:
			{
				StartPos = float4(672.f, 610.f);
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
		HPBarRenderer_->SetPivotPos(StartPos);
		HPBarRenderer_->SetCameraEffectOff();
	}
}

