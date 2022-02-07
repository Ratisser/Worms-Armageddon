#include "Worm.h"
#include "UIController.h"

#include <GameEngineRenderer.h>
#include <GameEngineInput.h>
#include <GameEngineTime.h>
#include <GameEngineLevelManager.h>
#include <GameEngineLevel.h>
#include <GameEngineCollision.h>

#include <GameEngineDebugExtension.h>

#include <GameEngineWindow.h>
#include <limits>

#include <GameEngineSoundManager.h>

#include "eCollisionGroup.h"
#include "eCollisionCheckColor.h"

#include "Bazooka.h"
#include "FirePunch.h"
#include "HomingMissile.h"
#include "MouseObject.h"
#include "GameController.h"
#include "Uzi.h"
#include "Sheep.h"
#include "Girder.h"
#include "SuperSheep.h"
#include "PlayLevel.h"
#include "MapTrain.h"

Worm::Worm()
	: mainRender_(nullptr)
	, crosshairRender_(nullptr)
	, bottomCenterCollision_(nullptr)
	, groundCheckCollision_(nullptr)
	, leftSideCollision_(nullptr)
	, rightSideCollision_(nullptr)
	, headCollision_(nullptr)
	, accelation_(float4::ZERO)
	, speed_(float4::ZERO)
	, direction_(float4::RIGHT)
	, forward_(float4::RIGHT)
	, bGround_(false)
	, bLeft_(false)
	, bBackJump_(false)
	, deltaTime_(0.0f)
	, weaponEquipDelay_(0.0f)
	, firePower_(0.0f)
	, aimRotation_(90.0f * GameEngineMath::DegreeToRadian)
	, currentRotation_(90.f * GameEngineMath::DegreeToRadian)
	, state_(this)
	, currentWeapon_(eItemList::WEAPON_BAZOOKA)
	, nextState_("")
	, bFocus_(false)
	, uicontroller_(nullptr)
	, hp_(100)
	, actionToken_(0)
	, bulletFocusActor_(nullptr)
	, blowTorchMoveTime_(3.f)
	, drillMoveTime_(0.f)
	, soundWhoosh_("DRILL.WAV")
{

}

Worm::~Worm() // default destructer 디폴트 소멸자
{

}

void Worm::Start()
{
	SetRenderOrder(static_cast<int>(RenderOrder::Worm));
	SetUpdateOrder(10);
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

	mainRender_->CreateAnimation("BazAimLeft", "bazAimLeft.bmp", 0, 31, false, FLT_MAX); // std::numeric_limit<float>::max()
	mainRender_->CreateAnimation("BazAimRight", "bazAimRight.bmp", 0, 31, false, FLT_MAX);

	mainRender_->CreateAnimation("ThrowStartLeft", "throwStartLeft.bmp", 0, 31, false, FLT_MAX); // 투척물 던진 직후 한 순간만 적용됩니다.
	mainRender_->CreateAnimation("ThrowStartRight", "throwStartRight.bmp", 0, 31, false, FLT_MAX);
	mainRender_->CreateAnimation("ThrowOffLeft", "throwOffLeft.bmp", 0, 9, false, 0.033f); // 던진 직후, 손을 다시 넣어 idle 로 가는 애니메이션
	mainRender_->CreateAnimation("ThrowOffRight", "throwOffRight.bmp", 0, 9, false, 0.033f);

	mainRender_->CreateAnimation("GrnAimLeft", "grnAimLeft.bmp", 0, 31, false, FLT_MAX); // 수류탄 애니메이션들입니다.
	mainRender_->CreateAnimation("GrnAimRight", "grnAimRight.bmp", 0, 31, false, FLT_MAX);
	mainRender_->CreateAnimation("GrnOnLeft", "grnOnLeft.bmp", 0, 9, false, 0.033f);
	mainRender_->CreateAnimation("GrnOnRight", "grnOnRight.bmp", 0, 9, false, 0.033f);
	mainRender_->CreateAnimation("GrnOffLeft", "grnOffLeft.bmp", 0, 9, false, 0.033f);
	mainRender_->CreateAnimation("GrnOffRight", "grnOffRight.bmp", 0, 9, false, 0.033f);

	mainRender_->CreateAnimation("FirepunchReadyLeft", "firePunchReadyLeft.bmp", 0, 25, false, 0.033f); // 승룡권 애니메이션입니다.
	mainRender_->CreateAnimation("FirepunchReadyRight", "firePunchReadyRight.bmp", 0, 25, false, 0.033f);
	mainRender_->CreateAnimation("FirepunchStartLeft", "firePunchStartLeft.bmp", 0, 8, false, 0.033f);
	mainRender_->CreateAnimation("FirepunchStartRight", "firePunchStartRight.bmp", 0, 8, false, 0.033f);
	mainRender_->CreateAnimation("FirepunchFlyLeft", "firePunchFlyLeft.bmp", 0, 2, false, 0.033f);
	mainRender_->CreateAnimation("FirepunchFlyRight", "firePunchFlyRight.bmp", 0, 2, false, 0.033f);
	mainRender_->CreateAnimation("FirepunchEndLeft", "firePunchEndLeft.bmp", 0, 12, false, 0.033f);
	mainRender_->CreateAnimation("FirepunchEndRight", "firePunchEndRight.bmp", 0, 12, false, 0.033f);
	mainRender_->CreateAnimation("FirepunchLandLeft", "firePunchLandLeft.bmp", 0, 7, false, 0.033f);
	mainRender_->CreateAnimation("FirepunchLandRight", "firePunchLandRight.bmp", 0, 7, false, 0.033f);
	mainRender_->CreateAnimation("FirepunchOffLeft", "firePunchOffLeft.bmp", 0, 25, false, 0.033f);
	mainRender_->CreateAnimation("FirepunchOffRight", "firePunchOffRight.bmp", 0, 25, false, 0.033f);

	mainRender_->CreateAnimation("UziOnLeft", "uziOnLeft.bmp", 0, 6, false, 0.033f); // 우지 애니메이션입니다.
	mainRender_->CreateAnimation("UziOnRight", "uziOnRight.bmp", 0, 6, false, 0.033f);
	mainRender_->CreateAnimation("UziOffLeft", "uziOffLeft.bmp", 0, 6, false, 0.033f);
	mainRender_->CreateAnimation("UziOffRight", "uziOffRight.bmp", 0, 6, false, 0.033f);
	mainRender_->CreateAnimation("UziAimLeft", "uziAimLeft.bmp", 0, 31, false, FLT_MAX);
	mainRender_->CreateAnimation("UziAimRight", "uziAimRight.bmp", 0, 31, false, FLT_MAX);
	mainRender_->CreateAnimation("UziFireLeft", "uziFireLeft.bmp", 0, 31, false, FLT_MAX);
	mainRender_->CreateAnimation("UziFireRight", "uziFireRight.bmp", 0, 31, false, FLT_MAX);

	mainRender_->CreateAnimation("SheepOnLeft", "sheepOnLeft.bmp", 0, 9, false, 0.033f);
	mainRender_->CreateAnimation("SheepOnRight", "sheepOnRight.bmp", 0, 9, false, 0.033f);
	mainRender_->CreateAnimation("SheepOffLeft", "sheepOffLeft.bmp", 0, 9, false, 0.033f);
	mainRender_->CreateAnimation("SheepOffRight", "sheepOffRight.bmp", 0, 9, false, 0.033f);
	mainRender_->CreateAnimation("SheepAimLeft", "sheepOnLeft.bmp", 9, 9, true);
	mainRender_->CreateAnimation("SheepAimRight", "sheepOnRight.bmp", 9, 9, true);

	mainRender_->CreateAnimation("HomingOnLeft", "homingOnLeft.bmp", 0, 6, false, 0.033f); // 호밍 미사일 애니메이션입니다.
	mainRender_->CreateAnimation("HomingOnRight", "homingOnRight.bmp", 0, 6, false, 0.033f);
	mainRender_->CreateAnimation("HomingOffLeft", "homingOffLeft.bmp", 0, 6, false, 0.033f);
	mainRender_->CreateAnimation("HomingOffRight", "homingOffRight.bmp", 0, 6, false, 0.033f);
	mainRender_->CreateAnimation("HomingAimLeft", "homingAimLeft.bmp", 0, 31, false, FLT_MAX);
	mainRender_->CreateAnimation("HomingAimRight", "homingAimRight.bmp", 0, 31, false, FLT_MAX);

	mainRender_->CreateAnimation("BattleAxeOnLeft", "axeOnLeft.bmp", 0, 14, false, 0.033f); // 배틀액스 애니메이션입니다.
	mainRender_->CreateAnimation("BattleAxeOnRight", "axeOnRight.bmp", 0, 14, false, 0.033f);
	mainRender_->CreateAnimation("BattleAxeFire1Left", "axeFire1Left.bmp", 0, 22, false, 0.033f);
	mainRender_->CreateAnimation("BattleAxeFire1Right", "axeFire1Right.bmp", 0, 22, false, 0.033f);
	mainRender_->CreateAnimation("BattleAxeFire2Left", "axeFire2Left.bmp", 0, 3, false, 0.033f);
	mainRender_->CreateAnimation("BattleAxeFire2Right", "axeFire2Right.bmp", 0, 3, false, 0.033f);
	mainRender_->CreateAnimation("BattleAxeFire3Left", "axeFire3Left.bmp", 0, 17, false, 0.033f);
	mainRender_->CreateAnimation("BattleAxeFire3Right", "axeFire3Right.bmp", 0, 17, false, 0.033f);
	mainRender_->CreateAnimation("BattleAxeOffLeft", "axeOffLeft.bmp", 0, 14, false, 0.033f);
	mainRender_->CreateAnimation("BattleAxeOffRight", "axeOffRight.bmp", 0, 14, false, 0.033f);

	mainRender_->CreateAnimation("GirderOnLeft", "girderOnLeft.bmp", 0, 14, false, 0.033f); // Girder 애니메이션입니다.
	mainRender_->CreateAnimation("GirderOnRight", "girderOnRight.bmp", 0, 14, false, 0.033f);
	mainRender_->CreateAnimation("GirderOffLeft", "girderOffLeft.bmp", 0, 14, false, 0.033f);
	mainRender_->CreateAnimation("GirderOffRight", "girderOffRight.bmp", 0, 14, false, 0.033f);

	mainRender_->CreateAnimation("BlowtorchOnLeft", "blowtorchOnLeft.bmp", 0, 14, false, 0.033f); // 토치 애니메이션입니다.
	mainRender_->CreateAnimation("BlowtorchOnRight", "blowtorchOnRight.bmp", 0, 14, false, 0.033f);
	mainRender_->CreateAnimation("BlowtorchOffLeft", "blowtorchOffLeft.bmp", 0, 14, false, 0.033f);
	mainRender_->CreateAnimation("BlowtorchOffRight", "blowtorchOffRight.bmp", 0, 14, false, 0.033f);
	mainRender_->CreateAnimation("BlowtorchFireLeft", "blowtorchFireLeft.bmp", 0, 14, true, 0.033f);
	mainRender_->CreateAnimation("BlowtorchFireRight", "blowtorchFireRight.bmp", 0, 14, true, 0.033f);

	mainRender_->CreateAnimation("DrillLeft", "drillLeft.bmp", 0, 3, true, 0.033f); // 드릴 애니메이션입니다.
	mainRender_->CreateAnimation("DrillRight", "drillRight.bmp", 0, 3, true, 0.033f);
	mainRender_->CreateAnimation("DrillOnLeft", "drillOnLeft.bmp", 0, 12, false, 0.033f);
	mainRender_->CreateAnimation("DrillOnRight", "drillOnRight.bmp", 0, 12, false, 0.033f);
	mainRender_->CreateAnimation("DrillOffLeft", "drillOffLeft.bmp", 0, 12, false, 0.033f);
	mainRender_->CreateAnimation("DrillOffRight", "drillOffRight.bmp", 0, 12, false, 0.033f);

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
	if (false == GameEngineInput::GetInst().IsKey("Fire"))
	{
		GameEngineInput::GetInst().CreateKey("Fire", VK_SPACE);
	}
	if (false == GameEngineInput::GetInst().IsKey("Mouse"))
	{
		GameEngineInput::GetInst().CreateKey("Mouse", VK_LBUTTON);
	}
}

