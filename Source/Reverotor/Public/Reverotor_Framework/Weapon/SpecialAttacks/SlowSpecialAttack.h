// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpecialAttackBase.h"
#include "SlowSpecialAttack.generated.h"

UCLASS()
class REVEROTOR_API USlowSpecialAttack : public USpecialAttackBase
{
	GENERATED_BODY()

public:
	virtual void ExecuteSpecialAttack_Implementation(AActor* Target) override;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Special Attack|Slow")
	float SlowSpeed;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Special Attack|Slow")
	float Duration;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Special Attack|Slow")
	float CoolDown;
};
