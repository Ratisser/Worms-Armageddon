#include "TopHPText.h"
#include "GameOptionInfo.h"

#include "Worm.h"
#include "UIController.h"
#include "WormTopStateUI.h"

#include <EngineEnum.h>
#include <GameEngineRenderer.h>

TopHPText::TopHPText() :
	ParentHPBoxUI_(nullptr),
	WormIndex_(-1),
	PlayerColorIndex_(-1),
	PrevHP_(0),
	CurHP_(0),
	HPUpdateStart_(false),
	HPUpdateEnd_(false),
	UpdateHundredNum(0),
	UpdateTenNum(0),
	UpdateNum(0),
	HundredFlag_(false),
	TenFlag_(false),
	NumFlag_(false),
	HPHundredNumRenderer_(nullptr),
	HPTenNumRenderer_(nullptr),
	HPNumRenderer_(nullptr)
{
	SetRenderOrder(static_cast<int>(RenderOrder::UI1));
}

TopHPText::~TopHPText()
{
}

void TopHPText::Start()
{
}

void TopHPText::UpdateBefore()
{
	//UpdateHPText();
}

void TopHPText::Update()
{
	// 
	if (true == HundredFlag_ && true == TenFlag_ && true == NumFlag_)
	{
		if (nullptr != HPHundredNumRenderer_ && nullptr != HPTenNumRenderer_ && nullptr != HPNumRenderer_)
		{
			HPHundredNumRenderer_->SetPivotPos(float4(ParentHPBoxUI_->GetParentWorm()->GetPos().x - 10.f, ParentHPBoxUI_->GetParentWorm()->GetPos().y - 31.f));
			HPTenNumRenderer_->SetPivotPos(float4(ParentHPBoxUI_->GetParentWorm()->GetPos().x, ParentHPBoxUI_->GetParentWorm()->GetPos().y - 31.f));
			HPNumRenderer_->SetPivotPos(float4(ParentHPBoxUI_->GetParentWorm()->GetPos().x + 10.f, ParentHPBoxUI_->GetParentWorm()->GetPos().y - 31.f));
		}
	}

	// 
	if (false == HundredFlag_ && true == TenFlag_ && true == NumFlag_)
	{
		if (nullptr != HPTenNumRenderer_ && nullptr != HPNumRenderer_)
		{
			HPTenNumRenderer_->SetPivotPos(float4(ParentHPBoxUI_->GetParentWorm()->GetPos().x - 5.f, ParentHPBoxUI_->GetParentWorm()->GetPos().y - 31.f));
			HPNumRenderer_->SetPivotPos(float4(ParentHPBoxUI_->GetParentWorm()->GetPos().x + 5.0f, ParentHPBoxUI_->GetParentWorm()->GetPos().y - 31.f));
		}
	}

	// 
	if (false == HundredFlag_ && false == TenFlag_ && true == NumFlag_)
	{
		if (nullptr != HPNumRenderer_)
		{
			HPNumRenderer_->SetPivotPos(float4(ParentHPBoxUI_->GetParentWorm()->GetPos().x, ParentHPBoxUI_->GetParentWorm()->GetPos().y - 31.f));
		}
	}
}

void TopHPText::UpdateAfter()
{
}

void TopHPText::Render()
{
	if (true == HundredFlag_)
	{
		if (nullptr != HPHundredNumRenderer_)
		{
			HPHundredNumRenderer_->AnimationUpdate();
		}
	}

	if (true == TenFlag_)
	{
		if (nullptr != HPTenNumRenderer_)
		{
			HPTenNumRenderer_->AnimationUpdate();
		}
	}

	if (true == NumFlag_)
	{
		if (nullptr != HPNumRenderer_)
		{
			HPNumRenderer_->AnimationUpdate();
		}
	}
}

void TopHPText::CreateHPText(WormTopStateUI* _Parent, int _WormIndex)
{
	// 부모와 링크
	ParentHPBoxUI_ = _Parent;
	if (nullptr != ParentHPBoxUI_)
	{
		WormIndex_ = ParentHPBoxUI_->GetWormIndex();
		PlayerColorIndex_ = ParentHPBoxUI_->GetPlayerColorIndex();
	}

	// Text의 Color를 셋팅한다.
	SetTextColor();

	// 생성시 플레이어의 체력을 셋팅한다.
	HPTextInit();
}