void Worm::initCollision()
{
	bottomCenterCollision_ = CreateCollision(static_cast<int>(eCollisionGroup::PLAYER), CollisionCheckType::POINT);
	bottomCenterCollision_->SetColorCheck(static_cast<DWORD>(eCollisionCheckColor::MAP));
	bottomCenterCollision_->SetPivot({ 0.0f, PLAYER_BOTTOM_PIVOT + 0.f });

	groundCheckCollision_ = CreateCollision(static_cast<int>(eCollisionGroup::PLAYER), CollisionCheckType::POINT);
	groundCheckCollision_->SetColorCheck(static_cast<DWORD>(eCollisionCheckColor::MAP));
	groundCheckCollision_->SetPivot({ 0.0f, PLAYER_BOTTOM_PIVOT + 1.f });

	leftSideCollision_ = CreateCollision(static_cast<int>(eCollisionGroup::PLAYER), CollisionCheckType::POINT);
	leftSideCollision_->SetColorCheck(static_cast<DWORD>(eCollisionCheckColor::MAP));
	leftSideCollision_->SetPivot({ -3.0f, PLAYER_BOTTOM_PIVOT - 9.0f });

	rightSideCollision_ = CreateCollision(static_cast<int>(eCollisionGroup::PLAYER), CollisionCheckType::POINT);
	rightSideCollision_->SetColorCheck(static_cast<DWORD>(eCollisionCheckColor::MAP));
	rightSideCollision_->SetPivot({ 3.0f, PLAYER_BOTTOM_PIVOT - 9.0f });

	headCollision_ = CreateCollision(static_cast<int>(eCollisionGroup::PLAYER), CollisionCheckType::POINT);
	headCollision_->SetColorCheck(static_cast<DWORD>(eCollisionCheckColor::MAP));
	headCollision_->SetPivot({ 0.0f, -PLAYER_BOTTOM_PIVOT + 9.f });
}

void Worm::initState()
{
	state_.CreateState("Idle", &Worm::startIdle, &Worm::updateIdle);
	state_.CreateState("Walk", &Worm::startWalk, &Worm::updateWalk);
	state_.CreateState("JumpReady", &Worm::startJumpReady, &Worm::updateJumpReady);
	state_.CreateState("Jump", &Worm::startJump, &Worm::updateJump);
	state_.CreateState("WeaponOn", &Worm::startWeaponOn, &Worm::updateWeaponOn);
	state_.CreateState("WeaponOff", &Worm::startWeaponOff, &Worm::updateWeaponOff);

	state_.CreateState("BazookaAim", &Worm::startBazookaAim, &Worm::updateBazookaAim);
	state_.CreateState("BazookaFire", &Worm::startBazookaFire, &Worm::updateBazookaFire);
	state_.CreateState("BazookaWait", &Worm::startBazookaWait, &Worm::updateBazookaWait);

	state_.CreateState("HomingStart", &Worm::startHomingStart, &Worm::updateHomingStart);
	state_.CreateState("HomingAim", &Worm::startHomingAim, &Worm::updateHomingAim);
	state_.CreateState("HomingFire", &Worm::startHomingFire, &Worm::updateHomingFire);
	state_.CreateState("HomingWait", &Worm::startHomingWait, &Worm::updateHomingWait);

	state_.CreateState("FirepunchReady", &Worm::startFirepunchReady, &Worm::updateFirepunchReady);
	state_.CreateState("FirepunchStart", &Worm::startFirepunchStart, &Worm::updateFirepunchStart);
	state_.CreateState("FirepunchFly", &Worm::startFirepunchFly, &Worm::updateFirepunchFly);
	state_.CreateState("FirepunchEnd", &Worm::startFirepunchEnd, &Worm::updateFirepunchEnd);
	state_.CreateState("FirepunchLand", &Worm::startFirepunchLand, &Worm::updateFirepunchLand);
	state_.CreateState("FirepunchOff", &Worm::startFirepunchOff, &Worm::updateFirepunchOff);

	state_.CreateState("BattleAxeOn", &Worm::startBattleAxeOn, &Worm::updateBattleAxeOn);
	state_.CreateState("BattleAxeFire1", &Worm::startBattleAxeFire1, &Worm::updateBattleAxeFire1);
	state_.CreateState("BattleAxeFire2", &Worm::startBattleAxeFire2, &Worm::updateBattleAxeFire2);
	state_.CreateState("BattleAxeFire3", &Worm::startBattleAxeFire3, &Worm::updateBattleAxeFire3);
	state_.CreateState("BattleAxeOff", &Worm::startBattleAxeOff, &Worm::updateBattleAxeOff);
	state_.CreateState("BattleAxeWait", &Worm::startBattleAxeWait, &Worm::updateBattleAxeWait);

	state_.CreateState("UziAim", &Worm::startUziAim, &Worm::updateUziAim);
	state_.CreateState("UziFire", &Worm::startUziFire, &Worm::updateUziFire);
	state_.CreateState("UziWait", &Worm::startUziWait, &Worm::updateUziWait);

	state_.CreateState("SheepAim", &Worm::startSheepAim, &Worm::updateSheepAim);
	state_.CreateState("SheepFire", &Worm::startSheepFire, &Worm::updateSheepFire);
	state_.CreateState("SheepWait", &Worm::startSheepWait, &Worm::updateSheepWait);

	state_.CreateState("SuperSheepAim", &Worm::startSuperSheepAim, &Worm::updateSuperSheepAim);
	state_.CreateState("SuperSheepFire", &Worm::startSuperSheepFire, &Worm::updateSuperSheepFire);
	state_.CreateState("SuperSheepWait", &Worm::startSuperSheepWait, &Worm::updateSuperSheepWait);

	state_.CreateState("GirderOn", &Worm::startGirderOn, &Worm::updateGirderOn);

	state_.CreateState("BlowtorchOn", &Worm::startBlowtorchOn, &Worm::updateBlowtorchOn);
	state_.CreateState("BlowtorchFire", &Worm::startBlowtorchFire, &Worm::updateBlowtorchFire);

	state_.CreateState("DrillOn", &Worm::startDrillOn, &Worm::updateDrillOn);
	state_.CreateState("DrillFire", &Worm::startDrillFire, &Worm::updateDrillFire);

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
		bottomCenterCollision_->SetPivot({ 0, PLAYER_BOTTOM_PIVOT + 1 });
		if (nullptr != bottomCenterCollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MAP)))
		{
			// 정상 땅에 딱 붙어있는 상태
			bottomCenterCollision_->SetPivot({ 0, PLAYER_BOTTOM_PIVOT + 0 });
			return;
		}

		// 낭떠러지에 섰다
		bottomCenterCollision_->SetPivot({ 0, PLAYER_BOTTOM_PIVOT + 5 });
		if (nullptr == bottomCenterCollision_->CollisionGroupCheckOne(static_cast<int>(eCollisionGroup::MAP)))
		{
			bGround_ = false;
			bottomCenterCollision_->SetPivot({ 0, PLAYER_BOTTOM_PIVOT + 0 });
			return;
		}


		bottomCenterCollision_->SetPivot({ 0, PLAYER_BOTTOM_PIVOT + 0 });
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

