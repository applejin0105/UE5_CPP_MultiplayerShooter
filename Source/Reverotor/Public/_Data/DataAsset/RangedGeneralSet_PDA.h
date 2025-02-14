// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Reverotor_Framework/Weapon/Bullet.h"
#include "Reverotor_Framework/Weapon/SpecialAttacks/SpecialAttackBase.h"
#include "RangedGeneralSet_PDA.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ERangedType : uint8
{
	Rifle UMETA(DisplayName = "Rifle"),
	HandGun UMETA(DisplayName = "HandGun"),
	ShotGun UMETA(DisplayName = "ShotGun"),
	Sniper UMETA(DisplayName = "Sniper"),
	ChargeRifle UMETA(DisplayName = "ChargeRifle"),
};

UENUM(BlueprintType)
enum class ERangedFireMode : uint8
{
	HitScan UMETA(DisplayName = "HitScan"),
	Projectile UMETA(DisplayName = "Projectile")
};

UENUM(BlueprintType)
enum class ERangedScope : uint8
{
	None UMETA(DisplayName = "None"),
	Exist UMETA(DisplayName = "Exist")
};

UENUM(BlueprintType)
enum class ERangedAttackType : uint8
{
	Red,
	White,
	Black,
	Pale
};

USTRUCT(BlueprintType)
struct FRangedDamageRange
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Range")
	float Min;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Range")
	float Max;

	FRangedDamageRange()
		: Min(0.0f), Max(0.0f)
	{}

	FRangedDamageRange(float InMin, float InMax)
		: Min(InMin), Max(InMax)
	{}

	bool IsInRange(float Value) const
	{
		return Value >= Min && Value <= Max;
	}
};

USTRUCT(BlueprintType)
struct FRangedWeaponData
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon|General", DisplayName = "Abnormality")
	FString Abnormality;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon|General", DisplayName = "Name")
	FString Name;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon|General", DisplayName = "Skeletal Mesh")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon|General", DisplayName = "Attack Type")
	TArray<ERangedAttackType> AttackType;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon|General", DisplayName = "Type")
	ERangedType RangedType;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon|General", DisplayName = "Fire Mode")
	ERangedFireMode RangedFireMode;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon|General", DisplayName = "Crosshair")
	TSoftObjectPtr<UTexture2D> Crosshair;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon|General", DisplayName = "Does the scope exist?")
	ERangedScope RangedScope;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon|General", meta = (EditCondition = "RangedScope == ERangedScope::Exist", EditConditionHides), DisplayName = "Scope Image")
	TSoftObjectPtr<UTexture2D> Scope;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon|General", DisplayName = "Bullet Spread")
	float BulletSpread;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon|General", DisplayName = "Bullet Spread Zoom In")
	float BulletSpreadZoomIn;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon|General", meta = (EditCondition = "RangedType != ERangedType::ChargeRifle", EditConditionHides), DisplayName = "Fire Rate")
	float FireRate;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon|General", meta = (EditCondition = "RangedType == ERangedType::ChargeRifle", EditConditionHides), DisplayName = "Charge Time")
	float ChargeTime;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon|General", DisplayName = "Max Ammo")
	float MaxAmmo;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon|General", DisplayName = "Max Mag")
	float MaxMag;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon|General", DisplayName = "Damage Ranges")
	FRangedDamageRange DamageRanges;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon|General", DisplayName = "Scope Zoom Rate")
	float ScopeZoomRate;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon|Projectile|Bullet", meta = (EditCondition = "FireMode == ERangedFireMode::Projectile", EditConditionHides), DisplayName = "Bullet Object")
	TSubclassOf<ABullet> Bullet;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon|Projectile|Bullet", meta = (EditCondition = "FireMode == ERangedFireMode::Projectile", EditConditionHides), DisplayName = "Bullet Case Object")
	TSubclassOf<ABullet> BulletCase;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon|Projectile|Bullet", meta = (EditCondition = "FireMode == ERangedFireMode::Projectile", EditConditionHides), DisplayName = "Bullet Speed")
	float BulletSpeed;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon|Sound", DisplayName = "Fire Sound")
	TSoftObjectPtr<USoundBase> FireSound;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon|Sound", DisplayName = "Bullet Case Sound")
	TSoftObjectPtr<USoundBase> BulletCaseSound;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon|Sound", DisplayName = "Reload Sound")
	TSoftObjectPtr<USoundBase> ReloadSound;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon|Sound", meta = (EditCondition = "RangedType == ERangedType::ChargeRifle", EditConditionHides), DisplayName = "Charge Sound")
	TSoftObjectPtr<USoundBase> ChargeSound;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon|Animation", DisplayName = "Idle Animation")
	TSoftObjectPtr<UAnimMontage> IdleAnimation;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon|Animation", DisplayName = "Crouch Animation")
	TSoftObjectPtr<UAnimMontage> CrouchAnimation;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon|Animation", DisplayName = "Jump Animation")
	TSoftObjectPtr<UAnimMontage> JumpAnimation;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon|Animation", DisplayName = "Aim Animation")
	TSoftObjectPtr<UAnimMontage> AimAnimation;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon|Animation", DisplayName = "Aim Walking Animation")
	TSoftObjectPtr<UAnimMontage> AimWalkingAnimation;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon|Animation", DisplayName = "Run Animation")
	TSoftObjectPtr<UAnimMontage> RunAnimation;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon|Animation", meta = (EditCondition = "RangedType == ERangedType::ChargeRifle", EditConditionHides), DisplayName = "Charge Animation")
	TSoftObjectPtr<UAnimMontage> ChargeAnimation;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon|Special Attack")
	bool bHasSpecialAttack;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon|Special Attack", meta = (EditCondition = "bHasSpecialAttack", EditConditionHides), DisplayName = "Special Attack")
	TSubclassOf<USpecialAttackBase> SpecialAttack;
};

UCLASS(Blueprintable, BlueprintType)
class REVEROTOR_API URangedGeneralSet_PDA : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Ranged Data")
	FName AssetName;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Ranged Data")
	FRangedWeaponData RangedData;
};
