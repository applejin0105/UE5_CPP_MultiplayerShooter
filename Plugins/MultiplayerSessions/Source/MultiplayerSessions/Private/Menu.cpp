// Fill out your copyright notice in the Description page of Project Settings.

/*
 * Slate에서는 UI의 포커스와 입력을 관리한다.
 * 따라서, UMG사용 중, 포커스와 입력을 처리하기 위해서는 UMG <-> Slate 전환이 필요하다.
 * 이를 해주는 함수가 TakeWidget이다.
 */

#include "Menu.h"
#include "Components/Button.h"
#include "MultiplayerSessionsSubsystem.h"

void UMenu::MenuSetup()
{
	// 현재 위젯을 게임화면에 추가하는 함수
	// 위젯은 메모리에 생성된 후 AddToViewport()를 통해 화면에 렌더링한다.
	AddToViewport();
	// UI 위젯을 숨김 상태로 설정한다.
	// 이를 통해 필요할때만 보이게 할 수있다.
	SetVisibility(ESlateVisibility::Visible);
	// bIsFocusable은 더 이상 사용하지 않는다.
	// 위젯이 포커스를 받을 수 있도록 설정한다.
	// 즉, UI가 활성화되면 이 위젯이 키보드나 컨트롤러 입력을 받을 수 있다.
	SetIsFocusable(true);

	// 위젯은 플레이어의 입력을 바탕으로 작동되므로, 현재 월드에서 캐릭터의 컨트롤러를 받아온다.
	// 이를 통해 UI와 상호작용이 가능하도록 한다.
	UWorld* world = GetWorld();
	if(world)
	{
		APlayerController* PlayerController = world->GetFirstPlayerController();
		if(PlayerController)
		{
			// UI 전용 입력 모드 구조체를 생성한다.
			// FInputModeUIOnly는 게임 플레이보다 UI와의 상호작용에 집중할 수 있는 입력 모드로,
			// 마우스와 키보드 입력이 UI 위젯에 집중되도록 한다.
			FInputModeUIOnly InputModeData;
			// UI 전용 입력 모드가 활성화되면 (위 Hidden이 해제되면) TakeWidget()함수는 UUserWidget을 SWidget으로 변환하여
			// Slate 시스템을 전달하는 함수로, 이 위젯이 현재 포커스를 받도록 지정한다.
			// UUserWidget 객체는 UMG의 고수준 위젯이다. 이를 SWidget을 변환해주어야(저수준 위젯), Slate 기반 시스템에서 위젯 사용이 가능하다.
			// Slate의 포커스 시스템을 사용하기 위해 이와 같은 작업이 필요하다.
			// TakeWidget()은 이를 변환해 두 시스템이 상호작용 할 수 있도록 해준다.
			InputModeData.SetWidgetToFocus(TakeWidget());
			// 위에서 Slate로 변환 InputModeData를 바탕으로,
			// 마우스 커서를 화면에 고정할지 여부를 선택한다.
			// DoNotLock의 경우 마우스 커서를 고정하지 않는다. (화면 밖으로 나갈 수 있다.)
			InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			// 설정한 FInputModeUIOnly 데이터를 플레이어 컨트롤러에 적용하여, 플레이어가 UI와 상호작용이 가능하도록 입력 모드를 변경한다.
			// 즉, Player 컨트롤러 사용 여부를 식별하고,위 코드까지의 과정을 통해 설정한 뒤, 다음 코드를 통해 게임 내의 캐릭터 조작 대신 UI 조작이 가능해진다.
			PlayerController->SetInputMode(InputModeData);
			PlayerController->SetShowMouseCursor(true);
		}
	}

	UGameInstance* GameInstance = GetGameInstance();
	if(GameInstance)
	{
		// return Subsystem
		MultiplayerSessionsSubsystem = GameInstance->GetSubsystem<UMultiplayerSessionsSubsystem>();
	}
}

// 생성자와 유사하지만, 위젯을 만든 후 초기화한다.
bool UMenu::Initialize()
{
	if(!Super::Initialize())
	{
		return false;
	}

	if(HostButton)
	{
		HostButton->OnClicked.AddDynamic(this, &ThisClass::HostButtonClick);
	}

	if(JoinButton)
	{
		JoinButton->OnClicked.AddDynamic(this, &ThisClass::JoinButtonClick);
	}
	
	return true;
}

void UMenu::HostButtonClick()
{
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, "Hosting button");
	}

	if(MultiplayerSessionsSubsystem)
	{
		MultiplayerSessionsSubsystem->CreateSession(4, FString("FreeForAll"));
	}
}

void UMenu::JoinButtonClick()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, "Join button");
}