std::string Worm::getWeaponAimState()
{
	switch (currentWeapon_)
	{
	case eItemList::WEAPON_JETPACK:
		break;
	case eItemList::WEAPON_LOWGRAVITY:
		break;
	case eItemList::WEAPON_FASTWALK:
		break;
	case eItemList::WEAPON_LASERSIGHT:
		break;
	case eItemList::WEAPON_INVISIBILITY:
		break;
	case eItemList::WEAPON_BAZOOKA:
		return "BazookaAim";
		break;
	case eItemList::WEAPON_HOMINGMISSILE:
		return "HomingStart";
		break;
	case eItemList::WEAPON_MORTAR:
		break;
	case eItemList::WEAPON_HOMINGPIGEON:
		break;
	case eItemList::WEAPON_SHEEPLAUNCHER:
		break;
	case eItemList::WEAPON_GRENADE:
		break;
	case eItemList::WEAPON_CLUSTERBOMB:
		break;
	case eItemList::WEAPON_BANNANABOMB:
		break;
	case eItemList::WEAPON_BATTLEAXE:
		return "BattleAxeOn";
		break;
	case eItemList::WEAPON_EARTHQUAKE:
		break;
	case eItemList::WEAPON_SHOTGUN:
		break;
	case eItemList::WEAPON_HANDGUN:
		break;
	case eItemList::WEAPON_UZI:
		return "UziAim";
		break;
	case eItemList::WEAPON_MINIGUN:
		break;
	case eItemList::WEAPON_LONGBOW:
		break;
	case eItemList::WEAPON_FIREPUNCH:
		return "FirepunchReady";
		break;
	case eItemList::WEAPON_DRAGONBALL:
		break;
	case eItemList::WEAPON_KAMIKAZE:
		break;
	case eItemList::WEAPON_SUICIDEBOMBER:
		break;
	case eItemList::WEAPON_PROD:
		break;
	case eItemList::WEAPON_DYNAMITE:
		break;
	case eItemList::WEAPON_MINE:
		//11
		break;
	case eItemList::WEAPON_SHEEP:
		return "SheepAim";
		break;
	case eItemList::WEAPON_SUPERSHEEP:
		return "SuperSheepAim";
		break;
	case eItemList::WEAPON_MOLEBOMB:
		break;
	case eItemList::WEAPON_AIRSTRIKE:
		break;
	case eItemList::WEAPON_NAPALMSTRIKE:
		break;
	case eItemList::WEAPON_MAILSTRIKE:
		break;
	case eItemList::WEAPON_MINESTRIKE:
		break;
	case eItemList::WEAPON_MOLESQUADRON:
		break;
	case eItemList::WEAPON_BLOWTORCH:
		return "BlowtorchOn";
		break;
	case eItemList::WEAPON_PNEUMATICDRILL:
		return "DrillOn";
		break;
	case eItemList::WEAPON_GIRDER:
		return "GirderOn";
		break;
	case eItemList::WEAPON_BASEBALLBAT:
		break;
	case eItemList::WEAPON_GIRDERSTARTERPACK:
		break;
	case eItemList::WEAPON_NINJAROPE:
		break;
	case eItemList::WEAPON_BUNGEE:
		break;
	case eItemList::WEAPON_PARACHUTE:
		break;
	case eItemList::WEAPON_TELEPORT:
		break;
	case eItemList::WEAPON_SCALESOFJUSTICE:
		break;
	case eItemList::WEAPON_SUPERBANANABOMB:
		break;
	case eItemList::WEAPON_HOLYHANDGRENDADE:
		break;
	case eItemList::WEAPON_FLAMETHROWER:
		break;
	case eItemList::WEAPON_SALVATIONARMY:
		break;
	case eItemList::WEAPON_MBBOMB:
		break;
	case eItemList::WEAPON_PETROLBOMB:
		break;
	case eItemList::WEAPON_SKUNK:
		break;
	case eItemList::WEAPON_PRICELESSMINGVASE:
		break;
	case eItemList::WEAPON_FRENCHSHEEPSTRIKE:
		break;
	case eItemList::WEAPON_MIKESCARPETBOMB:
		break;
	case eItemList::WEAPON_MADCOWS:
		break;
	case eItemList::WEAPON_OLDWOMAN:
		break;
	case eItemList::WEAPON_CONCREATEDONKEY:
		break;
	case eItemList::WEAPON_INDIANNUCLEAR:
		break;
	case eItemList::WEAPON_ARMAGEDDON:
		break;
	case eItemList::WEAPON_SKIPGO:
		break;
	case eItemList::WEAPON_SURRENDER:
		break;
	case eItemList::WEAPON_SELECTWORM:
		break;
	case eItemList::WEAPON_FREEZE:
		break;
	case eItemList::WEAPON_PATSYSMAGICBULLET:
		break;
	case eItemList::MAX:
		break;
	default:
		break;
	}

	return "";
}

