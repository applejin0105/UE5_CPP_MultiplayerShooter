// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionComponent.h"
#include "InteractionWidget.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "UE_Framework/Character/ReverotorCharacter.h"


// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.

	InteractionTime = 0.0f;
	InteractionDistance = 0.0f;
	InteractableNameText = FText::FromString("Interactable Object");
	InteractableActionText = FText::FromString("Interact");
	bAllowMultipleInteractors = true;

	Space = EWidgetSpace::World;
	bDrawAtDesiredSize = false;

	UActorComponent::SetActive(true);
	SetHiddenInGame(true);
}


void UInteractionComponent::SetInteractableNameText(const FText& NewNameText)
{
	InteractableNameText = NewNameText;
	RefreshWidget();
}

void UInteractionComponent::SetInteractableActionText(const FText& NewActionText)
{
	InteractableActionText = NewActionText;
	RefreshWidget();
}

void UInteractionComponent::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	FName PropertyName = (PropertyChangedEvent.Property != nullptr)
		                     ? PropertyChangedEvent.Property->GetFName()
		                     : NAME_None;

	if (PropertyName == GET_MEMBER_NAME_CHECKED(UInteractionComponent, DrawSizeOption))
	{
		if (DrawSizeOption != EDrawSizeOptions::Custom)
		{
			DrawSize = GetDrawSize(DrawSizeOption);
		}
	}
}

// Called when the game starts
void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
	InitUIPosition();
	// ...
}


void UInteractionComponent::Deactivate()
{
	Super::Deactivate();

	for (int32 i = Interactors.Num() - 1; i >= 0; --i)
	{
		if (AReverotorCharacter* Interactor = Interactors[i])
		{
			EndFocus(Interactor);
			EndInteract(Interactor);
		}
	}
	Interactors.Empty();
}

bool UInteractionComponent::CanInteract(class AReverotorCharacter* Character) const
{
	const bool bPlayerAlreadyInteracting = !bAllowMultipleInteractors && Interactors.Num() >= 1;
	return !bPlayerAlreadyInteracting && IsActive() && GetOwner() != nullptr && Character != nullptr;
}

void UInteractionComponent::LookAt(AReverotorCharacter* Character)
{
	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetComponentLocation(),
	                                                                 Character->GetFollowCamera()->
	                                                                 GetComponentLocation());
	//SetRelativeRotation(LookAtRotation);
	//LookAtRotation.Pitch = 0.f;
	SetWorldRotation(LookAtRotation);
}

void UInteractionComponent::InitUIPosition()
{
	if (AActor* Owner = GetOwner())
	{
		// 바운딩 박스 정보 가져오기
		Owner->GetActorBounds(true, Origin, BoxExtent);

		// 기준 위치 계산
		TopMostPosition = Origin + FVector(0.0f, 0.0f, BoxExtent.Z); // 가장 상단
		RightMostPosition = Origin + FVector(BoxExtent.X, 0.0f, 0.0f); // 가장 오른쪽

		TargetPosition = Origin; // 초기값

		// DrawSizeOption에 따라 위치 결정
		switch (DrawSizeOption)
		{
		case EDrawSizeOptions::HealthBar:
			offset = FVector(0.0f, 0.0f, 50.0f);
			TargetPosition = TopMostPosition + offset;
			break;
		case EDrawSizeOptions::InfoWindow_Door:
			offset = FVector(0.0f, -150.0f, 0.0f);
			TargetPosition = RightMostPosition + offset;
			break;
		case EDrawSizeOptions::InfoWindow_SmallObject:
			break;
		case EDrawSizeOptions::InfoWindow_LargeObject:
			break;
		}
	}
}

void UInteractionComponent::UpdateUIPosition()
{
	if (AActor* Owner = GetOwner())
	{
		SetWorldLocation(TargetPosition);
	}
}

// Called every frame
void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UInteractionComponent::RefreshWidget()
{
	if (!bHiddenInGame && GetOwner()->GetNetMode() != NM_DedicatedServer)
	{
		if (UInteractionWidget* InteractionWidget = Cast<UInteractionWidget>(GetUserWidgetObject()))
		{
			InteractionWidget->UpdateInteractionWidget(this);
		}
	}
}

