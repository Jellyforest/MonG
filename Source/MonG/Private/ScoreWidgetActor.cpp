// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreWidgetActor.h"
#include "ScoreWidget.h"
#include <UMG/Public/Components/WidgetComponent.h>

// Sets default values
AScoreWidgetActor::AScoreWidgetActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	score_UI = CreateDefaultSubobject<UScoreWidget>(TEXT("start_UI"));
	scoreWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("scoreWidgetComp"));
	SetRootComponent(RootComponent);
	scoreWidgetComp->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AScoreWidgetActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AScoreWidgetActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