void Worm::setAnimationWeaponOn()
{
	switch (currentWeapon_)
	{
	case eItemList::WEAPON_JETPACK:
		break;
	case eItemList::WEAPON_LOWGRAVITY:
		break;
	case eItemList::WEAPON_FASTWALK:
		break;
	case eItemList::WEAPON_LASERSIGHT:
		break;
	case eItemList::WEAPON_INVISIBILITY:
		break;
	case eItemList::WEAPON_BAZOOKA:
		if (bLeft_)
		{
			mainRender_->ChangeAnimation("BazOnLeft", std::string("bazOnLeft.bmp"));
		}
		else
		{
			mainRender_->ChangeAnimation("BazOnRight", std::string("bazOnRight.bmp"));
		}
		break;
	case eItemList::WEAPON_HOMINGMISSILE:
		if (bLeft_)
		{
			mainRender_->ChangeAnimation("HomingOnLeft", std::string("homingOnLeft.bmp"));
		}
		else
		{
			mainRender_->ChangeAnimation("HomingOnRight", std::string("homingOnRight.bmp"));
		}
		break;
	case eItemList::WEAPON_MORTAR:
		break;
	case eItemList::WEAPON_HOMINGPIGEON:
		break;
	case eItemList::WEAPON_SHEEPLAUNCHER:
		break;
	case eItemList::WEAPON_GRENADE:
		break;
	case eItemList::WEAPON_CLUSTERBOMB:
		break;
	case eItemList::WEAPON_BANNANABOMB:
		break;
	case eItemList::WEAPON_BATTLEAXE:
		if (bLeft_)
		{
			mainRender_->ChangeAnimation("BattleAxeOnLeft", std::string("axeOnLeft.bmp"));
		}
		else
		{
			mainRender_->ChangeAnimation("BattleAxeOnRight", std::string("axeOnRight.bmp"));
		}
		break;
	case eItemList::WEAPON_EARTHQUAKE:
		break;
	case eItemList::WEAPON_SHOTGUN:
		break;
	case eItemList::WEAPON_HANDGUN:
		break;
	case eItemList::WEAPON_UZI:
		if (bLeft_)
		{
			mainRender_->ChangeAnimation("UziOnLeft", std::string("uziOnLeft.bmp"));
		}
		else
		{
			mainRender_->ChangeAnimation("UziOnRight", std::string("uziOnRight.bmp"));
		}
		break;
	case eItemList::WEAPON_MINIGUN:
		break;
	case eItemList::WEAPON_LONGBOW:
		break;
	case eItemList::WEAPON_FIREPUNCH:
		if (bLeft_)
		{
			mainRender_->ChangeAnimation("FirepunchReadyLeft", std::string("firePunchReadyLeft.bmp"));
		}
		else
		{
			mainRender_->ChangeAnimation("FirepunchReadyRight", std::string("firePunchReadyRight.bmp"));
		}
		break;
	case eItemList::WEAPON_DRAGONBALL:
		break;
	case eItemList::WEAPON_KAMIKAZE:
		break;
	case eItemList::WEAPON_SUICIDEBOMBER:
		break;
	case eItemList::WEAPON_PROD:
		break;
	case eItemList::WEAPON_DYNAMITE:
		break;
	case eItemList::WEAPON_MINE:
		break;
	case eItemList::WEAPON_SHEEP:
		if (bLeft_)
		{
			mainRender_->ChangeAnimation("SheepOnLeft", std::string("sheepOnLeft.bmp"));
		}
		else
		{
			mainRender_->ChangeAnimation("SheepOnRight", std::string("sheepOnRight.bmp"));
		}
		break;
	case eItemList::WEAPON_SUPERSHEEP:
		if (bLeft_)
		{
			mainRender_->ChangeAnimation("SheepOnLeft", std::string("sheepOnLeft.bmp"));
		}
		else
		{
			mainRender_->ChangeAnimation("SheepOnRight", std::string("sheepOnRight.bmp"));
		}
		break;
	case eItemList::WEAPON_MOLEBOMB:
		break;
	case eItemList::WEAPON_AIRSTRIKE:
		break;
	case eItemList::WEAPON_NAPALMSTRIKE:
		break;
	case eItemList::WEAPON_MAILSTRIKE:
		break;
	case eItemList::WEAPON_MINESTRIKE:
		break;
	case eItemList::WEAPON_MOLESQUADRON:
		break;
	case eItemList::WEAPON_BLOWTORCH:
		crosshairRender_->Off();

		if (bLeft_)
		{
			mainRender_->ChangeAnimation("BlowtorchOnLeft", std::string("blowtorchOnLeft.bmp"));
		}
		else
		{
			mainRender_->ChangeAnimation("BlowtorchOnRight", std::string("blowtorchOnRight.bmp"));
		}
		break;
	case eItemList::WEAPON_PNEUMATICDRILL:
		crosshairRender_->Off();

		if (bLeft_)
		{
			mainRender_->ChangeAnimation("DrillOnLeft", std::string("drillOnLeft.bmp"));
		}
		else
		{
			mainRender_->ChangeAnimation("DrillOnRight", std::string("drillOnRight.bmp"));
		}
		break;
	case eItemList::WEAPON_GIRDER:
		crosshairRender_->Off();

		if (bLeft_)
		{
			mainRender_->ChangeAnimation("GirderOnLeft", std::string("girderOnLeft.bmp"));
		}
		else
		{
			mainRender_->ChangeAnimation("GirderOnRight", std::string("girderOnRight.bmp"));
		}
		break;
	case eItemList::WEAPON_BASEBALLBAT:
		break;
	case eItemList::WEAPON_GIRDERSTARTERPACK:
		break;
	case eItemList::WEAPON_NINJAROPE:
		break;
	case eItemList::WEAPON_BUNGEE:
		break;
	case eItemList::WEAPON_PARACHUTE:
		break;
	case eItemList::WEAPON_TELEPORT:
		break;
	case eItemList::WEAPON_SCALESOFJUSTICE:
		break;
	case eItemList::WEAPON_SUPERBANANABOMB:
		break;
	case eItemList::WEAPON_HOLYHANDGRENDADE:
		break;
	case eItemList::WEAPON_FLAMETHROWER:
		break;
	case eItemList::WEAPON_SALVATIONARMY:
		break;
	case eItemList::WEAPON_MBBOMB:
		break;
	case eItemList::WEAPON_PETROLBOMB:
		break;
	case eItemList::WEAPON_SKUNK:
		break;
	case eItemList::WEAPON_PRICELESSMINGVASE:
		break;
	case eItemList::WEAPON_FRENCHSHEEPSTRIKE:
		break;
	case eItemList::WEAPON_MIKESCARPETBOMB:
		break;
	case eItemList::WEAPON_MADCOWS:
		break;
	case eItemList::WEAPON_OLDWOMAN:
		break;
	case eItemList::WEAPON_CONCREATEDONKEY:
		break;
	case eItemList::WEAPON_INDIANNUCLEAR:
		break;
	case eItemList::WEAPON_ARMAGEDDON:
		break;
	case eItemList::WEAPON_SKIPGO:
		break;
	case eItemList::WEAPON_SURRENDER:
		break;
	case eItemList::WEAPON_SELECTWORM:
		break;
	case eItemList::WEAPON_FREEZE:
		break;
	case eItemList::WEAPON_PATSYSMAGICBULLET:
		break;
	case eItemList::MAX:
		break;
	default:
		break;
	}
}

