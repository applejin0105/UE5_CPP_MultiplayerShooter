// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "ResourcesGeneralSet_PDA.generated.h"

/**
 * 
 */
UCLASS()
class REVEROTOR_API UResourcesGeneralSet_PDA : public UPrimaryDataAsset
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TMap<FName, TObjectPtr<UTexture2D>> Texture;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TMap<FName, TObjectPtr<UMaterialInstance>> MaterialInstance;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TMap<FName, TObjectPtr<USoundCue>> SoundCue;

public:
	template <typename T>
	bool GetResourceInternal(const TMap<FName, TObjectPtr<T>>& ResourceMap, FName Key, T*& OutResource) const;
	
	UFUNCTION(BlueprintCallable)
	bool GetTexture(FName Key, UTexture2D*& OutTexture) const;

	UFUNCTION(BlueprintCallable)
	bool GetMaterialInstance(FName Key, UMaterialInstance*& OutMaterialInstance) const;

	UFUNCTION(BlueprintCallable)
	bool GetSoundCue(FName Key, USoundCue*& OutSoundCue) const;
};
