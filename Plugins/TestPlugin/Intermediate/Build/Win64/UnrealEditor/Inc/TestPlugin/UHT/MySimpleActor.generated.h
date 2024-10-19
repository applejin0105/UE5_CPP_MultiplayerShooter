// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "MySimpleActor.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef TESTPLUGIN_MySimpleActor_generated_h
#error "MySimpleActor.generated.h already included, missing '#pragma once' in MySimpleActor.h"
#endif
#define TESTPLUGIN_MySimpleActor_generated_h

#define FID_Unreal_Projects_Unreal_Projects_MenuSystem_Plugins_TestPlugin_Source_TestPlugin_Public_MySimpleActor_h_10_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAMySimpleActor(); \
	friend struct Z_Construct_UClass_AMySimpleActor_Statics; \
public: \
	DECLARE_CLASS(AMySimpleActor, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/TestPlugin"), NO_API) \
	DECLARE_SERIALIZER(AMySimpleActor)


#define FID_Unreal_Projects_Unreal_Projects_MenuSystem_Plugins_TestPlugin_Source_TestPlugin_Public_MySimpleActor_h_10_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	AMySimpleActor(AMySimpleActor&&); \
	AMySimpleActor(const AMySimpleActor&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AMySimpleActor); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AMySimpleActor); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AMySimpleActor) \
	NO_API virtual ~AMySimpleActor();


#define FID_Unreal_Projects_Unreal_Projects_MenuSystem_Plugins_TestPlugin_Source_TestPlugin_Public_MySimpleActor_h_7_PROLOG
#define FID_Unreal_Projects_Unreal_Projects_MenuSystem_Plugins_TestPlugin_Source_TestPlugin_Public_MySimpleActor_h_10_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Unreal_Projects_Unreal_Projects_MenuSystem_Plugins_TestPlugin_Source_TestPlugin_Public_MySimpleActor_h_10_INCLASS_NO_PURE_DECLS \
	FID_Unreal_Projects_Unreal_Projects_MenuSystem_Plugins_TestPlugin_Source_TestPlugin_Public_MySimpleActor_h_10_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> TESTPLUGIN_API UClass* StaticClass<class AMySimpleActor>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Unreal_Projects_Unreal_Projects_MenuSystem_Plugins_TestPlugin_Source_TestPlugin_Public_MySimpleActor_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