void Worm::setAnimationWeaponOff()
{
	switch (currentWeapon_)
	{
	case eItemList::WEAPON_JETPACK:
		break;
	case eItemList::WEAPON_LOWGRAVITY:
		break;
	case eItemList::WEAPON_FASTWALK:
		break;
	case eItemList::WEAPON_LASERSIGHT:
		break;
	case eItemList::WEAPON_INVISIBILITY:
		break;
	case eItemList::WEAPON_BAZOOKA:
		if (bLeft_)
		{
			mainRender_->ChangeAnimation("BazOffLeft", std::string("bazOffLeft.bmp"));
		}
		else
		{
			mainRender_->ChangeAnimation("BazOffRight", std::string("bazOffRight.bmp"));
		}
		break;
	case eItemList::WEAPON_HOMINGMISSILE:
		if (bLeft_)
		{
			mainRender_->ChangeAnimation("HomingOffLeft", std::string("homingOffLeft.bmp"));
		}
		else
		{
			mainRender_->ChangeAnimation("HomingOffRight", std::string("homingOffRight.bmp"));
		}
		break;
	case eItemList::WEAPON_MORTAR:
		break;
	case eItemList::WEAPON_HOMINGPIGEON:
		break;
	case eItemList::WEAPON_SHEEPLAUNCHER:
		break;
	case eItemList::WEAPON_GRENADE:
		break;
	case eItemList::WEAPON_CLUSTERBOMB:
		break;
	case eItemList::WEAPON_BANNANABOMB:
		break;
	case eItemList::WEAPON_BATTLEAXE:
		if (bLeft_)
		{
			mainRender_->ChangeAnimation("BattleAxeOffLeft", std::string("axeOffLeft.bmp"));
		}
		else
		{
			mainRender_->ChangeAnimation("BattleAxeOffRight", std::string("axeOffRight.bmp"));
		}
		break;
	case eItemList::WEAPON_EARTHQUAKE:
		break;
	case eItemList::WEAPON_SHOTGUN:
		break;
	case eItemList::WEAPON_HANDGUN:
		break;
	case eItemList::WEAPON_UZI:
		if (bLeft_)
		{
			mainRender_->ChangeAnimation("UziOffLeft", std::string("uziOffLeft.bmp"));
		}
		else
		{
			mainRender_->ChangeAnimation("UziOffRight", std::string("uziOffRight.bmp"));
		}
		break;
	case eItemList::WEAPON_MINIGUN:
		break;
	case eItemList::WEAPON_LONGBOW:
		break;
	case eItemList::WEAPON_FIREPUNCH:
		if (bLeft_)
		{
			mainRender_->ChangeAnimation("FirepunchOffLeft", std::string("firePunchOffLeft.bmp"));
		}
		else
		{
			mainRender_->ChangeAnimation("FirepunchOffRight", std::string("firePunchOffRight.bmp"));
		}
		break;
	case eItemList::WEAPON_DRAGONBALL:
		break;
	case eItemList::WEAPON_KAMIKAZE:
		break;
	case eItemList::WEAPON_SUICIDEBOMBER:
		break;
	case eItemList::WEAPON_PROD:
		break;
	case eItemList::WEAPON_DYNAMITE:
		break;
	case eItemList::WEAPON_MINE:
		break;
	case eItemList::WEAPON_SHEEP:
		if (bLeft_)
		{
			mainRender_->ChangeAnimation("SheepOffLeft", std::string("sheepOffLeft.bmp"));
		}
		else
		{
			mainRender_->ChangeAnimation("SheepOffRight", std::string("sheepOffRight.bmp"));
		}
		break;
	case eItemList::WEAPON_SUPERSHEEP:
		if (bLeft_)
		{
			mainRender_->ChangeAnimation("SheepOffLeft", std::string("sheepOffLeft.bmp"));
		}
		else
		{
			mainRender_->ChangeAnimation("SheepOffRight", std::string("sheepOffRight.bmp"));
		}
		break;
	case eItemList::WEAPON_MOLEBOMB:
		break;
	case eItemList::WEAPON_AIRSTRIKE:
		break;
	case eItemList::WEAPON_NAPALMSTRIKE:
		break;
	case eItemList::WEAPON_MAILSTRIKE:
		break;
	case eItemList::WEAPON_MINESTRIKE:
		break;
	case eItemList::WEAPON_MOLESQUADRON:
		break;
	case eItemList::WEAPON_BLOWTORCH:
		if (bLeft_)
		{
			mainRender_->ChangeAnimation("BlowtorchOffLeft", std::string("blowtorchOffLeft.bmp"));
		}
		else
		{
			mainRender_->ChangeAnimation("BlowtorchOffRight", std::string("blowtorchOffRight.bmp"));
		}
		break;
	case eItemList::WEAPON_PNEUMATICDRILL:
		if (bLeft_)
		{
			mainRender_->ChangeAnimation("DrillOffLeft", std::string("drillOffLeft.bmp"));
		}
		else
		{
			mainRender_->ChangeAnimation("DrillOffRight", std::string("drillOffRight.bmp"));
		}
		break;
	case eItemList::WEAPON_GIRDER:
		if (bLeft_)
		{
			mainRender_->ChangeAnimation("GirderOffLeft", std::string("girderOffLeft.bmp"));
		}
		else
		{
			mainRender_->ChangeAnimation("GirderOffRight", std::string("girderOffRight.bmp"));
		}
		break;
	case eItemList::WEAPON_BASEBALLBAT:
		break;
	case eItemList::WEAPON_GIRDERSTARTERPACK:
		break;
	case eItemList::WEAPON_NINJAROPE:
		break;
	case eItemList::WEAPON_BUNGEE:
		break;
	case eItemList::WEAPON_PARACHUTE:
		break;
	case eItemList::WEAPON_TELEPORT:
		break;
	case eItemList::WEAPON_SCALESOFJUSTICE:
		break;
	case eItemList::WEAPON_SUPERBANANABOMB:
		break;
	case eItemList::WEAPON_HOLYHANDGRENDADE:
		break;
	case eItemList::WEAPON_FLAMETHROWER:
		break;
	case eItemList::WEAPON_SALVATIONARMY:
		break;
	case eItemList::WEAPON_MBBOMB:
		break;
	case eItemList::WEAPON_PETROLBOMB:
		break;
	case eItemList::WEAPON_SKUNK:
		break;
	case eItemList::WEAPON_PRICELESSMINGVASE:
		break;
	case eItemList::WEAPON_FRENCHSHEEPSTRIKE:
		break;
	case eItemList::WEAPON_MIKESCARPETBOMB:
		break;
	case eItemList::WEAPON_MADCOWS:
		break;
	case eItemList::WEAPON_OLDWOMAN:
		break;
	case eItemList::WEAPON_CONCREATEDONKEY:
		break;
	case eItemList::WEAPON_INDIANNUCLEAR:
		break;
	case eItemList::WEAPON_ARMAGEDDON:
		break;
	case eItemList::WEAPON_SKIPGO:
		break;
	case eItemList::WEAPON_SURRENDER:
		break;
	case eItemList::WEAPON_SELECTWORM:
		break;
	case eItemList::WEAPON_FREEZE:
		break;
	case eItemList::WEAPON_PATSYSMAGICBULLET:
		break;
	case eItemList::MAX:
		break;
	default:
		break;
	}
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
	speed_.x = 0.0f;

	return StateInfo();
}

StateInfo Worm::updateIdle(StateInfo _state)
{
	addGravity();

	weaponEquipDelay_ += deltaTime_;

	if (true == bFocus_)
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
	}

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
	else
	{
		if (bLeft_)
		{
			mainRender_->ChangeAnimation("IdleLeft", std::string("idleLeft.bmp"));
		}
		else
		{
			mainRender_->ChangeAnimation("IdleRight", std::string("idleRight.bmp"));
		}
	}

	normalMove();

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
			if (nullptr == leftSideCollision_->CollisionGroupCheckOne(eCollisionGroup::MAP))
			{
				mainRender_->ChangeAnimation("WalkLeft", std::string("walkLeft.bmp"));
				bLeft_ = true;
				speed_.x = -MOVE_SPEED;
			}
			else
			{
				mainRender_->ChangeAnimation("IdleLeft", std::string("idleLeft.bmp"));
				speed_.x = 0.0f;
			}
		}
		else if (GameEngineInput::GetInst().IsPress("RightArrow"))
		{
			if (nullptr == rightSideCollision_->CollisionGroupCheckOne(eCollisionGroup::MAP))
			{
				mainRender_->ChangeAnimation("WalkRight", std::string("walkRight.bmp"));
				bLeft_ = false;
				speed_.x = MOVE_SPEED;
			}
			else
			{
				mainRender_->ChangeAnimation("IdleRight", std::string("idleRight.bmp"));
				speed_.x = 0.0f;
			}
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

	if (speed_.y >= 0.0f)
	{
		if (bLeft_)
		{
			mainRender_->ChangeAnimation("FlyDownLeft", std::string("flyDownLeft.bmp"));
		}
		else
		{
			mainRender_->ChangeAnimation("FlyDownRight", std::string("flyDownRight.bmp"));
		}
		if (nullptr != groundCheckCollision_->CollisionGroupCheckOne(eCollisionGroup::MAP))
		{
			speed_ = { 0.0f, 0.0f };
			return "Idle";
		}
	}

	
	if (nullptr != leftSideCollision_->CollisionGroupCheckOne(eCollisionGroup::MAP))
	{
		SetMove({ 3.0f, 0.0f });
		speed_.x *= -1.f;
	}
	
	if (nullptr != rightSideCollision_->CollisionGroupCheckOne(eCollisionGroup::MAP))
	{
		SetMove({ -3.0f, 0.0f });
		speed_.x *= 1.f;
	}

	if (speed_.y < 0 && nullptr != headCollision_->CollisionGroupCheckOne(eCollisionGroup::MAP))
	{
		SetMove({ 0.0f, 1.0f });
		speed_.y = 0.0f;
	}


	//SetMove(speed_ * deltaTime_);
	normalMove();
	return StateInfo();
}

StateInfo Worm::startBazookaAim(StateInfo _state)
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

StateInfo Worm::updateBazookaAim(StateInfo _state)
{
	addGravity();

	if (false == bFocus_)
	{
		return "WeaponOff";
	}

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

	if (GameEngineInput::GetInst().IsPress("Fire"))
	{
		return "BazookaFire";
	}

	normalMove();

	return StateInfo();
}

StateInfo Worm::startBazookaFire(StateInfo _state)
{
	firePower_ = 100.0f;
	return StateInfo();
}

StateInfo Worm::updateBazookaFire(StateInfo _state)
{
	if (GameEngineInput::GetInst().IsUp("Fire"))
	{
		Bazooka* newBaz = parentLevel_->CreateActor<Bazooka>();
		newBaz->SetPos(pos_ + float4(forward_ * 20.f));
		newBaz->SetBazooka(forward_, firePower_);
		//bFocus_ = false;
		return "BazookaWait";
	}

	if (GameEngineInput::GetInst().IsPress("Fire"))
	{
		firePower_ += deltaTime_ * 500.f;

		if (firePower_ > 1000.f)
		{
			Bazooka* newBaz = parentLevel_->CreateActor<Bazooka>();
			newBaz->SetPos(pos_ + float4(forward_ * 20.f));
			newBaz->SetBazooka(forward_, firePower_);
			//bFocus_ = false;
			return "BazookaWait";
		}
	}

	return StateInfo();
}

StateInfo Worm::startBazookaWait(StateInfo _state)
{
	return StateInfo();
}

