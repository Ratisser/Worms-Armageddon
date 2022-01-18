#include "Worm.h"

#include <GameEngineRenderer.h>
#include <GameEngineInput.h>
#include <GameEngineTime.h>
#include <GameEngineLevelManager.h>
#include <GameEngineLevel.h>
#include <GameEngineCollision.h>

#include <GameEngineDebugExtension.h>

#include "eCollisionGroup.h"
#include "eCollisionCheckColor.h"

Worm::Worm()
	: mainRender_(nullptr)
	, crosshairRender_(nullptr)
	, bottomCenterCollision_(nullptr)
	, groundCheckCollision_(nullptr)
	, accelation_(float4::ZERO)
	, speed_(float4::ZERO)
	, direction_(float4::RIGHT)
	, forward_(float4::RIGHT)
	, bGround_(false)
	, bLeft_(false)
	, bBackJump_(false)
	, deltaTime_(0.0f)
	, weaponEquipDelay_(0.0f)
	, aimRotation_(90.0f * GameEngineMath::DegreeToRadian)
	, state_(this)
	, currentWeapon_(eItemList::WEAPON_BAZOOKA)
	, nextState_("")
	, bFocus_(true)
{

}

Worm::~Worm() // default destructer 디폴트 소멸자
{

}

void Worm::Start()
{
	SetPos({ 1625.f, -235.f });
	SetRenderOrder(static_cast<int>(RenderOrder::Worm));
	initRenderer();
	initCollision();
	initInput();
	initState();
}

void Worm::initRenderer()
{
	mainRender_ = CreateRenderer("walkRight.bmp");

	mainRender_->CreateAnimation("WalkRight", "walkRight.bmp", 0, 14, true, 0.033f);
	mainRender_->CreateAnimation("WalkLeft", "walkLeft.bmp", 0, 14, true, 0.033f);

	mainRender_->CreateAnimation("JumpReadyLeft", "jumpReadyLeft.bmp", 0, 9, true, 0.033f);
	mainRender_->CreateAnimation("JumpReadyRight", "jumpReadyRight.bmp", 0, 9, true, 0.033f);

	mainRender_->CreateAnimation("FlyUpLeft", "flyUpLeft.bmp", 0, 1, true, 0.033f);
	mainRender_->CreateAnimation("FlyUpRight", "flyUpRight.bmp", 0, 1, true, 0.033f);

	mainRender_->CreateAnimation("FlyDownLeft", "flyDownLeft.bmp", 0, 1, true, 0.033f);
	mainRender_->CreateAnimation("FlyDownRight", "flyDownRight.bmp", 0, 1, true, 0.033f);

	mainRender_->CreateAnimation("FlyLinkLeft", "flyLinkLeft.bmp", 0, 6, true, 0.033f);
	mainRender_->CreateAnimation("FlyLinkRight", "flyLinkRight.bmp", 0, 6, true, 0.033f);

	mainRender_->CreateAnimation("IdleLeft", "idleLeft.bmp", 0, 5, true, 0.1f);
	mainRender_->CreateAnimation("IdleRight", "idleRight.bmp", 0, 5, true, 0.1f);

	mainRender_->CreateAnimation("BazOnLeft", "bazOnLeft.bmp", 0, 6, false, 0.033f);
	mainRender_->CreateAnimation("BazOnRight", "bazOnRight.bmp", 0, 6, false, 0.033f);

	mainRender_->CreateAnimation("BazOffLeft", "bazOffLeft.bmp", 0, 6, false, 0.033f);
	mainRender_->CreateAnimation("BazOffRight", "bazOffRight.bmp", 0, 6, false, 0.033f);

	mainRender_->CreateAnimation("BazAimLeft", "bazAimLeft.bmp", 0, 31, false, 1.0f);
	mainRender_->CreateAnimation("BazAimRight", "bazAimRight.bmp", 0, 31, false, 1.0f);

	mainRender_->ChangeAnimation("IdleRight", std::string("idleRight.bmp"));

	crosshairRender_ = CreateRenderer("crshairr.bmp");
	crosshairRender_->CreateAnimation("Aim", "crshairr.bmp", 0, 31, false, 1.0f);
	crosshairRender_->ChangeAnimation("Aim");
	crosshairRender_->Off();
}

