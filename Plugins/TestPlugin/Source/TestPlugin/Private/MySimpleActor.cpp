#include "MySimpleActor.h"



AMySimpleActor::AMySimpleActor()
{
	PrimaryActorTick.bCanEverTick = true;
}



void AMySimpleActor::BeginPlay()
{
	Super::BeginPlay();
}



void AMySimpleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
