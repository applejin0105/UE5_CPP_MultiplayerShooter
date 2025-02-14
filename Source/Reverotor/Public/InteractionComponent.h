// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "InteractionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBeginInteract, class AReverotorCharacter*, Character);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEndInteract, class AReverotorCharacter*, Character);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBeginFocus, class AReverotorCharacter*, Character);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEndFocus, class AReverotorCharacter*, Character);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteract, class AReverotorCharacter*, Character);

UENUM(BlueprintType, Category = "Interaction")
enum class EDrawSizeOptions : uint8
{
	HealthBar						UMETA(DisplayName = "Health Bar"),
	InfoWindow_Door					UMETA(DisplayName = "Info_Door"),
	InfoWindow_SmallObject			UMETA(DisplayName = "Info_SmallObject"),
	InfoWindow_LargeObject			UMETA(DisplayName = "Info_LargeObject"),
	Custom							UMETA(DisplayName = "Custom")
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class REVEROTOR_API UInteractionComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInteractionComponent();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	float InteractionTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	float InteractionDistance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	FText InteractableNameText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	FText InteractableActionText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	bool bAllowMultipleInteractors;

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void SetInteractableNameText(const FText& NewNameText);

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void SetInteractableActionText(const FText& NewActionText);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	EDrawSizeOptions DrawSizeOption;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction", meta = (EditCondition = "DrawSizeOptions == EDrawSizeOptions::Custom", EditConditionHides))
	FIntPoint CustomDrawSize;
	
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
							   FActorComponentTickFunction* ThisTickFunction) override;

	void RefreshWidget();
	
	void BeginFocus(class AReverotorCharacter* Character);
	void EndFocus(class AReverotorCharacter* Character);
	
	void BeginInteract(class AReverotorCharacter* Character);
	void EndInteract(class AReverotorCharacter* Character);

	void Interact(class AReverotorCharacter* Character);

	// For UI Progressbar - Interacting Time
	UFUNCTION(BlueprintPure, Category = "Interaction")
	float GetInteractPercentage();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Delegates
	UPROPERTY(EditDefaultsOnly, BlueprintAssignable)
	FOnBeginInteract OnBeginInteract;
	
	UPROPERTY(EditDefaultsOnly, BlueprintAssignable)
	FOnEndInteract OnEndInteract;
	
	UPROPERTY(EditDefaultsOnly, BlueprintAssignable)
	FOnBeginFocus OnBeginFocus;
	
	UPROPERTY(EditDefaultsOnly, BlueprintAssignable)
	FOnEndFocus OnEndFocus;
	
	UPROPERTY(EditDefaultsOnly, BlueprintAssignable)
	FOnInteract OnInteract;

	virtual void Deactivate() override;

	bool CanInteract(class AReverotorCharacter* Character) const;

	FTimerHandle LookAtTimerHandle;
	void LookAt(AReverotorCharacter* Character);

	void UpdateUIPosition();

	void InitUIPosition();
	
	UPROPERTY()
	TArray<class AReverotorCharacter*> Interactors;

private:
	static FIntPoint GetDrawSize(EDrawSizeOptions Option);

	FVector Origin, BoxExtent, TopMostPosition, RightMostPosition, TargetPosition, offset;
};
