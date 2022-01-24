#include "ChattingInput.h"
#include "eCollisionGroup.h"
#include "ChattingHistory.h"

#include <EngineEnum.h>
#include <KeyboardClass.h>
#include <GameEngineInput.h>
#include <GameEngineImage.h>
#include <GameEngineImageFile.h>
#include <GameEngineWindow.h>
#include <GameEngineRenderer.h>
#include <GameEngineCollision.h>

ChattingInput::ChattingInput() :
	ChattingInputOK_(false),
	chattingInputBoxSpriteRender_(nullptr),
	chattinInputBoxCollision_(nullptr)
{
	SetRenderOrder(static_cast<int>(RenderOrder::UI));
}

ChattingInput::~ChattingInput()
{

}

ChattingInput::ChattingInput(ChattingInput&& _other) noexcept :
	ChattingInputOK_(_other.ChattingInputOK_),
	chattingInputBoxSpriteRender_(_other.chattingInputBoxSpriteRender_),
	chattinInputBoxCollision_(_other.chattinInputBoxCollision_)
{

}

void ChattingInput::Start()
{
	float4 ImageHarfSize = float4::ZERO;

	// Chatting Box
	chattingInputBoxSpriteRender_ = CreateRenderer("Lobby_ChattingInput");
	ImageHarfSize = chattingInputBoxSpriteRender_->GetImageSize().halffloat4();
	chattingInputBoxSpriteRender_->SetPivotPos(float4(ImageHarfSize.x + 10.f, ImageHarfSize.y + 650.f));
	chattingInputBoxSpriteRender_->SetRenderSize(float4(1000.f, 32.f));
	chattingInputBoxSpriteRender_->SetCameraEffectOff();

	// �浹ü ����
	chattinInputBoxCollision_ = CreateCollision(static_cast<int>(eCollisionGroup::UI), CollisionCheckType::RECT);
	chattinInputBoxCollision_->SetSize(float4(1000.f, 32.f));
	chattinInputBoxCollision_->SetPivot(float4(500.f + 10.f, 16.f + 650.f));

	// Ű���
	if (false == GameEngineInput::GetInst().IsKey("Chatting_InputOK"))
	{
		GameEngineInput::GetInst().CreateKey("Chatting_InputOK", VK_LBUTTON);
	}

	if (false == GameEngineInput::GetInst().IsKey("Chatting_End"))
	{
		GameEngineInput::GetInst().CreateKey("Chatting_End", VK_RETURN);
	}

	if (false == GameEngineInput::GetInst().IsKey("Chatting_Del"))
	{
		GameEngineInput::GetInst().CreateKey("Chatting_Del", VK_BACK);
	}
}

void ChattingInput::UpdateBefore()
{
	// ���콺�� ä�� �Է�â �浹
	// ChattingInputOK_ On
	GameEngineCollision* ColUI = chattinInputBoxCollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MOUSE));
	if (nullptr != ColUI)
	{
		if (true == GameEngineInput::GetInst().IsDown("Chatting_InputOK"))
		{
			if (false == ChattingInputOK_)
			{
				// Input On
				ChattingInputOK_ = true;

				// Ŀ�� ����
				
			}
		}
	}

}

void ChattingInput::Update()
{
	// Ű���� Ű�Է� üũ �� ���ڿ� ����
	if (true == ChattingInputOK_)
	{
		while (!KeyboardClass::GetInst().CharBufferIsEmpty())
		{
			std::string SetStr = "";
			unsigned char ReadChar = KeyboardClass::GetInst().ReadChar();
			SetStr += ReadChar;

			AddText(SetStr);
		}
	}
	else // ���� �Է»��°� �ƴѿ��߿��� Ű���� �Է��� �ִٸ� charbuffer�� Ŭ�����Ѵ�.
	{
		KeyboardClass::GetInst().DeleteCharBuffer();
	}

	// �Է����� ä�� ���ڿ��� ä�� �̷����� ������(ä���Է¿Ϸ�)
	if (true == GameEngineInput::GetInst().IsDown("Chatting_End"))
	{
		// ���� �Էµ� ���ڿ��� ChattingHistory�� �Ѱ��ش�.
		ChattingHistory::ChattingHistoryAdd(InputText_);

		// ��� ���ڿ��� �Ѱ�ٸ� ���� �Է� ���ڿ��� Ŭ�����Ѵ�.
		if (!InputText_.empty())
		{
			InputText_.clear();
		}
	}

	// �Է����� ä�� ���ڿ� ���������� ����
	if (true == GameEngineInput::GetInst().IsDown("Chatting_Del"))
	{
		if (!InputText_.empty())
		{
			InputText_.pop_back();
		}
	}
}

void ChattingInput::UpdateAfter()
{
	
}

void ChattingInput::Render()
{
	// Chatting
	chattingInputBoxSpriteRender_->Render();

	if (!InputText_.empty())
	{
		TextOut(GameEngineImage::GetInst().GetBackBufferImage()->GetDC(), 20, 660, InputText_.c_str(), lstrlen(InputText_.c_str()));
	}
}

void ChattingInput::AddText(const std::string& _Text)
{
	// ä�� �ִ���ڼ� �Ѿ�� �ԷºҰ�
	std::string CurText = InputText_;
	CurText += _Text;
	if (MAX_INPUTCOUNT <= lstrlen(CurText.c_str()))
	{
		// �ԷºҰ�
		return;
	}

	InputText_ += _Text;
}

