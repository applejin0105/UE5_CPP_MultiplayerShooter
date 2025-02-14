// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MainScreenInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UMainScreenInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class REVEROTOR_API IMainScreenInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="MainScreen|HP")
	void SetCurrentHP(float CurrentHP);
	virtual void SetCurrentHP_Implementation(float CurrentHP) PURE_VIRTUAL(IMainScreenInterface::SetCurrentHP,)

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="MainScreen|HP")
	void SetMaxHP(float NewMaxHP);
	virtual void SetMaxHP_Implementation(float NewMaxHP) PURE_VIRTUAL(IMainScreenInterface::SetCurrentHP,)

};
