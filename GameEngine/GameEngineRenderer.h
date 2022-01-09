#pragma once
#include <map>
#include <vector>
#include <string>
#include <GameEngineMath.h>
#include <GameEngineNameBase.h>

// ����� ���� �ڷ���
// ���� ����(�ϳ��� ��ü�� ��� ���¸� �����ٰ� �Ҷ�)�� 
// ��������� ǥ���ϰ� ������ ���� ����մϴ�.
enum class RENDERPIVOT
{
	CENTER,
	BOT,
	LEFTTOP,
	MAX,
};

// �з� : ������
// �뵵 : �׸��� �׸��µ� �ʿ��� ���Ǳ���� �����Ѵ�.
// ���� : ���Ͱ� �����ϸ� �������� �ʿ��� ���Ǳ�� ����
class GameEngineActor;
class GameEngineImage;
class GameEngineImageFile;
class GameEngineRenderer : public GameEngineNameBase
{
private:
	class FrameAnimation : public GameEngineNameBase
	{
		friend GameEngineRenderer;

	private:
		int start_;
		int end_;
		int cur_;
		std::vector<float> frameTime_;

		float curframeTime_;
		GameEngineRenderer* renderer_;
		GameEngineImageFile* image_;
		RENDERPIVOT pivot_;
		bool loop_;
		bool isend_;

	private:
		FrameAnimation();

	private:
		void Reset()
		{
			cur_ = start_;
			curframeTime_ = frameTime_[0];
			isend_ = false;
		}
		void Update();
	};

public:
	friend GameEngineActor;

private:	// member Var
	GameEngineActor* actor_;
	float4 imagePivot_;
	float4 pivotpos_;
	float4 rendersize_;
	float4 imagepos_;
	float4 imagesize_;
	GameEngineImageFile* image_;
	GameEngineImageFile* maskimage_;
	bool isCamEffect_;
	float rotate_;
	int alpha_;

private:
	void SetActor(GameEngineActor* _parent)
	{
		actor_ = _parent;
	}

public:
	void SetAlpha(const int _Value)
	{
		alpha_ = _Value;

		if (255 <= alpha_)
		{
			alpha_ = 255;
			return;
		}

		if (0 >= alpha_)
		{
			alpha_ = 0;
			return;
		}
	}

	void SetAddAlpha(const int _Value)
	{
		alpha_ += _Value;

		if (255 <= alpha_)
		{
			alpha_ = 255;
			return;
		}

		if (0 >= alpha_)
		{
			alpha_ = 0;
			return;
		}

	}

	void SetRotate(const float _Value)
	{
		rotate_ = _Value;
	}

	void SetAddRotate(const float _Value)
	{
		rotate_ += _Value;
	}

	void SetImagePivot(const float4& _Value)
	{
		imagePivot_ = _Value;
	}

	void SetPivotPos(const float4& _Value)
	{
		pivotpos_ = _Value;
	}
	void SetRenderSize(const float4& _Value)
	{
		rendersize_ = _Value;
	}
	void SetImagePos(const float4& _Value)
	{
		imagepos_ = _Value;
	}
	void SetImageSize(const float4& _Value)
	{
		imagesize_ = _Value;
	}

	void SetCameraEffectOn() 
	{
		isCamEffect_ = true;
	}

	void SetCameraEffectOff()
	{
		isCamEffect_ = false;
	}

	void SetImage(const std::string& _Name);

	void SetMaskImage(const std::string& _Name);

	void SetImage(GameEngineImageFile* _image)
	{
		image_ = _image;
	}

	GameEngineImageFile* GetImage() {
		return image_;
	}

public:
	GameEngineRenderer(); // default constructer ����Ʈ ������
	~GameEngineRenderer(); // default destructer ����Ʈ �Ҹ���

public:		// delete constructer
	GameEngineRenderer(const GameEngineRenderer& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineRenderer(GameEngineRenderer&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

public:		//delete operator
	GameEngineRenderer& operator=(const GameEngineRenderer& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineRenderer& operator=(const GameEngineRenderer&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:		//member Func
	void SetCutIndex(size_t _Index, RENDERPIVOT _Pivot = RENDERPIVOT::CENTER);
	void Render();

private:
	std::map<std::string, FrameAnimation*> allAnimation_;
	FrameAnimation* curani_;

private:
	FrameAnimation* FindAnimation(const std::string& _name);

public:
	void CreateAnimation(
		const std::string& _Name, // idle,
		const std::string& _ImageName, // ,
		int _Start,
		int _End,
		bool _Loop = true,
		float _FrameTime = 0.1f,
		RENDERPIVOT pivot_ = RENDERPIVOT::CENTER
	);

	bool IsCurAnimationName(const std::string& _Name);
	void ChangeAnimation(const std::string& _Name, bool _forceChange = false);
	void SetChangeFrame(const std::string& _Name, int _index, float _Time);
	void AnimationUpdate();
	bool IsCurAnimationEnd();

	int GetCurAnimationFrame();
};

