// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Reverotor_Framework/Weapon/SpecialAttacks/SpecialAttackBase.h"
#include "MeleeGeneralSet_PDA.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EMeleeAttackType : uint8
{
	Red,
	White,
	Black,
	Pale
};

USTRUCT(BlueprintType)
struct FMeleeDamageRange
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Range")
	float Min;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Range")
	float Max;

	FMeleeDamageRange()
		: Min(0.0f), Max(0.0f)
	{}

	FMeleeDamageRange(float InMin, float InMax)
		: Min(InMin), Max(InMax)
	{}

	bool IsInRange(float Value) const
	{
		return Value >= Min && Value <= Max;
	}
};

USTRUCT(BlueprintType)
struct FMeleeWeaponData
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon|General", DisplayName = "Abnormality")
	FString Abnormality;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon|General", DisplayName = "Name")
	FString Name;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon|General", DisplayName = "Skeletal Mesh")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon|General", DisplayName = "Attack Type")
	TArray<EMeleeAttackType> AttackType;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon|General", DisplayName = "Damage Ranges")
	FMeleeDamageRange DamageRanges;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon|General", DisplayName = "Attack Range")
	float AttackRange;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon|General", DisplayName = "Attack Speed")
	float AttackSpeed;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon|Special Attack")
	bool bHasSpecialAttack;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon|Special Attack", meta = (EditCondition = "bHasSpecialAttack", EditConditionHides), DisplayName = "Special Attack")
	TSubclassOf<USpecialAttackBase> SpecialAttack;
};

UCLASS(Blueprintable, BlueprintType)
class REVEROTOR_API UMeleeGeneralSet_PDA : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Melee Data")
	FName AssetName;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Melee Data")
	FMeleeWeaponData RangedData;
};