void TopHPText::SetTextColor()
{
	std::string AnimationName = "TimerNum";
	int ImageIndex = 0;

	std::string CurPlayerName = GameOptionInfo::CurPlayerName[WormIndex_];
	char PlayerIndex = CurPlayerName[0];
	int PlayerNumber = (static_cast<int>(PlayerIndex) - '0');
	PlayerNumber -= 1;
	PlayerColorIndex_ = PlayerNumber;
	switch (PlayerColorIndex_)
	{
		case 0:
		{
			HPHundredNumRenderer_ = CreateRenderer("HPnumber");
			HPTenNumRenderer_ = CreateRenderer("HPnumber");
			HPNumRenderer_ = CreateRenderer("HPnumber");
			for (int i = 0; i < 10; ++i)
			{
				ImageIndex = i + 20;

				std::string AnimationIndex = std::to_string(i);
				HPHundredNumRenderer_->CreateAnimation(AnimationIndex, AnimationName, ImageIndex, ImageIndex, false, 1.f);
				HPTenNumRenderer_->CreateAnimation(AnimationIndex, AnimationName, ImageIndex, ImageIndex, false, 1.f);
				HPNumRenderer_->CreateAnimation(AnimationIndex, AnimationName, ImageIndex, ImageIndex, false, 1.f);
			}
			HPHundredNumRenderer_->ChangeAnimation("0");
			HPTenNumRenderer_->ChangeAnimation("0");
			HPNumRenderer_->ChangeAnimation("0");

			break;
		}
		case 1:
		{
			HPHundredNumRenderer_ = CreateRenderer("HPnumber");
			HPTenNumRenderer_ = CreateRenderer("HPnumber");
			HPNumRenderer_ = CreateRenderer("HPnumber");
			for (int i = 0; i < 10; ++i)
			{
				ImageIndex = i + 30;

				std::string AnimationIndex = std::to_string(i);
				HPHundredNumRenderer_->CreateAnimation(AnimationIndex, AnimationName, ImageIndex, ImageIndex, false, 1.f);
				HPTenNumRenderer_->CreateAnimation(AnimationIndex, AnimationName, ImageIndex, ImageIndex, false, 1.f);
				HPNumRenderer_->CreateAnimation(AnimationIndex, AnimationName, ImageIndex, ImageIndex, false, 1.f);
			}
			HPHundredNumRenderer_->ChangeAnimation("0");
			HPTenNumRenderer_->ChangeAnimation("0");
			HPNumRenderer_->ChangeAnimation("0");

			break;
		}
		case 2:
		{
			HPHundredNumRenderer_ = CreateRenderer("HPnumber");
			HPTenNumRenderer_ = CreateRenderer("HPnumber");
			HPNumRenderer_ = CreateRenderer("HPnumber");
			for (int i = 0; i < 10; ++i)
			{
				ImageIndex = i + 40;

				std::string AnimationIndex = std::to_string(i);
				HPHundredNumRenderer_->CreateAnimation(AnimationIndex, AnimationName, ImageIndex, ImageIndex, false, 1.f);
				HPTenNumRenderer_->CreateAnimation(AnimationIndex, AnimationName, ImageIndex, ImageIndex, false, 1.f);
				HPNumRenderer_->CreateAnimation(AnimationIndex, AnimationName, ImageIndex, ImageIndex, false, 1.f);
			}
			HPHundredNumRenderer_->ChangeAnimation("0");
			HPTenNumRenderer_->ChangeAnimation("0");
			HPNumRenderer_->ChangeAnimation("0");

			break;
		}
		case 3:
		{
			HPHundredNumRenderer_ = CreateRenderer("HPnumber");
			HPTenNumRenderer_ = CreateRenderer("HPnumber");
			HPNumRenderer_ = CreateRenderer("HPnumber");
			for (int i = 0; i < 10; ++i)
			{
				ImageIndex = i + 50;

				std::string AnimationIndex = std::to_string(i);
				HPHundredNumRenderer_->CreateAnimation(AnimationIndex, AnimationName, ImageIndex, ImageIndex, false, 1.f);
				HPTenNumRenderer_->CreateAnimation(AnimationIndex, AnimationName, ImageIndex, ImageIndex, false, 1.f);
				HPNumRenderer_->CreateAnimation(AnimationIndex, AnimationName, ImageIndex, ImageIndex, false, 1.f);
			}
			HPHundredNumRenderer_->ChangeAnimation("0");
			HPTenNumRenderer_->ChangeAnimation("0");
			HPNumRenderer_->ChangeAnimation("0");

			break;
		}
		case 4:
		{
			HPHundredNumRenderer_ = CreateRenderer("HPnumber");
			HPTenNumRenderer_ = CreateRenderer("HPnumber");
			HPNumRenderer_ = CreateRenderer("HPnumber");
			for (int i = 0; i < 10; ++i)
			{
				ImageIndex = i + 70;

				std::string AnimationIndex = std::to_string(i);
				HPHundredNumRenderer_->CreateAnimation(AnimationIndex, AnimationName, ImageIndex, ImageIndex, false, 1.f);
				HPTenNumRenderer_->CreateAnimation(AnimationIndex, AnimationName, ImageIndex, ImageIndex, false, 1.f);
				HPNumRenderer_->CreateAnimation(AnimationIndex, AnimationName, ImageIndex, ImageIndex, false, 1.f);
			}
			HPHundredNumRenderer_->ChangeAnimation("0");
			HPTenNumRenderer_->ChangeAnimation("0");
			HPNumRenderer_->ChangeAnimation("0");

			break;
		}
		case 5:
		{
			HPHundredNumRenderer_ = CreateRenderer("HPnumber");
			HPTenNumRenderer_ = CreateRenderer("HPnumber");
			HPNumRenderer_ = CreateRenderer("HPnumber");
			for (int i = 0; i < 10; ++i)
			{
				ImageIndex = i + 60;

				std::string AnimationIndex = std::to_string(i);
				HPHundredNumRenderer_->CreateAnimation(AnimationIndex, AnimationName, ImageIndex, ImageIndex, false, 1.f);
				HPTenNumRenderer_->CreateAnimation(AnimationIndex, AnimationName, ImageIndex, ImageIndex, false, 1.f);
				HPNumRenderer_->CreateAnimation(AnimationIndex, AnimationName, ImageIndex, ImageIndex, false, 1.f);
			}
			HPHundredNumRenderer_->ChangeAnimation("0");
			HPTenNumRenderer_->ChangeAnimation("0");
			HPNumRenderer_->ChangeAnimation("0");

			break;
		}
		default:
		{
			HPHundredNumRenderer_ = CreateRenderer("HPnumber");
			HPTenNumRenderer_ = CreateRenderer("HPnumber");
			HPNumRenderer_ = CreateRenderer("HPnumber");
			for (int i = 0; i < 10; ++i)
			{
				ImageIndex = i + 20;

				std::string AnimationIndex = std::to_string(i);
				HPHundredNumRenderer_->CreateAnimation(AnimationIndex, AnimationName, ImageIndex, ImageIndex, false, 1.f);
				HPTenNumRenderer_->CreateAnimation(AnimationIndex, AnimationName, ImageIndex, ImageIndex, false, 1.f);
				HPNumRenderer_->CreateAnimation(AnimationIndex, AnimationName, ImageIndex, ImageIndex, false, 1.f);
			}
			HPHundredNumRenderer_->ChangeAnimation("0");
			HPTenNumRenderer_->ChangeAnimation("0");
			HPNumRenderer_->ChangeAnimation("0");

			break;
		}
	}
}

