// Fill out your copyright notice in the Description page of Project Settings.


#include "_Data/DataAsset/MeleeGeneralSet_PDA.h"

FPrimaryAssetId UMeleeGeneralSet_PDA::GetPrimaryAssetId() const
{
	// Type을 MeleeWeapon으로 선언, GetFName과 섞어서 ID를 생성
	// ID
	// Type: MeleeWeapon
	// Name: Set or MeleeGeneralSet_PDA
	return FPrimaryAssetId("MeleeWeapon", AssetName != NAME_None ? AssetName : GetFName());
}