StateInfo Worm::updateBazookaWait(StateInfo _state)
{
	nextState_ = "Idle";
	return "WeaponOff";
}

StateInfo Worm::startHomingStart(StateInfo _state)
{
	// 마우스 커서 생성
	// ShowCursor(false);

	return StateInfo();
}

StateInfo Worm::updateHomingStart(StateInfo _state)
{
	// 마우스 포지션 클릭
	// 마우스 이미지 x로 변경
	// 마우스 이동 불가

	if (GameEngineInput::GetInst().IsDown("Mouse"))
	{
		MouseObject* mouse = (MouseObject*)GetLevel()->FindActor("PlayLevelMouse");
			
		float4 MousePos = mouse->GetPos() + mouse->GetGameController()->GetCameraPos();

		mouseTargetPos_ = MousePos;

		GameEngineSoundManager::GetInstance().PlaySoundByName("CursorSelect.wav");

		mouse->MouseBlock(true);

		return "HomingAim";
	}

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

	if (GameEngineInput::GetInst().IsPress("Fire"))
	{
		return "BazookaFire";
	}

	normalMove();
	return StateInfo();
}

StateInfo Worm::startHomingAim(StateInfo _state)
{
	if (bLeft_)
	{
		mainRender_->ChangeAnimation("HomingAimLeft", std::string("homingAimLeft.bmp"));
	}
	else
	{
		mainRender_->ChangeAnimation("HomingAimRight", std::string("homingAimRight.bmp"));
	}

	int frame = getAimingFrame();
	mainRender_->SetAnimationCurrentFrame(frame);
	setAimingForward();
	crosshairRender_->On();
	crosshairRender_->SetPivotPos(forward_ * 50.f);
	return StateInfo();
}

StateInfo Worm::updateHomingAim(StateInfo _state)
{
	addGravity();

	if (false == bFocus_)
	{
		return "WeaponOff";
	}

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

	MouseObject* mouse = (MouseObject*)GetLevel()->FindActor("PlayLevelMouse");

	if (GameEngineInput::GetInst().IsPress("LeftArrow"))
	{
		mouse->MouseBlock(false);
		bLeft_ = true;
		nextState_ = "Walk";
		return "WeaponOff";
	}

	if (GameEngineInput::GetInst().IsPress("RightArrow"))
	{
		mouse->MouseBlock(false);
		bLeft_ = false;
		nextState_ = "Walk";
		return "WeaponOff";
	}

	if (GameEngineInput::GetInst().IsDown("Jump"))
	{
		mouse->MouseBlock(false);
		nextState_ = "JumpReady";
		return "WeaponOff";
	}

	if (GameEngineInput::GetInst().IsPress("Fire"))
	{
		return "HomingFire";
	}

	normalMove();

	return StateInfo();
}

StateInfo Worm::startHomingFire(StateInfo _state)
{
	firePower_ = 100.0f;
	return StateInfo();
}

StateInfo Worm::updateHomingFire(StateInfo _state)
{
	if (GameEngineInput::GetInst().IsUp("Fire"))
	{
		HomingMissile* newHom = parentLevel_->CreateActor<HomingMissile>();
		newHom->SetPos(pos_ + float4(forward_ * 20.f));
		newHom->SetPower(forward_, firePower_);
		newHom->SetHomingPoint(mouseTargetPos_);
		//bFocus_ = false;
		return "HomingWait";
	}

	if (GameEngineInput::GetInst().IsPress("Fire"))
	{
		firePower_ += deltaTime_ * 500.f;

		if (firePower_ > 1000.f)
		{
			HomingMissile* newHom = parentLevel_->CreateActor<HomingMissile>();
			newHom->SetPos(pos_ + float4(forward_ * 20.f));
			newHom->SetPower(forward_, firePower_);
			newHom->SetHomingPoint(mouseTargetPos_);
			//bFocus_ = false;
			return "HomingWait";
		}
	}

	return StateInfo();
}

StateInfo Worm::startHomingWait(StateInfo _state)
{
	return StateInfo();
}

StateInfo Worm::updateHomingWait(StateInfo _state)
{
	nextState_ = "Idle";
	return "WeaponOff";
}


StateInfo Worm::startFirepunchReady(StateInfo _state)
{
	if (bLeft_)
	{
		mainRender_->ChangeAnimation("FirepunchReadyLeft", std::string("firePunchReadyLeft.bmp"));
	}
	else
	{
		mainRender_->ChangeAnimation("FirepunchReadyRight", std::string("firePunchReadyRight.bmp"));
	}
	return StateInfo();
}

StateInfo Worm::updateFirepunchReady(StateInfo _state)
{
	addGravity();
	crosshairRender_->Off();
	if (false == bFocus_)
	{
		return "WeaponOff";
	}

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

	if (GameEngineInput::GetInst().IsDown("Fire"))
	{
		return "FirepunchStart";
	}

	normalMove();

	return StateInfo();
}

StateInfo Worm::startFirepunchStart(StateInfo _state)
{
	if (bLeft_)
	{
		mainRender_->ChangeAnimation("FirepunchStartLeft", std::string("firePunchStartLeft.bmp"));
	}
	else
	{
		mainRender_->ChangeAnimation("FirepunchStartRight", std::string("firePunchStartRight.bmp"));
	}
	return StateInfo();
}

StateInfo Worm::updateFirepunchStart(StateInfo _state)
{
	// 점프 하는거부터...
	if (bLeft_)
	{
		//FirePunch* firePunch = parentLevel_->CreateActor<FirePunch>();
		//firePunch->SetPos(GetPos());
		if (true == mainRender_->IsCurAnimationEnd())
		{
			mainRender_->ChangeAnimation("FirepunchFlyLeft", std::string("firePunchFlyLeft.bmp"));
			return "FirepunchFly";
		}

	}
	else
	{
	//	FirePunch* firePunch = parentLevel_->CreateActor<FirePunch>();
	//	firePunch->SetPos(GetPos());
		if (true == mainRender_->IsCurAnimationEnd())
		{
			mainRender_->ChangeAnimation("FirepunchFlyRight", std::string("firePunchFlyRight.bmp"));
			return "FirepunchFly";
		}
	}
	return StateInfo();
}

StateInfo Worm::startFirepunchFly(StateInfo _state)
{
	if (bLeft_)
	{
		speed_.x = -JUMP_POWER/2;
		speed_.y = -JUMP_POWER*2.0f;
		SetMove({ 0.0f, -6.f });
	}
	else
	{
		speed_.x = JUMP_POWER/2;
		speed_.y = -JUMP_POWER*2.0f;
		SetMove({ 0.0f, -6.f });
	}

	return StateInfo();
}

StateInfo Worm::updateFirepunchFly(StateInfo _state)
{
	addGravity();

	if (speed_.y > 0.0f)
	{
		if (bLeft_)
		{
			mainRender_->ChangeAnimation("FirepunchEndLeft", std::string("firePunchEndLeft.bmp"));
			return "FirepunchEnd";
		}
		else
		{
			mainRender_->ChangeAnimation("FirepunchEndRight", std::string("firePunchEndRight.bmp"));
			return "FirepunchEnd";
		}
		if (nullptr != groundCheckCollision_->CollisionGroupCheckOne(eCollisionGroup::MAP))
		{
			speed_ = { 0.0f, 0.0f };
			return "Idle";
		}
	}


	if (nullptr != leftSideCollision_->CollisionGroupCheckOne(eCollisionGroup::MAP))
	{
		SetMove({ 3.0f, 0.0f });
		speed_.x *= -1.f;
	}

	if (nullptr != rightSideCollision_->CollisionGroupCheckOne(eCollisionGroup::MAP))
	{
		SetMove({ -3.0f, 0.0f });
		speed_.x *= 1.f;
	}

	if (speed_.y < 0 && nullptr != headCollision_->CollisionGroupCheckOne(eCollisionGroup::MAP))
	{
		SetMove({ 0.0f, 1.0f });
		speed_.y = 0.0f;
	}

	//SetMove(speed_ * deltaTime_);
	normalMove();
	return StateInfo();
}

StateInfo Worm::startFirepunchEnd(StateInfo _state)
{
	addGravity();
	return StateInfo();
}

StateInfo Worm::updateFirepunchEnd(StateInfo _state)
{
	addGravity();
	// 떨어지는 중
	if (nullptr != groundCheckCollision_->CollisionGroupCheckOne(eCollisionGroup::MAP))
	{
		speed_.x = 0.0f;
		if (bLeft_)
		{
			mainRender_->ChangeAnimation("FirepunchLandLeft", std::string("firePunchLandLeft.bmp"));
			return "FirepunchLand";
		}
		else
		{
			mainRender_->ChangeAnimation("FirepunchLandRight", std::string("firePunchLandRight.bmp"));
			return "FirepunchLand";
		}
	}
	else
	{
	}

	normalMove();

	return StateInfo();
}

