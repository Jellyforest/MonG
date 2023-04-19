// Fill out your copyright notice in the Description page of Project Settings.


#include "CleanRobot.h"
#include <Components/SphereComponent.h>
#include <Components/StaticMeshComponent.h>

// Sets default values
ACleanRobot::ACleanRobot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	robotComp = CreateDefaultSubobject<USphereComponent>(TEXT("robotComp"));
	SetRootComponent(RootComponent);
	robotMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("robotMesh"));
	robotMesh->SetupAttachment(robotComp);
}

// Called when the game starts or when spawned
void ACleanRobot::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACleanRobot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



}

