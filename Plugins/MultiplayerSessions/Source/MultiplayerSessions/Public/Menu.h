// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Menu.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERSESSIONS_API UMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	// 위젯을 만들면 블루프린트 호출이 가능한 MenuSetup을 생성
	UFUNCTION(BlueprintCallable)
	void MenuSetup();

protected:

	virtual bool Initialize() override;

private:

	// 위젯과 코드를 바인딩한다.
	// 블루프린트의 버튼 위젯이 C++의 버튼과 연결되는 것
	// 버튼 이름은 반드시 같아야 한다.
	UPROPERTY(meta = (BindWidget))
	class UButton* HostButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* JoinButton;

	UFUNCTION()
	void HostButtonClick();
	
	UFUNCTION()
	void JoinButtonClick();

	// The Subsystem designed to all online session functionality
	class UMultiplayerSessionsSubsystem* MultiplayerSessionsSubsystem;
};
