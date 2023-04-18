// Fill out your copyright notice in the Description page of Project Settings.


#include "DustWaveSpawner.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Components/ArrowComponent.h>

// Sets default values
ADustWaveSpawner::ADustWaveSpawner()
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
void ADustWaveSpawner::BeginPlay()
{
	Super::BeginPlay();
	

	

}

// Called every frame
void ADustWaveSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*
	currentTime += DeltaTime;
	coolCurentTime += DeltaTime;
	if (currentTime == 0)
	{
		SetActorLocation(locationSetting);
	}

	if (coolCurentTime >= coolTime)
	{
		GetWorld()->SpawnActor<ADust>(dustSpawn, arrow->GetComponentLocation(), arrow->GetComponentRotation());
		coolCurentTime = 0;
	}
	if (currentTime > teleportTime && currentTime < teleportTime1)
	{
		SetActorLocation(GetActorLocation() + GetActorUpVector().RotateAngleAxis(180, FVector(1, 0, 0)).GetSafeNormal() * moveSpeed);
	}
	if (currentTime > teleportTime1)
	{
		SetActorLocation(GetActorLocation() + GetActorUpVector().GetSafeNormal() * moveSpeed);
	}
	if (currentTime > 5)
	{
		currentTime = 0;
	}
	
	*/


	FVector direction = GetActorUpVector() * -1;
	SetActorLocation(GetActorLocation() + direction * 200 * DeltaTime);

	float index = GetActorLocation().Z;



	/*
	float distance = (locationSetting - GetActorLocation()).Length();
	///float deltaTime = GetWorld()->DeltaTimeSeconds;
	if (distance < 500 && distance >=200 )
	{
		FVector direction = GetActorUpVector() * -1;
		SetActorLocation(GetActorLocation() + direction * 200 * DeltaTime);

	}
	if (distance >= 0 && distance < 200)
	{
		FVector direction = GetActorUpVector();
		SetActorLocation(GetActorLocation() + direction * 200 * DeltaTime);
	}
	*/
}

