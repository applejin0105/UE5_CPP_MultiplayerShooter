// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "ReverotorCharacter.generated.h"

class UInteractionComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

USTRUCT()
struct FInteractionData
{
	GENERATED_BODY()

	FInteractionData()
	{
		ViewedInteractionComponent = nullptr;
		LastInteractionCheckTime = 0.0f;
		bInteractHeld = false;
	}

	UPROPERTY()
	class UInteractionComponent* ViewedInteractionComponent;

	UPROPERTY()
	float LastInteractionCheckTime;

	UPROPERTY()
	bool bInteractHeld;
};

UCLASS(config=Game)
class AReverotorCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Status", meta=(AllowPrivateAccess=true))
	float HP;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Status", meta=(AllowPrivateAccess=true))
	float SP;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Status", meta=(AllowPrivateAccess=true))
	float Ammo;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Status", meta=(AllowPrivateAccess=true))
	int Magazine;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Status", meta=(AllowPrivateAccess=true))
	float Charge;
	
	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractionAction;
	
	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** Run Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* RunAction;

	/** Fire Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* FireAction;

	/** Zoom Input Action */
	
public:
	AReverotorCharacter();

	bool IsInteracting() const;
	float GetRemainingTime() const;
	
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	void Run(const FInputActionValue& Value);
	
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// To add mapping context
	virtual void BeginPlay();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
	float InteractionCheckFrequency;

	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
	float InteractionCheckDistance;

	void PerformInteractionCheck();

	void CouldntFindInteractable();
	void FoundNewInteractable(UInteractionComponent* Interactable);

	void BeginInteract();
	void EndInteract();

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerBeginInteract();

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerEndInteract();
	
	void Interact();

	UPROPERTY()
	FInteractionData InteractionData;

	FORCEINLINE class UInteractionComponent* GetInteractable() const
	{
		return InteractionData.ViewedInteractionComponent;
	}

	FTimerHandle TimerHandle_Interact;
};