void UInteractionComponent::BeginFocus(class AReverotorCharacter* Character)
{
	if (!IsActive() || !GetOwner() || !Character)
	{
		return;
	}

	OnBeginFocus.Broadcast(Character);

	SetHiddenInGame(false);

	UpdateUIPosition();

	if (GetOwner()->HasAuthority())
	{
		// GetComponentsByClass가 없어서 다음과 같이 변경
		TArray<UPrimitiveComponent*> OutComps;
		GetOwner()->GetComponents<UPrimitiveComponent>(OutComps);
		for (auto OutComp : OutComps)
		{
			OutComp->SetRenderCustomDepth(true);
		}

		/*for (auto& VisualComp : GetOwner->K2_GetComponentsByClass(UPrimitiveComponent::StaticClass()))
		{
			if (UPrimitiveComponent* Prim = Cast<UPrimitiveComponent>(VisualComp))
			{
				Prim->SetRenderCustomDepth(true);
			}
		}*/
	}

	FTimerDelegate TimerDelegate;
	TimerDelegate.BindUObject(this, &ThisClass::LookAt, Character);
	Character->GetWorld()->GetTimerManager().SetTimer(LookAtTimerHandle, TimerDelegate, 0.1f, true);

	RefreshWidget();
}

void UInteractionComponent::EndFocus(class AReverotorCharacter* Character)
{
	OnEndFocus.Broadcast(Character);

	SetHiddenInGame(true);

	if (GetOwner()->HasAuthority())
	{
		// GetComponentsByClass가 없어서 다음과 같이 변경
		TArray<UPrimitiveComponent*> OutComps;
		GetOwner()->GetComponents<UPrimitiveComponent>(OutComps);
		for (auto OutComp : OutComps)
		{
			OutComp->SetRenderCustomDepth(false);
		}

		/*for (auto& VisualComp : GetOwner->K2_GetComponentsByClass(UPrimitiveComponent::StaticClass()))
		{
			if (UPrimitiveComponent* Prim = Cast<UPrimitiveComponent>(VisualComp))
			{
				Prim->SetRenderCustomDepth(true);
			}
		}*/
	}

	Character->GetWorld()->GetTimerManager().ClearTimer(LookAtTimerHandle);
}

void UInteractionComponent::BeginInteract(class AReverotorCharacter* Character)
{
	if (CanInteract(Character))
	{
		Interactors.AddUnique(Character);
		OnBeginInteract.Broadcast(Character);
	}
}

void UInteractionComponent::EndInteract(class AReverotorCharacter* Character)
{
	Interactors.RemoveSingle(Character);
	OnEndInteract.Broadcast(Character);
}

void UInteractionComponent::Interact(class AReverotorCharacter* Character)
{
	if (CanInteract(Character))
	{
		OnInteract.Broadcast(Character);
	}
}

float UInteractionComponent::GetInteractPercentage()
{
	if (Interactors.IsValidIndex(0))
	{
		if (AReverotorCharacter* Interactor = Interactors[0])
		{
			if (Interactor && Interactor->IsInteracting())
			{
				return 1.f - FMath::Abs(Interactor->GetRemainingTime() / InteractionTime);
			}
		}
	}
	return 0.0f;
}

FIntPoint UInteractionComponent::GetDrawSize(EDrawSizeOptions Option)
{
	switch (Option)
	{
	case EDrawSizeOptions::HealthBar:
		return FIntPoint(333, 54);
	case EDrawSizeOptions::InfoWindow_Door:
		return FIntPoint(200, 110);
	case EDrawSizeOptions::InfoWindow_SmallObject:
		return FIntPoint(200, 110);
	case EDrawSizeOptions::InfoWindow_LargeObject:
		return FIntPoint(200, 110);
	case EDrawSizeOptions::Custom:
	default:
		return FIntPoint(0, 0);
	}
}
