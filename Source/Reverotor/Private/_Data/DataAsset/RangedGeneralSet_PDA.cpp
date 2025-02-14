// Fill out your copyright notice in the Description page of Project Settings.


#include "_Data/DataAsset/RangedGeneralSet_PDA.h"

FPrimaryAssetId URangedGeneralSet_PDA::GetPrimaryAssetId() const
{
	// Type을 RangedWeapon으로 선언, GetFName과 섞어서 ID를 생성
	// ID
	// Type: RangedWeapon
	// Name: Set or RangedGeneralSet_PDA
	return FPrimaryAssetId("RangedWeapon", AssetName != NAME_None ? AssetName : GetFName());
}
