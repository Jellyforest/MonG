// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayWidgetActor.h"
#include <UMG/Public/Components/WidgetComponent.h>

// Sets default values
APlayWidgetActor::APlayWidgetActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	playWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("playWidgetComp"));
	SetRootComponent(RootComponent);
}

// Called when the game starts or when spawned
void APlayWidgetActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayWidgetActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

