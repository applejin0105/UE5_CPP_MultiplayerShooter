// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SpecialAttackBase.generated.h"

UCLASS(Blueprintable, Abstract)
class REVEROTOR_API USpecialAttackBase : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Special Attack")
	void ExecuteSpecialAttack(AActor* Target);

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Special Attack")
	FString AttackName;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Special Attack")
	float Chance;
};
