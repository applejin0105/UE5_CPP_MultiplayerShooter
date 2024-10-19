// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "TestPlugin/Public/MySimpleActor.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMySimpleActor() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_AActor();
TESTPLUGIN_API UClass* Z_Construct_UClass_AMySimpleActor();
TESTPLUGIN_API UClass* Z_Construct_UClass_AMySimpleActor_NoRegister();
UPackage* Z_Construct_UPackage__Script_TestPlugin();
// End Cross Module References

// Begin Class AMySimpleActor
void AMySimpleActor::StaticRegisterNativesAMySimpleActor()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AMySimpleActor);
UClass* Z_Construct_UClass_AMySimpleActor_NoRegister()
{
	return AMySimpleActor::StaticClass();
}
struct Z_Construct_UClass_AMySimpleActor_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "MySimpleActor.h" },
		{ "ModuleRelativePath", "Public/MySimpleActor.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AMySimpleActor>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_AMySimpleActor_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_TestPlugin,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AMySimpleActor_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AMySimpleActor_Statics::ClassParams = {
	&AMySimpleActor::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AMySimpleActor_Statics::Class_MetaDataParams), Z_Construct_UClass_AMySimpleActor_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AMySimpleActor()
{
	if (!Z_Registration_Info_UClass_AMySimpleActor.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AMySimpleActor.OuterSingleton, Z_Construct_UClass_AMySimpleActor_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AMySimpleActor.OuterSingleton;
}
template<> TESTPLUGIN_API UClass* StaticClass<AMySimpleActor>()
{
	return AMySimpleActor::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AMySimpleActor);
AMySimpleActor::~AMySimpleActor() {}
// End Class AMySimpleActor

// Begin Registration
struct Z_CompiledInDeferFile_FID_Unreal_Projects_Unreal_Projects_MenuSystem_Plugins_TestPlugin_Source_TestPlugin_Public_MySimpleActor_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AMySimpleActor, AMySimpleActor::StaticClass, TEXT("AMySimpleActor"), &Z_Registration_Info_UClass_AMySimpleActor, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AMySimpleActor), 1155455484U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Unreal_Projects_Unreal_Projects_MenuSystem_Plugins_TestPlugin_Source_TestPlugin_Public_MySimpleActor_h_1797562726(TEXT("/Script/TestPlugin"),
	Z_CompiledInDeferFile_FID_Unreal_Projects_Unreal_Projects_MenuSystem_Plugins_TestPlugin_Source_TestPlugin_Public_MySimpleActor_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Unreal_Projects_Unreal_Projects_MenuSystem_Plugins_TestPlugin_Source_TestPlugin_Public_MySimpleActor_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
