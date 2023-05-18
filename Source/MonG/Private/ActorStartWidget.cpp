// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorStartWidget.h"
#include "StartWidget.h"
#include <UMG/Public/Components/WidgetComponent.h>

// Sets default values
AActorStartWidget::AActorStartWidget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	start_UI = CreateDefaultSubobject<UStartWidget>(TEXT("start_UI"));
	startWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("startWidgetComp"));
	SetRootComponent(RootComponent);
	startWidgetComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AActorStartWidget::BeginPlay()
{
	Super::BeginPlay();
	


	isShowStartUI = true;

}

// Called every frame
void AActorStartWidget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	

}