void Worm::initInput()
{
	if (false == GameEngineInput::GetInst().IsKey("UpArrow"))
	{
		GameEngineInput::GetInst().CreateKey("UpArrow", VK_UP);
	}
	if (false == GameEngineInput::GetInst().IsKey("DownArrow"))
	{
		GameEngineInput::GetInst().CreateKey("DownArrow", VK_DOWN);
	}
	if (false == GameEngineInput::GetInst().IsKey("LeftArrow"))
	{
		GameEngineInput::GetInst().CreateKey("LeftArrow", VK_LEFT);
	}
	if (false == GameEngineInput::GetInst().IsKey("RightArrow"))
	{
		GameEngineInput::GetInst().CreateKey("RightArrow", VK_RIGHT);
	}
	if (false == GameEngineInput::GetInst().IsKey("Jump"))
	{
		GameEngineInput::GetInst().CreateKey("Jump", 'C');
	}
}

void Worm::initCollision()
{
	bottomCenterCollision_ = CreateCollision(static_cast<int>(eCollisionGroup::PLAYER), CollisionCheckType::POINT);
	bottomCenterCollision_->SetColorCheck(static_cast<DWORD>(eCollisionCheckColor::MAP));
	bottomCenterCollision_->SetPivot({ 0.0f, BOTTOM_PIVOT + 0 });

	groundCheckCollision_ = CreateCollision(static_cast<int>(eCollisionGroup::PLAYER), CollisionCheckType::POINT);
	groundCheckCollision_->SetColorCheck(static_cast<DWORD>(eCollisionCheckColor::MAP));
	groundCheckCollision_->SetPivot({ 0.0f, BOTTOM_PIVOT + 1.f });
}

void Worm::initState()
{
	state_.CreateState("Idle", &Worm::startIdle, &Worm::updateIdle);
	state_.CreateState("Walk", &Worm::startWalk, &Worm::updateWalk);
	state_.CreateState("JumpReady", &Worm::startJumpReady, &Worm::updateJumpReady);
	state_.CreateState("Jump", &Worm::startJump, &Worm::updateJump);
	state_.CreateState("WeaponAim", &Worm::startWeaponAim, &Worm::updateWeaponAim);
	state_.CreateState("WeaponOn", &Worm::startWeaponOn, &Worm::updateWeaponOn);
	state_.CreateState("WeaponOff", &Worm::startWeaponOff, &Worm::updateWeaponOff);


	state_.ChangeState("Idle");
}

void Worm::addGravity()
{
	if (nullptr == groundCheckCollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MAP)))
	{
		bGround_ = false;
		speed_.y += GRAVITY_POWER * deltaTime_;
	}
	else
	{
		bGround_ = true;
		speed_.y = 0.0f;
		pos_.y = static_cast<float>(static_cast<int>(pos_.y));
	}
}

void Worm::normalMove()
{
	SetMove(speed_ * deltaTime_);

	// 땅에 박힌 것
	if (nullptr != bottomCenterCollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MAP)))
	{
		while (nullptr != bottomCenterCollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MAP)))
		{
			SetMove({ 0.0f, -1.0f });
			pos_.y = static_cast<float>(static_cast<int>(pos_.y));
		}
	}
	else
	{
		bottomCenterCollision_->SetPivot({ 0, BOTTOM_PIVOT + 1 });
		if (nullptr != bottomCenterCollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MAP)))
		{
			// 정상 땅에 딱 붙어있는 상태
			bottomCenterCollision_->SetPivot({ 0, BOTTOM_PIVOT + 0 });
			return;
		}

		// 낭떠러지에 섰다
		bottomCenterCollision_->SetPivot({ 0, BOTTOM_PIVOT + 5 });
		if (nullptr == bottomCenterCollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MAP)))
		{
			bGround_ = false;
			bottomCenterCollision_->SetPivot({ 0, BOTTOM_PIVOT + 0 });
			return;
		}


		bottomCenterCollision_->SetPivot({ 0, BOTTOM_PIVOT + 0 });
		// 여기 왔으면 경사라고 본다.
		while (nullptr == bottomCenterCollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MAP)))
		{
			SetMove({ 0.0f, 1.0f });
			pos_.y = static_cast<float>(static_cast<int>(pos_.y));
		}

		SetMove({ 0.0f, -1.0f });
	}
}

int Worm::getAimingFrame()
{
	return static_cast<int>(aimRotation_ / (AIM_STEP_RADIAN));
}

void Worm::setAimingForward()
{
	if (bLeft_)
	{
		forward_ = float4::RadianToRotatefloat2(float4::DOWN, aimRotation_);
	}
	else
	{
		forward_ = float4::RadianToRotatefloat2(float4::DOWN, -aimRotation_);
	}
}