StateInfo Worm::startFirepunchLand(StateInfo _state)
{
	return StateInfo();
}
StateInfo Worm::updateFirepunchLand(StateInfo _state)
{
	if (bLeft_)
	{
		mainRender_->ChangeAnimation("FirepunchOffLeft", std::string("firePunchOffLeft.bmp"));
		return "FirepunchOff";
	}
	else
	{
		mainRender_->ChangeAnimation("FirepunchOffRight", std::string("firePunchOffRight.bmp"));
		return "FirepunchOff";
	}
	return StateInfo();
}

StateInfo Worm::startFirepunchOff(StateInfo _state)
{
	return StateInfo();
}

StateInfo Worm::updateFirepunchOff(StateInfo _state)
{
	if (mainRender_->IsCurAnimationEnd() == true)
	{
		nextState_ = "Idle";
		return "WeaponOff";
	}

	return StateInfo();
}


StateInfo Worm::startUziAim(StateInfo _state)
{
	if (bLeft_)
	{
		mainRender_->ChangeAnimation("UziAimLeft", std::string("uziAimLeft.bmp"));
	}
	else
	{
		mainRender_->ChangeAnimation("UziAimRight", std::string("uziAimRight.bmp"));
	}

	int frame = getAimingFrame();
	mainRender_->SetAnimationCurrentFrame(frame);
	setAimingForward();
	crosshairRender_->On();
	crosshairRender_->SetPivotPos(forward_ * 50.f);
	return StateInfo();
}


StateInfo Worm::updateUziAim(StateInfo _state)
{
	addGravity();

	if (false == bFocus_)
	{
		return "WeaponOff";
	}

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

	if (GameEngineInput::GetInst().IsDown("Fire"))
	{
		return "UziFire";
	}

	normalMove();

	return StateInfo();
}

StateInfo Worm::startUziFire(StateInfo _state)
{
	if (bLeft_)
	{
		mainRender_->ChangeAnimation("UziFireLeft", std::string("uziFireLeft.bmp"));
		Uzi* newUzi = parentLevel_->CreateActor<Uzi>();
		newUzi->SetParentWorm(this);
		newUzi->SetPos(pos_ + float4(forward_ * 20.f));
		newUzi->SetUziBulletShotBox(forward_);
		return StateInfo();
	}
	else
	{
		mainRender_->ChangeAnimation("UziFireRight", std::string("uziFireRight.bmp"));
		Uzi* newUzi = parentLevel_->CreateActor<Uzi>();
		newUzi->SetParentWorm(this);
		newUzi->SetPos(pos_ + float4(forward_ * 20.f));
		newUzi->SetUziBulletShotBox(forward_);
		return StateInfo();
	}

}

StateInfo Worm::updateUziFire(StateInfo _state)
{
	mainRender_->ChangeAnimation("UziAimRight", std::string("uziAimRight.bmp"));
	return "UziWait";

	return StateInfo();
}

StateInfo Worm::startUziWait(StateInfo _state)
{
	return StateInfo();
}

StateInfo Worm::updateUziWait(StateInfo _state)
{
	nextState_ = "Idle";
	return "WeaponOff";
}

StateInfo Worm::startSheepAim(StateInfo _state)
{
	if (bLeft_)
	{
		mainRender_->ChangeAnimation("SheepAimLeft", std::string("sheepOnLeft.bmp"));
	}
	else
	{
		mainRender_->ChangeAnimation("SheepAimRight", std::string("sheepOnRight.bmp"));
	}
	crosshairRender_->Off();
	return StateInfo();
}

StateInfo Worm::updateSheepAim(StateInfo _state)
{
	addGravity();

	if (false == bFocus_)
	{
		return "WeaponOff";
	}

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

	if (GameEngineInput::GetInst().IsUp("Fire"))
	{
		return "SheepFire";
	}

	normalMove();
	return StateInfo();
}

StateInfo Worm::startSheepFire(StateInfo _state)
{
	return StateInfo();
}

StateInfo Worm::updateSheepFire(StateInfo _state)
{
	Sheep* newSheep = parentLevel_->CreateActor<Sheep>();
	newSheep->Initialize(this, bLeft_);
	newSheep->SetPos(pos_);
	BulletFocusOn(newSheep);
	return "SheepWait";
}

StateInfo Worm::startSheepWait(StateInfo _state)
{
	if (bLeft_)
	{
		mainRender_->ChangeAnimation("IdleLeft", std::string("idleLeft.bmp"));
	}
	else
	{
		mainRender_->ChangeAnimation("IdleRight", std::string("idleRight.bmp"));
	}
	return StateInfo();
}

StateInfo Worm::updateSheepWait(StateInfo _state)
{
	addGravity();
	normalMove();
	return StateInfo();
}

StateInfo Worm::startSuperSheepAim(StateInfo _state)
{
	if (bLeft_)
	{
		mainRender_->ChangeAnimation("SheepAimLeft", std::string("sheepOnLeft.bmp"));
	}
	else
	{
		mainRender_->ChangeAnimation("SheepAimRight", std::string("sheepOnRight.bmp"));
	}
	crosshairRender_->Off();
	return StateInfo();
}

StateInfo Worm::updateSuperSheepAim(StateInfo _state)
{
	addGravity();

	if (false == bFocus_)
	{
		return "WeaponOff";
	}

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

	if (GameEngineInput::GetInst().IsUp("Fire"))
	{
		return "SuperSheepFire";
	}

	normalMove();
	return StateInfo();
}

StateInfo Worm::startSuperSheepFire(StateInfo _state)
{
	return StateInfo();
}

StateInfo Worm::updateSuperSheepFire(StateInfo _state)
{
	SuperSheep* newSheep = parentLevel_->CreateActor<SuperSheep>();
	newSheep->Initialize(this, bLeft_);
	newSheep->SetPos(pos_);
	BulletFocusOn(newSheep);
	return "SuperSheepWait";
}

StateInfo Worm::startSuperSheepWait(StateInfo _state)
{
	if (bLeft_)
	{
		mainRender_->ChangeAnimation("IdleLeft", std::string("idleLeft.bmp"));
	}
	else
	{
		mainRender_->ChangeAnimation("IdleRight", std::string("idleRight.bmp"));
	}
	return StateInfo();
}

StateInfo Worm::updateSuperSheepWait(StateInfo _state)
{
	addGravity();
	normalMove();
	return StateInfo();
}

StateInfo Worm::startBattleAxeOn(StateInfo _state)
{
	if (bLeft_)
	{
		mainRender_->ChangeAnimation("BattleAxeOnLeft", std::string("axeOnLeft.bmp"));
	}
	else
	{
		mainRender_->ChangeAnimation("BattleAxeOnRight", std::string("axeOnRight.bmp"));
	}
	return StateInfo();
}
StateInfo Worm::updateBattleAxeOn(StateInfo _state)
{
	addGravity();

	if (false == bFocus_)
	{
		return "WeaponOff";
	}

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

	if (GameEngineInput::GetInst().IsDown("Fire"))
	{
		return "BattleAxeFire1";
	}

	normalMove();
	return StateInfo();
}
StateInfo Worm::startBattleAxeFire1(StateInfo _state)
{
	if (bLeft_)
	{
		// 배틀액스 피격박스 액터 생성은 여기다 해 주세요.
		mainRender_->ChangeAnimation("BattleAxeFire1Left", std::string("axeFire1Left.bmp"));
	}
	else
	{
		// 배틀액스 피격박스 액터 생성은 여기다 해 주세요.
		mainRender_->ChangeAnimation("BattleAxeFire1Right", std::string("axeFire1Right.bmp"));
	}
	return StateInfo();
}
StateInfo Worm::updateBattleAxeFire1(StateInfo _state)
{
	if (true == mainRender_->IsCurAnimationEnd())
	{
		return "BattleAxeFire2";
	}
	return StateInfo();
}
StateInfo Worm::startBattleAxeFire2(StateInfo _state)
{
	if (bLeft_)
	{
		mainRender_->ChangeAnimation("BattleAxeFire2Left", std::string("axeFire2Left.bmp"));
	}
	else
	{
		mainRender_->ChangeAnimation("BattleAxeFire2Right", std::string("axeFire2Right.bmp"));
	}
	return StateInfo();
}
StateInfo Worm::updateBattleAxeFire2(StateInfo _state)
{
	if (true == mainRender_->IsCurAnimationEnd())
	{
		return "BattleAxeFire3";
	}
	return StateInfo();
}
StateInfo Worm::startBattleAxeFire3(StateInfo _state)
{
	if (bLeft_)
	{
		mainRender_->ChangeAnimation("BattleAxeFire3Left", std::string("axeFire3Left.bmp"));
	}
	else
	{
		mainRender_->ChangeAnimation("BattleAxeFire3Right", std::string("axeFire3Right.bmp"));
	}
	return StateInfo();
}
StateInfo Worm::updateBattleAxeFire3(StateInfo _state)
{
	if (true == mainRender_->IsCurAnimationEnd())
	{
		return "BattleAxeOff";
	}
	return StateInfo();
}
StateInfo Worm::startBattleAxeOff(StateInfo _state)
{
	if (bLeft_)
	{
		mainRender_->ChangeAnimation("BattleAxeOffLeft", std::string("axeOffLeft.bmp"));
	}
	else
	{
		mainRender_->ChangeAnimation("BattleAxeOffRight", std::string("axeOffRight.bmp"));
	}
	return StateInfo();
}
StateInfo Worm::updateBattleAxeOff(StateInfo _state)
{
	if (true == mainRender_->IsCurAnimationEnd())
	{
		return "BattleAxeWait";
	}
	return StateInfo();
}
StateInfo Worm::startBattleAxeWait(StateInfo _state)
{
//	if (bLeft_)
//	{
//		mainRender_->ChangeAnimation("IdleLeft", std::string("idleLeft.bmp"));
//	}
//	else
//	{
//		mainRender_->ChangeAnimation("IdleRight", std::string("idleRight.bmp"));
//	}
	return StateInfo();
}
StateInfo Worm::updateBattleAxeWait(StateInfo _state)
{
	nextState_ = "Idle";
	return "WeaponOff";
}
StateInfo Worm::startGirderOn(StateInfo _state)
{
	Girder* newGirder = parentLevel_->CreateActor<Girder>();
	newGirder->Initialize(this, bLeft_);
	crosshairRender_->Off();

	return StateInfo();
}

