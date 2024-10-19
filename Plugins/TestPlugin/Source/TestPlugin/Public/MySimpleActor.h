#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MySimpleActor.generated.h"

UCLASS()
class TESTPLUGIN_API AMySimpleActor : public AActor
{
	GENERATED_BODY()

public:
	AMySimpleActor();
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
