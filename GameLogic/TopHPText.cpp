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
	// �θ�� ��ũ
	ParentHPBoxUI_ = _Parent;
	if (nullptr != ParentHPBoxUI_)
	{
		WormIndex_ = ParentHPBoxUI_->GetWormIndex();
		PlayerColorIndex_ = ParentHPBoxUI_->GetPlayerColorIndex();
	}

	// Text�� Color�� �����Ѵ�.
	SetTextColor();

	// ������ �÷��̾��� ü���� �����Ѵ�.
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
		// �� �ڸ����� Number�� ã�Ƴ���.
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
		// �÷��̾ ��������ʾҰ� ���� ü�°� �޶��� ��� ����
		CurHP_ = CurWorm->GetCurHP();
		if (PrevHP_ != CurHP_)
		{
			// ����ü������ �� �ڸ��� ��ǥ���� ����.
			UpdateHundredNum = 100;
			UpdateTenNum = 100;
			UpdateNum = 100;

			HPUpdateStart_ = true;
		}

		if (true == HPUpdateStart_)
		{
			



			// ���� ������ ����Ǹ� Flag ����
			if (true == HPUpdateEnd_)
			{
				HPUpdateStart_ = false;
				HPUpdateEnd_ = false;
			}
		}

		//// ����ü�� - ����ü�� = ����������
		//int Damage = PrevHP_ - CurHP_;
		//if (0 >= CurHP_) // �÷��̾� ������� �Ǵ�
		//{
		//	// �θ��� WormTopSate�� ���̰�
		//	//ParentHPBoxUI_->Death();

		//	// �� �ڽ��� ����
		//	//Death();

		//	return;
		//}
		//else
		//{
		//	// �����ڸ��� ü�� ���� ���� On
		//	if (true == HPUpdate_)
		//	{




		//		int a = 0;
		//	}
		//}

		if (true == HPUpdateStart_)
		{
			// �� �ڸ����� Number�� ã�Ƴ���.
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
				// ���� 0�� �������� �����ڸ��� �ִٸ� Flag True
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
	// ���� �÷��̾��� ü���� ���Ž�Ű��, PrevHP ���� ��������,
// �ð������� ǥ��ȭ�ϴ� �Լ��� �ƴմϴ�.

	Worm* CurWorm = ParentHPBoxUI_->GetParentWorm();
	if (nullptr != CurWorm)
	{
		// �÷��̾ ��������ʾҰ� ���� ü�°� �޶��� ��� ����
		CurHP_ = CurWorm->GetCurHP();
		if (PrevHP_ != CurHP_)
		{
			// ����ü������ �� �ڸ��� ��ǥ���� ����.
			UpdateHundredNum = 100;
			UpdateTenNum = 100;
			UpdateNum = 100;

			HPUpdateStart_ = true;
		}

		if (true == HPUpdateStart_)
		{




			// ���� ������ ����Ǹ� Flag ����
			if (true == HPUpdateEnd_)
			{
				HPUpdateStart_ = false;
				HPUpdateEnd_ = false;
			}
		}

		if (true == HPUpdateStart_)
		{
			// �� �ڸ����� Number�� ã�Ƴ���.
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
				// ���� 0�� �������� �����ڸ��� �ִٸ� Flag True
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
	// ���� �÷��̾��� ü���� ����
	Worm* CurWorm = ParentHPBoxUI_->GetParentWorm();
	if (nullptr != CurWorm)
	{
		// �÷��̾ ��������ʾҰ� ���� ü�°� �޶��� ��� ����
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