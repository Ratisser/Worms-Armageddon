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
	// 국기
	FlagRenderer_ = CreateRenderer("BottomFlagKOR");
	FlagRenderer_->SetCameraEffectOff();

	// 플레이어명
	NameRenderer_ = CreateRenderer("BottomNameTag");
	NameRenderer_->SetCameraEffectOff();

	// 플레이어 Worm Total HP Bar
	HPBarRenderer_ = CreateRenderer("BottomHPbarR");
	HPBarRenderer_->SetCameraEffectOff();
}

void BottomStateUI::UpdateBefore()
{
	if (true == DecreaseHPBar_)
	{
		// 델타타임 누적
		PrevHPBarLen_ -= GameEngineTime::GetInst().GetDeltaTime() * DecreaseSpeed_;
		if (TargetHPBarLen_ >= PrevHPBarLen_)
		{
			if (1.f >= PrevHPBarLen_)
			{
				HPBarRenderer_->SetRenderSize(float4(1.f, 17.f));

				// 게임컨트롤 호출해서 HPBar 정렬



				DecreaseHPBar_ = false;
				return;
			}

			CurHPBarLen_ = PrevHPBarLen_;
			DecreaseHPBar_ = false;

			return;
		}

		// 체력바 크기는 100 x 17
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
	// 1.f 이하이면 플레이어 사망으로 처리
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
	// 현재 생성된 하단바의 주인이 누구인지 저장
	WormIndex_ = _WormIndex;

	// 렌더러를 셋팅한다.
	SettingRenderer();

	// 렌더러의 위치를 셋팅한다.
	SettingRendererPos();
}

void BottomStateUI::SettingRenderer()
{
	// 국기 렌더러 세팅
	SetFlag();

	// 플레이어 이름 렌더러 세팅
	SetPlayerName();

	// 플레이어 Total HP Bar 렌더러 세팅
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
	// 현재 선택된 플레이어 이름으로 플레이어 명을 알아낸다.
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
	// 국기 렌더러 위치 세팅
	SetFlagPos();

	// 플레이어 이름 렌더러 위치 세팅
	SetNamePos();

	// 플레이어 Total HPBar 위치 세팅
	SetHPBarPos();
}

void BottomStateUI::SetFlagPos()
{
	int MaxWormCnt = GameOptionInfo::CurWormCnt;
	if (0 != MaxWormCnt)
	{
		// 현재 생성된 플레이어의 갯수를 이용하여 시작위치를 설정한다.
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
		
		// Worm Index를 이용하여 시작 위치부터의 자신의 위치를 계산한다.
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
		// 현재 생성된 플레이어의 갯수를 이용하여 시작위치를 설정한다.
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

		// Worm Index를 이용하여 시작 위치부터의 자신의 위치를 계산한다.
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
		// 현재 생성된 플레이어의 갯수를 이용하여 시작위치를 설정한다.
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

		// Worm Index를 이용하여 시작 위치부터의 자신의 위치를 계산한다.
		RenderPos_.y += static_cast<float>(WormIndex_ * 20);
		HPBarRenderer_->SetPivotPos(RenderPos_);
		HPBarRenderer_->SetCameraEffectOff();
	}
}

void BottomStateUI::DecreaseHPBar()
{
	// 해당 플레이어의 체력을 기준으로 감소 목표치 계산 및 Flag On
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

	// 데미지 계산이 완료되었으므로 현재체력을 이전체력에 저장
	PrevHP_ = CurHP_;
}
