// Fill out your copyright notice in the Description page of Project Settings.


#include "_Data/DataAsset/ResourcesGeneralSet_PDA.h"

template <typename T>
bool UResourcesGeneralSet_PDA::GetResourceInternal(const TMap<FName, TObjectPtr<T>>& ResourceMap, FName Key, T*& OutResource) const
{
	if (ResourceMap.Contains(Key))
	{
		OutResource = ResourceMap.FindRef(Key);
		return true;
	}
	return false;
}

bool UResourcesGeneralSet_PDA::GetTexture(FName Key, UTexture2D*& OutTexture) const
{
	return UResourcesGeneralSet_PDA::GetResourceInternal(Texture, Key, OutTexture);
}

bool UResourcesGeneralSet_PDA::GetMaterialInstance(FName Key, UMaterialInstance*& OutMaterialInstance) const
{
	return UResourcesGeneralSet_PDA::GetResourceInternal(MaterialInstance, Key, OutMaterialInstance);
}

bool UResourcesGeneralSet_PDA::GetSoundCue(FName Key, USoundCue*& OutSoundCue) const
{
	return UResourcesGeneralSet_PDA::GetResourceInternal(SoundCue ,Key, OutSoundCue);
}
