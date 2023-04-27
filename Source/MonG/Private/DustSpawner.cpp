// Fill out your copyright notice in the Description page of Project Settings.


#include "DustSpawner.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Components/ArrowComponent.h>
#include "Dust.h"

// Sets default values
ADustSpawner::ADustSpawner()
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
void ADustSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADustSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	currentTime += DeltaTime;
	int32 drawNumber = FMath::RandRange(1, 100);
	

	if (currentTime >= coolTime)
	{
		if (drawNumber < pointThree && pointFive < drawNumber)
		{
			GetWorld()->SpawnActor<ADust>(dustP3Spawn, arrow->GetComponentLocation(), arrow->GetComponentRotation());
		}
		if (drawNumber > pointThree)
		{
			GetWorld()->SpawnActor<ADust>(dustSpawn, arrow->GetComponentLocation(), arrow->GetComponentRotation());
		}
		if (drawNumber < pointFive)
		{
			GetWorld()->SpawnActor<ADust>(dustP4Spawn, arrow->GetComponentLocation(), arrow->GetComponentRotation());
		}
		
		currentTime = 0;
	}

}