StateInfo Worm::startIdle(StateInfo _state)
{
	if (bLeft_)
	{
		mainRender_->ChangeAnimation("IdleLeft", std::string("idleLeft.bmp"));
	}
	else
	{
		mainRender_->ChangeAnimation("IdleRight", std::string("idleRight.bmp"));
	}

	weaponEquipDelay_ = 0.0f;

	return StateInfo();
}

StateInfo Worm::updateIdle(StateInfo _state)
{
	addGravity();

	weaponEquipDelay_ += deltaTime_;
	if ( true == bFocus_)
	{
		if (weaponEquipDelay_ > WEAPON_EQUIP_DELAY)
		{
			weaponEquipDelay_ = 0.0f;
			return "WeaponOn";
		}

		if (GameEngineInput::GetInst().IsPress("UpArrow"))
		{
			return "WeaponOn";
		}

		if (GameEngineInput::GetInst().IsPress("DownArrow"))
		{
			return "WeaponOn";
		}

		if (GameEngineInput::GetInst().IsPress("LeftArrow"))
		{
			bLeft_ = true;
			return "Walk";
		}

		if (GameEngineInput::GetInst().IsPress("RightArrow"))
		{
			bLeft_ = false;
			return "Walk";
		}

		if (GameEngineInput::GetInst().IsDown("Jump"))
		{
			return "JumpReady";
		}

		normalMove();
	}

	return StateInfo();
}


StateInfo Worm::startWalk(StateInfo _state)
{
	if (bLeft_)
	{
		mainRender_->ChangeAnimation("WalkLeft", std::string("walkLeft.bmp"));
	}
	else
	{
		mainRender_->ChangeAnimation("WalkRight", std::string("walkRight.bmp"));
	}
	return StateInfo();
}


StateInfo Worm::updateWalk(StateInfo _state)
{
	addGravity();


	// 떨어지는 중
	if (speed_.y > 0.0f)
	{
		speed_.x = 0.0f;
		if (bLeft_)
		{
			mainRender_->ChangeAnimation("FlyDownLeft", std::string("flyDownLeft.bmp"));
		}
		else
		{
			mainRender_->ChangeAnimation("FlyDownRight", std::string("flyDownRight.bmp"));
		}
	}
	else // 땅에 서있다
	{
		if (GameEngineInput::GetInst().IsPress("LeftArrow"))
		{
			mainRender_->ChangeAnimation("WalkLeft", std::string("walkLeft.bmp"));
			bLeft_ = true;
			speed_.x = -MOVE_SPEED;
		}
		else if (GameEngineInput::GetInst().IsPress("RightArrow"))
		{
			mainRender_->ChangeAnimation("WalkRight", std::string("walkRight.bmp"));
			bLeft_ = false;
			speed_.x = MOVE_SPEED;
		}
		else
		{
			speed_.x = 0.0f;
			return "Idle";
		}

		if (GameEngineInput::GetInst().IsDown("Jump"))
		{
			return "JumpReady";
		}
	}

	normalMove();
	return StateInfo();
}

StateInfo Worm::startJumpReady(StateInfo _state)
{
	if (bLeft_)
	{
		mainRender_->ChangeAnimation("JumpReadyLeft", std::string("jumpReadyLeft.bmp"));
	}
	else
	{
		mainRender_->ChangeAnimation("JumpReadyRight", std::string("jumpReadyRight.bmp"));
	}
	return StateInfo();
}

StateInfo Worm::updateJumpReady(StateInfo _state)
{
	if (mainRender_->IsCurAnimationEnd())
	{
		return "Jump";
	}

	if (GameEngineInput::GetInst().IsDown("Jump"))
	{
		bBackJump_ = true;
	}

	return StateInfo();
}

StateInfo Worm::startJump(StateInfo _state)
{
	if (bLeft_)
	{
		speed_.x = -JUMP_POWER;
		speed_.y = -JUMP_POWER;
		SetMove({ 0.0f, -6.f });
		mainRender_->ChangeAnimation("FlyUpLeft", std::string("flyUpLeft.bmp"));
	}
	else
	{
		speed_.x = JUMP_POWER;
		speed_.y = -JUMP_POWER;
		SetMove({ 0.0f, -6.f });
		mainRender_->ChangeAnimation("FlyUpRight", std::string("flyUpRight.bmp"));
	}

	if (bBackJump_)
	{
		speed_.x *= -1.0f;
		bBackJump_ = false;
	}
	return StateInfo();
}

