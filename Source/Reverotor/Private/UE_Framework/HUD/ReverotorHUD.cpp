// Fill out your copyright notice in the Description page of Project Settings.


#include "UE_Framework/HUD/ReverotorHUD.h"

#include "Blueprint/UserWidget.h"



bool AReverotorHUD::IsPendingKill(const FGameplayTag WidgetGameplayTag) const
{
	return PendingKill_Collect.Contains(WidgetGameplayTag);
}



void AReverotorHUD::BackToUserUserWidget_Collect(const FGameplayTag WidgetGameplayTag)
{
	if (!PendingKill_Collect.Contains(WidgetGameplayTag)) return;
	
	const FPendingKillUserWidget PendingKillUserWidget = PendingKill_Collect.FindRef(WidgetGameplayTag);
	
	if (UWorld* World = GetWorld())
	{
		FTimerHandle ClearHandle = PendingKillUserWidget.TimerHandle;
		World->GetTimerManager().ClearTimer(ClearHandle);
	}

	UserWidget_Collect.FindOrAdd(WidgetGameplayTag, PendingKillUserWidget.UserWidget);
	
	PendingKill_Collect.Remove(WidgetGameplayTag);
}




void AReverotorHUD::CreateWidgetWithGameplayTag(const FGameplayTag CreateWidgetGameplayTag, const TSubclassOf<UUserWidget> CreateWidgetClass, UUserWidget*& ResultUserWidget)
{
	if (IsPendingKill(CreateWidgetGameplayTag))
	{
		BackToUserUserWidget_Collect(CreateWidgetGameplayTag);
	}

	if (UserWidget_Collect.Contains(CreateWidgetGameplayTag))
	{
		ResultUserWidget = UserWidget_Collect.FindRef(CreateWidgetGameplayTag);
		if (IsValid(ResultUserWidget)) return;
	}
	
	APlayerController* const OwningPlayerController = GetOwningPlayerController();
	if (IsValid(CreateWidgetClass) && IsValid(OwningPlayerController))
	{
		ResultUserWidget = CreateWidget<UUserWidget>(OwningPlayerController, CreateWidgetClass);
		if (ResultUserWidget)
		{
			UserWidget_Collect.Add(CreateWidgetGameplayTag, ResultUserWidget);
		}
	}
}



void AReverotorHUD::AddToViewPortWithGameplayTag(const FGameplayTag AddWidgetGameplayTag, const int32 ZOrder /*= 0*/, const bool Force /*= false*/)
{
	if (IsPendingKill(AddWidgetGameplayTag))
	{
		BackToUserUserWidget_Collect(AddWidgetGameplayTag);
	}
	
	if (UserWidget_Collect.Contains(AddWidgetGameplayTag))
	{
		const TObjectPtr<UUserWidget> FindUserWidgetRef = UserWidget_Collect.FindRef(AddWidgetGameplayTag);
		if (IsValid(FindUserWidgetRef))
		{
			
			if (FindUserWidgetRef->IsInViewport() && Force)
			{
				FindUserWidgetRef->RemoveFromParent();
			}
			
			if (!FindUserWidgetRef->IsInViewport())
			{
				FindUserWidgetRef->AddToViewport(ZOrder);
			}
			
			return;
		}
		UserWidget_Collect.Remove(AddWidgetGameplayTag);
	}
}



void AReverotorHUD::RemoveFromParentWithGameplayTag(FGameplayTag RemoveWidgetGameplayTag, const float LifeTime /*= 10.f*/)
{
	if (!UserWidget_Collect.Contains(RemoveWidgetGameplayTag)) return;

	const TObjectPtr<UUserWidget> FindUserWidgetRef = UserWidget_Collect.FindRef(RemoveWidgetGameplayTag);
	if (!IsValid(FindUserWidgetRef) || !FindUserWidgetRef->IsInViewport()) return;

	FindUserWidgetRef->RemoveFromParent();
	UserWidget_Collect.Remove(RemoveWidgetGameplayTag);

	if (LifeTime <= 0.f) return;

	FTimerHandle TimerHandle;
	if (const UWorld* World = GetWorld())
	{
		World->GetTimerManager().SetTimer(
			TimerHandle,
			[this, RemoveWidgetGameplayTag]()
			{
				if (PendingKill_Collect.Contains(RemoveWidgetGameplayTag)) PendingKill_Collect.Remove(RemoveWidgetGameplayTag);
			},
			LifeTime,
			false
		);
	}

	if (TimerHandle.IsValid())
	{
		PendingKill_Collect.FindOrAdd(RemoveWidgetGameplayTag, FPendingKillUserWidget(FindUserWidgetRef, TimerHandle));
	}
}



void AReverotorHUD::GetUserWidget(const FGameplayTag WidgetGameplayTag, UUserWidget*& ResultUserWidget, EIsValid& Switch)
{
	
	ResultUserWidget= UserWidget_Collect.Contains(WidgetGameplayTag) ? UserWidget_Collect.FindRef(WidgetGameplayTag) : nullptr;
	const bool bIsValid = IsValid(ResultUserWidget) || IsPendingKill(WidgetGameplayTag);
	
	Switch = bIsValid ? EIsValid::IsValid : EIsValid::IsNotValid;
}



void AReverotorHUD::IsValidUserWidget(const FGameplayTag WidgetGameplayTag, EIsValid& Switch)
{
	UUserWidget* DummyUserWidget;
	GetUserWidget(WidgetGameplayTag, DummyUserWidget, Switch);
}



