// Fill out your copyright notice in the Description page of Project Settings.


#include "LeftDustSpawner.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Components/ArrowComponent.h>

// Sets default values
ALeftDustSpawner::ALeftDustSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	spawnerComp = CreateDefaultSubobject<UBoxComponent>(TEXT("spawnerComp"));
	SetRootComponent(spawnerComp);
	spawnerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("spawnerMesh"));
	spawnerMesh->SetupAttachment(spawnerComp);
	arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("arrow"));
	arrow->SetupAttachment(spawnerComp);
}

// Called when the game starts or when spawned
void ALeftDustSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALeftDustSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	currentTime += DeltaTime;
	coolCurentTime += DeltaTime;
	fireTime += DeltaTime;
	if (coolCurentTime >= coolTime)
	{
		GetWorld()->SpawnActor<ADust>(dustSpawn, arrow->GetComponentLocation(), arrow->GetComponentRotation());
		coolCurentTime = 0;
	}
	FVector stroll_left = FVector(10, -250, 60);
	if (currentTime < teleportTime)
	{
		SetActorLocation(stroll_left);

	}
	if (currentTime > teleportTime && currentTime < teleportTime1)
	{
		SetActorLocation(GetActorLocation() + GetActorUpVector().RotateAngleAxis(-90, FVector(1, 0, 0)).GetSafeNormal() * moveSpeed);

	}
	if (currentTime > teleportTime1)
	{
		SetActorLocation(GetActorLocation() + GetActorRightVector().RotateAngleAxis(0, FVector(0, 1, 0)).GetSafeNormal() * moveSpeed);
	}
	if (currentTime > 11)
	{
		currentTime = 0;
	}
}