StateInfo Worm::updateGirderOn(StateInfo _state)
{
	return StateInfo();
}

StateInfo Worm::startBlowtorchOn(StateInfo _state)
{
	return StateInfo();
}

StateInfo Worm::updateBlowtorchOn(StateInfo _state)
{
	addGravity();

	if (false == bFocus_)
	{
		return "WeaponOff";
	}

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

	if (GameEngineInput::GetInst().IsDown("Fire"))
	{
		GameEngineSoundManager::GetInstance().PlaySoundByName("BlowTorch.wav");
		soundWhoosh_.ChangeSound("BlowTorch.wav");
		soundWhoosh_.Play();

		return "BlowtorchFire";
	}

	normalMove();

	return StateInfo();
}

StateInfo Worm::startBlowtorchFire(StateInfo _state)
{
	if (bLeft_)
	{
		mainRender_->ChangeAnimation("BlowtorchFireLeft", std::string("blowtorchFireLeft.bmp"));
	}
	else
	{
		mainRender_->ChangeAnimation("BlowtorchFireRight", std::string("blowtorchFireRight.bmp"));
	}
	return StateInfo();
}

StateInfo Worm::updateBlowtorchFire(StateInfo _state)
{
	addGravity();

	blowTorchMoveTime_ -= deltaTime_;

	PlayLevel* level = (PlayLevel*)GetLevel(); 
	level->GetMap()->GroundUpdate(float4(pos_.x - 15.f, pos_.y - 13.f), float4(30.f, 30.f));

	if (bLeft_)
	{
		level->GetMap()->GroundUpdate(float4(pos_.x - 30.f, pos_.y - 13.f), float4(30.f, 30.f));
		SetMove(float4::LEFT * 0.5f);
	}
	else
	{
		level->GetMap()->GroundUpdate(float4(pos_.x, pos_.y - 13.f), float4(30.f, 30.f));
		SetMove(float4::RIGHT * 0.5f);
	}

	if (soundWhoosh_.GetPositionMillisecond() >= soundWhoosh_.GetLengthMillisecond())
	{
		soundWhoosh_.Play();
		soundWhoosh_.SetPosition(150);
	}

	if (blowTorchMoveTime_ <= 0.f)
	{
		soundWhoosh_.Stop();
		blowTorchMoveTime_ = 3.0f;
		setAnimationWeaponOff();
		return "Idle";
	}

	normalMove();

	return StateInfo();
}

StateInfo Worm::startDrillOn(StateInfo _state)
{
	return StateInfo();
}

StateInfo Worm::updateDrillOn(StateInfo _state)
{
	addGravity();

	if (false == bFocus_)
	{
		return "WeaponOff";
	}

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

	if (GameEngineInput::GetInst().IsDown("Fire"))
	{
		GameEngineSoundManager::GetInstance().PlaySoundByName("DRILL.WAV");
		soundWhoosh_.ChangeSound("DRILL.WAV");
		soundWhoosh_.Play();

		return "DrillFire";
	}

	normalMove();

	return StateInfo();
}

StateInfo Worm::startDrillFire(StateInfo _state)
{
	if (bLeft_)
	{
		mainRender_->ChangeAnimation("DrillLeft", std::string("drillLeft.bmp"));
	}
	else
	{
		mainRender_->ChangeAnimation("DrillRight", std::string("drillRight.bmp"));
	}
	return StateInfo();
}

StateInfo Worm::updateDrillFire(StateInfo _state)
{
	addGravity();

	blowTorchMoveTime_ -= deltaTime_;

	PlayLevel* level = (PlayLevel*)GetLevel();

	drillMoveTime_ -= deltaTime_;

	if (soundWhoosh_.GetPositionMillisecond() >= soundWhoosh_.GetLengthMillisecond())
	{
		soundWhoosh_.Play();
		soundWhoosh_.SetPosition(150);
	}

	if (drillMoveTime_ <= 0.f)
	{
		level->GetMap()->GroundUpdate(float4(pos_.x - 15.f, pos_.y - 4.f), float4(30.f, 30.f));
		drillMoveTime_ = 0.3f;
	}

	if (blowTorchMoveTime_ <= 0.f)
	{
		soundWhoosh_.Stop();
		blowTorchMoveTime_ = 3.0f;
		setAnimationWeaponOff();
		return "Idle";
	}

	normalMove();

	return StateInfo();
}


void Worm::SetCurWeapon(eItemList _WeaponType)
{
	// 현재무기를 무기창에서 선택한 무기로 변경하고,
	currentWeapon_ = _WeaponType;

	// 현재 상태 변경
	ChangeState("WeaponOn");
}

void Worm::SetUIController(UIController* _uicontroller)
{
	uicontroller_ = _uicontroller;
}

UIController* Worm::GetCurUIController() const
{
	return uicontroller_;
}

void Worm::Damage(int _numDamage)
{
	hp_ -= _numDamage;

	if (hp_ < 0)
	{
		hp_ = 0;
	}
}

bool Worm::IsDie() const
{
	return hp_ <= 0;
}

void Worm::AddActionToken(int _numToken)
{
	actionToken_ += _numToken;
}

void Worm::SubtractActionToken(int _numToken)
{
	actionToken_ -= _numToken;

	if (actionToken_ < 0)
	{
		actionToken_ = 0;
	}
}

void Worm::ClearActionToken()
{
	actionToken_ = 0;
}

int Worm::GetActionTokenCount() const
{
	return actionToken_;
}

float4 Worm::GetForward() const
{
	return forward_;
}

void Worm::BulletFocusOn(GameEngineActor* _actor)
{
	bulletFocusActor_ = _actor;
}

void Worm::BulletFocusOff()
{
	bulletFocusActor_ = nullptr;
}

void Worm::SetFocus(bool _bFocus)
{
	bFocus_ = _bFocus;
	state_.ChangeState("Idle");
}

StateInfo Worm::startWeaponOn(StateInfo _state)
{
	setAnimationWeaponOn();
	return StateInfo();
}

StateInfo Worm::updateWeaponOn(StateInfo _state)
{
	if (mainRender_->IsCurAnimationEnd())
	{
		return getWeaponAimState();
	}

	return StateInfo();
}

StateInfo Worm::startWeaponOff(StateInfo _state)
{
	setAnimationWeaponOff();
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
	if (nullptr != bulletFocusActor_)
	{
		GetLevel()->SetCamPos(bulletFocusActor_->GetPos() - GameEngineWindow::GetInst().GetSize().halffloat4());

	}
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
	//leftSideCollision_->DebugRender();
	//rightSideCollision_->DebugRender();
	//headCollision_->DebugRender();
}

void Worm::ChangeState(std::string _stateName)
{
	state_.ChangeState(_stateName);
}

bool Worm::isFocused()
{
	return bFocus_;
}