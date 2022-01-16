#include "GameEngineRenderer.h"
#include <GameEngineDebug.h>
#include <GameEngineTime.h>
#include "GameEngineImage.h"
#include "GameEngineImageFile.h"
#include "GameEngineActor.h"

GameEngineRenderer::FrameAnimation::FrameAnimation()
	: start_(-1),
	end_(-1),
	cur_(-1),
	curframeTime_(0.0f),
	renderer_(nullptr),
	pivot_(RENDERPIVOT::BOT),
	loop_(nullptr),
	image_(nullptr)
{

}

GameEngineRenderer::FrameAnimation::~FrameAnimation()
{
	auto iterfirst = FrameFunctionList_.begin();
	auto iterEnd = FrameFunctionList_.end();
	for (; iterfirst != iterEnd; ++iterfirst)
	{
		delete *iterfirst;
	}
}

void GameEngineRenderer::FrameAnimation::Update()
{
	isend_ = false;
	curframeTime_ -= GameEngineTime::GetInst().GetDeltaTime();
	if (0.0f >= curframeTime_)
	{
		//                        10 ~ 20
		//                        0  ~ 10


		++cur_;
		// 프레임이 증가했다.
		// 애니메이션의 끝을 넘겼어.


		//에니메이션 프레임당 할당된 호출 함수가 있나 검사 및 실행;
		auto iter1 = FrameFunctionList_.begin();
		auto iter2 = FrameFunctionList_.end();
		for (; iter1 != iter2; ++iter1)
		{
			if ((*iter1)->Frame_ == cur_)
			{
				(*iter1)->FrameFunction_();
			}
		}
		//


		if (end_ < cur_)
		{
			if (nullptr != EndFunction_)
			{
				EndFunction_(); // 에니메이션 종료시 호출 함수;
			}

			isend_ = true;
			// 루프가 true면
			if (true == loop_)
			{
				// 처음으로 돌아간다.
				cur_ = start_;
			}
			else
			{
				--cur_;
			}
		}

		curframeTime_ = frameTime_[cur_ - start_];
	}

	renderer_->SetCutIndex(cur_, pivot_);
	renderer_->Render();
}


// Static Var
// Static Func

// constructer destructer
GameEngineRenderer::GameEngineRenderer()
	: imagePivot_(float4::ZERO),
	pivotpos_(float4::ZERO),
	rendersize_(float4::ZERO),
	imagepos_(float4::ZERO),
	imagesize_(float4::ZERO),
	isCamEffect_(true),
	rotate_(0.0f),
	alpha_(255)
{
}

GameEngineRenderer::~GameEngineRenderer()
{
	std::map<std::string, FrameAnimation*>::iterator AniStart = allAnimation_.begin();
	std::map<std::string, FrameAnimation*>::iterator AniEnd = allAnimation_.end();

	for (; AniStart != AniEnd; ++AniStart)
	{
		if (nullptr == AniStart->second)
		{
			continue;
		}

		// 에니메이션 프레임 호출 함수 소멸 : 이현
		//int size = AniStart->second->vecNotify_.size();

		//for (int i = 0; i < size; ++i)
		//{
		//	delete AniStart->second->vecNotify_[i];
		//	AniStart->second->vecNotify_[i] = nullptr;

		//}
		//

		delete AniStart->second;
		AniStart->second = nullptr;
	}



	allAnimation_.clear();
}

GameEngineRenderer::GameEngineRenderer(GameEngineRenderer&& _other) noexcept
{

}

//member Func

void GameEngineRenderer::SetImage(const std::string& _Name)
{
	image_ = GameEngineImage::GetInst().FindGameImage(_Name);

	if (nullptr == image_)
	{
		GameEngineDebug::AssertFalse();
	}

	imagepos_ = float4::ZERO;
	imagesize_ = image_->GetSize();
	rendersize_ = image_->GetSize();
	imagePivot_ = rendersize_.halffloat4();
}

void GameEngineRenderer::SetImageNoSize(const std::string& _name)
{
	image_ = GameEngineImage::GetInst().FindGameImage(_name);

	if (nullptr == image_)
	{
		GameEngineDebug::AssertFalse();
	}
}

void GameEngineRenderer::SetMaskImage(const std::string& _Name) 
{
	maskimage_ = GameEngineImage::GetInst().FindGameImage(_Name);

	if (nullptr == maskimage_)
	{
		GameEngineDebug::AssertFalse();
	}
}


void GameEngineRenderer::Render()
{
	GameEngineImageFile* WindowImage = GameEngineImage::GetInst().GetBackBufferImage();

	float4 ActorPos = actor_->GetCamEffectPos();

	if (false == isCamEffect_)
	{
		ActorPos = actor_->GetPos();
	}

	float4 RenderPos = ActorPos + pivotpos_ - imagePivot_;

	if (0.0f == rotate_)
	{

		if (alpha_ == 255)
		{
			WindowImage->TransCopy(image_,
				RenderPos,
				rendersize_,
				imagepos_,
				imagesize_,
				RGB(255, 0, 255));
		}
		else 
		{
			WindowImage->AlphaCopy(image_, 
				alpha_,
				RenderPos,
				rendersize_,
				imagepos_,
				imagesize_);
		}

	}
	else 
	{
		WindowImage->PlgCopy(image_,
			maskimage_,
			rotate_,
			RenderPos,
			rendersize_,
			imagepos_,
			imagesize_);
	}
}