void TopHPText::HPTextInit()
{
	int InitHP = GameOptionInfo::WormEnergy;
	if (0 != InitHP)
	{
		// 각 자릿수의 Number를 찾아낸다.
		int HundredNum = 0;
		int TenNum = 0;
		int Num = 0;
		if (0 != (InitHP /100))
		{
			HundredFlag_ = true;

			HundredNum = InitHP / 100;
			HPHundredNumRenderer_->ChangeAnimation(std::to_string(HundredNum));
		}

		if (0 != (InitHP / 10))
		{
			TenFlag_ = true;

			TenNum = InitHP / 10;
			TenNum = TenNum % 10;
			HPTenNumRenderer_->ChangeAnimation(std::to_string(TenNum));
		}

		if (0 != (InitHP / 1))
		{
			NumFlag_ = true;

			Num = InitHP % 10;
			HPNumRenderer_->ChangeAnimation(std::to_string(Num));
		}

		PrevHP_ = CurHP_ = InitHP;
	}
}

void TopHPText::UpdateHPText()
{
	Worm* CurWorm = ParentHPBoxUI_->GetParentWorm();
	if (nullptr != CurWorm)
	{
		// 플레이어가 사망하지않았고 이전 체력과 달라진 경우 갱신
		CurHP_ = CurWorm->GetCurHP();
		if (PrevHP_ != CurHP_)
		{
			// 현재체력으로 각 자리의 목표값을 얻어낸다.
			UpdateHundredNum = 100;
			UpdateTenNum = 100;
			UpdateNum = 100;

			HPUpdateStart_ = true;
		}

		if (true == HPUpdateStart_)
		{
			



			// 갱신 종료이 종료되면 Flag 해제
			if (true == HPUpdateEnd_)
			{
				HPUpdateStart_ = false;
				HPUpdateEnd_ = false;
			}
		}

		//// 이전체력 - 현재체력 = 받은데미지
		//int Damage = PrevHP_ - CurHP_;
		//if (0 >= CurHP_) // 플레이어 사망으로 판단
		//{
		//	// 부모인 WormTopSate를 죽이고
		//	//ParentHPBoxUI_->Death();

		//	// 나 자신을 죽임
		//	//Death();

		//	return;
		//}
		//else
		//{
		//	// 일의자리씩 체력 감소 갱신 On
		//	if (true == HPUpdate_)
		//	{




		//		int a = 0;
		//	}
		//}

		if (true == HPUpdateStart_)
		{
			// 각 자릿수의 Number를 찾아낸다.
			int HundredNum = 0;
			int TenNum = 0;
			int Num = 0;

			if (true == HundredFlag_)
			{
				HundredNum = CurHP_ / 100;
				if (0 >= HundredNum)
				{
					HundredFlag_ = false;
				}
				else
				{
					HundredNum = CurHP_ / 100;
					HPHundredNumRenderer_->ChangeAnimation(std::to_string(HundredNum));
				}
			}

			if (true == TenFlag_)
			{
				TenNum = CurHP_ / 10;
				TenNum = TenNum % 10;
				// 만약 0이 나왔을때 백의자리가 있다면 Flag True
				if (true == HundredFlag_)
				{
					HPTenNumRenderer_->ChangeAnimation(std::to_string(TenNum));
				}
				else
				{
					TenFlag_ = false;
				}
			}

			if (0 != (CurHP_ / 1))
			{
				NumFlag_ = true;

				Num = CurHP_ % 10;
				HPNumRenderer_->ChangeAnimation(std::to_string(Num));
			}

			PrevHP_ = CurHP_;
		}
	}
}