StateInfo Worm::updateJump(StateInfo _state)
{
	addGravity();

	if (speed_.y > 0.0f)
	{
		if (bLeft_)
		{
			mainRender_->ChangeAnimation("FlyDownLeft", std::string("flyDownLeft.bmp"));
		}
		else
		{
			mainRender_->ChangeAnimation("FlyDownRight", std::string("flyDownRight.bmp"));
		}
	}


	if (nullptr != groundCheckCollision_->CollisionGroupCheckOne(eCollisionGroup::MAP))
	{
		speed_ = { 0.0f, 0.0f };
		return "Idle";
	}

	//SetMove(speed_ * deltaTime_);
	normalMove();
	return StateInfo();
}

StateInfo Worm::startWeaponAim(StateInfo _state)
{
	if (bLeft_)
	{
		mainRender_->ChangeAnimation("BazAimLeft", std::string("bazAimLeft.bmp"));
	}
	else
	{
		mainRender_->ChangeAnimation("BazAimRight", std::string("bazAimRight.bmp"));
	}

	int frame = getAimingFrame();
	mainRender_->SetAnimationCurrentFrame(frame);
	setAimingForward();
	crosshairRender_->On();
	crosshairRender_->SetPivotPos(forward_ * 50.f);
	return StateInfo();
}

StateInfo Worm::updateWeaponAim(StateInfo _state)
{
	addGravity();
	if (GameEngineInput::GetInst().IsPress("UpArrow"))
	{
		aimRotation_ += deltaTime_;
		if (aimRotation_ >= 180.f * GameEngineMath::DegreeToRadian)
		{
			aimRotation_ = 180.f * GameEngineMath::DegreeToRadian;
		}
	}

	if (GameEngineInput::GetInst().IsPress("DownArrow"))
	{
		aimRotation_ -= deltaTime_;
		if (aimRotation_ <= 0.0f)
		{
			aimRotation_ = 0.0f;
		}
	}

	int frame = getAimingFrame();
	mainRender_->SetAnimationCurrentFrame(frame);

	if (bLeft_)
	{
		crosshairRender_->SetAnimationCurrentFrame(frame);
	}
	else
	{
		crosshairRender_->SetAnimationCurrentFrame(31 - frame);
	}

	setAimingForward();
	crosshairRender_->SetPivotPos(forward_ * 50.f);

	GameEngineDebugExtension::PrintDebugWindowText("Ratation : ", aimRotation_ * GameEngineMath::RadianToDegree);
	GameEngineDebugExtension::PrintDebugWindowText("forward : ", forward_.x, ", ", forward_.y);

	if (true == bFocus_)
	{
		if (GameEngineInput::GetInst().IsPress("LeftArrow"))
		{
			bLeft_ = true;
			nextState_ = "Walk";
			return "WeaponOff";
		}

		if (GameEngineInput::GetInst().IsPress("RightArrow"))
		{
			bLeft_ = false;
			nextState_ = "Walk";
			return "WeaponOff";
		}

		if (GameEngineInput::GetInst().IsDown("Jump"))
		{
			nextState_ = "JumpReady";
			return "WeaponOff";
		}

		normalMove();
	}

	return StateInfo();
}

StateInfo Worm::startWeaponOn(StateInfo _state)
{
	if (bLeft_)
	{
		mainRender_->ChangeAnimation("BazOnLeft", std::string("bazOnLeft.bmp"));
	}
	else
	{
		mainRender_->ChangeAnimation("BazOnRight", std::string("bazOnRight.bmp"));
	}
	return StateInfo();
}

StateInfo Worm::updateWeaponOn(StateInfo _state)
{
	if (mainRender_->IsCurAnimationEnd())
	{
		return "WeaponAim";
	}
	return StateInfo();
}

StateInfo Worm::startWeaponOff(StateInfo _state)
{
	if (bLeft_)
	{
		mainRender_->ChangeAnimation("BazOffLeft", std::string("bazOffLeft.bmp"));
	}
	else
	{
		mainRender_->ChangeAnimation("BazOffRight", std::string("bazOffRight.bmp"));
	}
	crosshairRender_->Off();
	return StateInfo();
}

StateInfo Worm::updateWeaponOff(StateInfo _state)
{
	if (mainRender_->IsCurAnimationEnd())
	{
		return nextState_;
	}
	return StateInfo();
}

void Worm::UpdateBefore()
{
	mainRender_->AnimationUpdate();
	crosshairRender_->AnimationUpdate();
}

void Worm::Update()
{
	deltaTime_ = GameEngineTime::GetInst().GetDeltaTime();
	state_.Update();
}

void Worm::UpdateAfter()
{
}

void Worm::Render()
{
	mainRender_->Render();
	if (crosshairRender_->IsOn())
	{
		crosshairRender_->Render();
	}

	//bottomCenterCollision_->DebugRender();
	//groundCheckCollision_->DebugRender();
}

