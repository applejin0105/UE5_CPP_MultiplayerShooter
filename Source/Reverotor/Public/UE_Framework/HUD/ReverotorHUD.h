// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/HUD.h"
#include "ReverotorHUD.generated.h"


/**
 * 
 */
USTRUCT()
struct FPendingKillUserWidget
{
	GENERATED_BODY()
	
	FPendingKillUserWidget() = default;

	FPendingKillUserWidget(const TObjectPtr<UUserWidget>& InUserWidget, const FTimerHandle& InTimerHandle): UserWidget(InUserWidget), TimerHandle(InTimerHandle){}
	
	TObjectPtr<UUserWidget> UserWidget;

	FTimerHandle TimerHandle;
};


UENUM(BlueprintType)
enum class EIsValid : uint8
{
	IsValid,
	IsNotValid
};

class IUW_ReverotorEditionInterface;
/**
 * 
 */
UCLASS()
class REVEROTOR_API AReverotorHUD : public AHUD
{
	GENERATED_BODY()

	UPROPERTY()
	TMap <FGameplayTag, TObjectPtr<UUserWidget>> UserWidget_Collect;

	UPROPERTY()
	TMap <FGameplayTag, FPendingKillUserWidget> PendingKill_Collect; 

protected:
	bool IsPendingKill(FGameplayTag WidgetGameplayTag) const;
	void BackToUserUserWidget_Collect(FGameplayTag WidgetGameplayTag);
	
public:
	UFUNCTION(BlueprintCallable, Category="UserWidget")
	void CreateWidgetWithGameplayTag(FGameplayTag CreateWidgetGameplayTag, TSubclassOf<UUserWidget> CreateWidgetClass, UUserWidget*& ResultUserWidget);

	UFUNCTION(BlueprintCallable, Category="UserWidget", meta=(AdvancedDisplay="Zorder, Force"))
	void AddToViewPortWithGameplayTag(FGameplayTag AddWidgetGameplayTag, int32 ZOrder = 0, bool Force = false);

	UFUNCTION(BlueprintCallable, Category="UserWidget", meta=(AdvancedDisplay="LifeTime"))
	void RemoveFromParentWithGameplayTag(FGameplayTag RemoveWidgetGameplayTag, float LifeTime = 10.f);

	UFUNCTION(BlueprintCallable, Category="UserWidget", meta=(ExpandEnumAsExecs="Switch"))
	void GetUserWidget(FGameplayTag WidgetGameplayTag, UUserWidget*& ResultUserWidget, EIsValid& Switch);

	UFUNCTION(BlueprintCallable, Category="UserWidget", meta=(ExpandEnumAsExecs="Switch"))
	void IsValidUserWidget(FGameplayTag WidgetGameplayTag, EIsValid& Switch);

	
	
};