void TopHPText::UpdateHP()
{
	// 현재 플레이어의 체력을 갱신시키고, PrevHP 값을 얻어오지만,
// 시각적으로 표시화하는 함수는 아닙니다.

	Worm* CurWorm = ParentHPBoxUI_->GetParentWorm();
	if (nullptr != CurWorm)
	{
		// 플레이어가 사망하지않았고 이전 체력과 달라진 경우 갱신
		CurHP_ = CurWorm->GetCurHP();
		if (PrevHP_ != CurHP_)
		{
			// 현재체력으로 각 자리의 목표값을 얻어낸다.
			UpdateHundredNum = 100;
			UpdateTenNum = 100;
			UpdateNum = 100;

			HPUpdateStart_ = true;
		}

		if (true == HPUpdateStart_)
		{




			// 갱신 종료이 종료되면 Flag 해제
			if (true == HPUpdateEnd_)
			{
				HPUpdateStart_ = false;
				HPUpdateEnd_ = false;
			}
		}

		if (true == HPUpdateStart_)
		{
			// 각 자릿수의 Number를 찾아낸다.
			int HundredNum = 0;
			int TenNum = 0;
			int Num = 0;

			if (true == HundredFlag_)
			{
				HundredNum = CurHP_ / 100;
				if (0 >= HundredNum)
				{
					HundredFlag_ = false;
				}
				else
				{
					HundredNum = CurHP_ / 100;
					//HPHundredNumRenderer_->ChangeAnimation(std::to_string(HundredNum));
				}
			}

			if (true == TenFlag_)
			{
				TenNum = CurHP_ / 10;
				TenNum = TenNum % 10;
				// 만약 0이 나왔을때 백의자리가 있다면 Flag True
				if (true == HundredFlag_)
				{
					//HPTenNumRenderer_->ChangeAnimation(std::to_string(TenNum));
				}
				else
				{
					TenFlag_ = false;
				}
			}

			if (0 != (CurHP_ / 1))
			{
				NumFlag_ = true;

				Num = CurHP_ % 10;
				//HPNumRenderer_->ChangeAnimation(std::to_string(Num));
			}

			PrevHP_ = CurHP_;
		}
	}
}


void TopHPText::ChangeHPText()
{
	// 현재 플레이어의 체력을 갱신
	Worm* CurWorm = ParentHPBoxUI_->GetParentWorm();
	if (nullptr != CurWorm)
	{
		// 플레이어가 사망하지않았고 이전 체력과 달라진 경우 갱신
		CurHP_ = CurWorm->GetCurHP();

		if (PrevHP_ == CurHP_)
		{
			isChangingDone_ = true;
			return;
		}

		if (PrevHP_ > CurHP_)
		{
			
			deltaTime_ += GameEngineTime::GetInst().GetDeltaTime();
			HPHundredNumRenderer_->ChangeAnimation(std::to_string(PrevHP_ /100));
			HPTenNumRenderer_->ChangeAnimation(std::to_string(PrevHP_ / 10));
			HPNumRenderer_->ChangeAnimation(std::to_string(PrevHP_ % 10));

			PrevHP_--;

			if (deltaTime_ >= NUMBER_CHANGE_TIME)
			{
				deltaTime_ = 0.0f;
				isChangingDone_ = true;
				return;
			}
		}
	}
}