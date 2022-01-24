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

	// 충돌체 생성
	chattinInputBoxCollision_ = CreateCollision(static_cast<int>(eCollisionGroup::UI), CollisionCheckType::RECT);
	chattinInputBoxCollision_->SetSize(float4(1000.f, 32.f));
	chattinInputBoxCollision_->SetPivot(float4(500.f + 10.f, 16.f + 650.f));

	// 키등록
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
	// 마우스와 채팅 입력창 충돌
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

				// 커서 생성
				
			}
		}
	}

}

void ChattingInput::Update()
{
	// 키보드 키입력 체크 및 문자열 편집
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
	else // 현재 입력상태가 아닌와중에도 키보드 입력이 있다면 charbuffer를 클리어한다.
	{
		KeyboardClass::GetInst().DeleteCharBuffer();
	}

	// 입력중인 채팅 문자열을 채팅 이력으로 보내기(채팅입력완료)
	if (true == GameEngineInput::GetInst().IsDown("Chatting_End"))
	{
		// 현재 입력된 문자열을 ChattingHistory로 넘겨준다.
		ChattingHistory::ChattingHistoryAdd(InputText_);

		// 모든 문자열을 넘겼다면 현재 입력 문자열을 클리어한다.
		if (!InputText_.empty())
		{
			InputText_.clear();
		}
	}

	// 입력중인 채팅 문자열 마지막부터 삭제
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
	// 채팅 최대글자수 넘어가면 입력불가
	std::string CurText = InputText_;
	CurText += _Text;
	if (MAX_INPUTCOUNT <= lstrlen(CurText.c_str()))
	{
		// 입력불가
		return;
	}

	InputText_ += _Text;
}