void GameEngineRenderer::SetCutIndex(size_t _Index, RENDERPIVOT _Pivot)
{
	if (false == image_->IsCut())
	{
		GameEngineDebug::AssertFalse();
		return;
	}

	imagepos_ = image_->GetCutPos(_Index);
	imagesize_ = image_->GetCutSize(_Index);
	rendersize_ = imagesize_;

	// w
	imagePivot_ = rendersize_.halffloat4();

	switch (_Pivot)
	{
	case RENDERPIVOT::LEFTTOP:
		imagePivot_ = float4::ZERO;
		break;
	case RENDERPIVOT::CENTER:
		imagePivot_ = rendersize_.halffloat4();
		break;
	case RENDERPIVOT::BOT:
		imagePivot_ = rendersize_.halffloat4();
		imagePivot_.y += rendersize_.halffloat4().y;
		break;
	default:
		GameEngineDebug::AssertFalse();
		break;
	}

}

GameEngineRenderer::FrameAnimation* GameEngineRenderer::FindAnimation(const std::string& _name)
{
	std::map<std::string, FrameAnimation*>::iterator FindAniIter = allAnimation_.find(_name);

	if (FindAniIter == allAnimation_.end())
	{
		return nullptr;
	}

	return FindAniIter->second;
}

void GameEngineRenderer::ChangeAnimation(const std::string& _Name, bool _forceChange /*= false*/)
{
	// 기존 애니메이션도 진행하고 있고
	if (nullptr != curani_ &&
		// 강제바꾸기가 아니고
		false == _forceChange &&
		// 애니메이션 이름이 같으면
		curani_->GetName() == _Name)
	{
		return;
	}

	curani_ = FindAnimation(_Name);
	curani_->Reset();

	if (nullptr == curani_)
	{
		GameEngineDebug::AssertFalse();
		return;
	}
}

void GameEngineRenderer::ChangeAnimation(const std::string& _Name, const std::string& _name, bool _forceChange)
{
	// 기존 애니메이션도 진행하고 있고
	if (nullptr != curani_ &&
		// 강제바꾸기가 아니고
		false == _forceChange &&
		// 애니메이션 이름이 같으면
		curani_->GetName() == _Name)
	{
		return;
	}

	SetImageNoSize(_name);
	curani_ = FindAnimation(_Name);
	curani_->Reset();

	if (nullptr == curani_)
	{
		GameEngineDebug::AssertFalse();
		return;
	}
}

void GameEngineRenderer::CreateAnimation(
	const std::string& _Name, // idle,
	const std::string& _ImageName, // ,
	int _Start,
	int _End,
	bool _Loop /*= true*/,
	float _FrameTime /*= 0.1f*/,
	RENDERPIVOT pivot_ /*= RENDERPIVOT::CENTER*/
)
{
	if (nullptr != FindAnimation(_Name))
	{
		GameEngineDebug::AssertFalse();
		return;
	}

	GameEngineImageFile* ImagePtr = GameEngineImage::GetInst().FindGameImage(_ImageName);

	if (nullptr == ImagePtr)
	{
		GameEngineDebug::AssertFalse();
		return;
	}

	if (false == ImagePtr->IsCut())
	{
		GameEngineDebug::AssertFalse();
		return;
	}

	FrameAnimation* NewAnimation = new FrameAnimation();

	NewAnimation->SetName(_Name);
	NewAnimation->start_ = _Start;
	NewAnimation->end_ = _End;

	NewAnimation->frameTime_.reserve(NewAnimation->end_ - NewAnimation->start_);
	for (size_t i = 0; i < (NewAnimation->end_ - NewAnimation->start_) + 1; i++)
	{
		NewAnimation->frameTime_.push_back(_FrameTime);
	}
	// NewAnimation->frameTime_ = _FrameTime;
	NewAnimation->image_ = ImagePtr;
	NewAnimation->cur_ = _Start;
	NewAnimation->curframeTime_ = _FrameTime;
	NewAnimation->pivot_ = pivot_;
	NewAnimation->renderer_ = this;
	NewAnimation->loop_ = _Loop;

	allAnimation_.insert(std::map<std::string, FrameAnimation*>::value_type(_Name, NewAnimation));

}

void GameEngineRenderer::AnimationUpdate()
{
	if (nullptr == curani_)
	{
		GameEngineDebug::AssertFalse();
		return;
	}

	curani_->Update();
}

bool GameEngineRenderer::IsCurAnimationName(const std::string& _Name)
{
	if (nullptr == curani_)
	{
		GameEngineDebug::AssertFalse();
		return false;
	}

	if (curani_->GetName() == _Name)
	{
		return true;
	}

	return false;
}

bool GameEngineRenderer::IsCurAnimationEnd()
{
	if (nullptr == curani_)
	{
		GameEngineDebug::AssertFalse();
		return false;
	}

	return curani_->isend_;
}

void GameEngineRenderer::SetChangeFrame(const std::string& _Name, int _index, float _Time)
{
	FrameAnimation* FindAni = FindAnimation(_Name);

	if (nullptr == FindAni)
	{
		GameEngineDebug::AssertFalse();
		return;
	}

	FindAni->frameTime_[static_cast<size_t>(_index - FindAni->start_)] = _Time;

}

int GameEngineRenderer::GetCurAnimationFrame()
{
	if (nullptr == curani_)
	{
		GameEngineDebug::AssertFalse();
		return false;
	}

	return curani_->cur_;
}