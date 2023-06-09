// Fill out your copyright notice in the Description page of Project Settings.


#include "DustStrollSpawner.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Components/ArrowComponent.h>
#include "MonGPlayer.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
ADustStrollSpawner::ADustStrollSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	spawnerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("spawnerMesh"));
	SetRootComponent(spawnerMesh);
	spawnerComp = CreateDefaultSubobject<UBoxComponent>(TEXT("spawnerComp"));
	spawnerComp->SetCollisionProfileName(TEXT("MonGBossPreset"));
	spawnerComp->SetupAttachment(spawnerMesh);
	arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("arrow"));
	arrow->SetupAttachment(spawnerMesh);
}

// Called when the game starts or when spawned
void ADustStrollSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	monGPlayer = Cast<AMonGPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), AMonGPlayer::StaticClass()));


}

// Called every frame
void ADustStrollSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*
	currentTime += DeltaTime;
	coolCurentTime += DeltaTime;
	fireTime += DeltaTime;
	//UE_LOG(LogTemp, Warning, TEXT("%d"), fireTime);
	//if (fireTime > fire && fireTime<120)
	//{
	int32 drawNumber = FMath::RandRange(1, 100);

		if (coolCurentTime >= coolTime)
		{
			if (coolCurentTime >= coolTime)
			{
				if (drawNumber < pointThree && pointFive < drawNumber)
				{
					GetWorld()->SpawnActor<ADust>(dustP3Spawn, arrow->GetComponentLocation(), arrow->GetComponentRotation());
				}
				if (drawNumber >= pointThree)
				{
					GetWorld()->SpawnActor<ADust>(dustSpawn, arrow->GetComponentLocation(), arrow->GetComponentRotation());
				}
				if (drawNumber <= pointFive)
				{
					GetWorld()->SpawnActor<ADust>(dustP5Spawn, arrow->GetComponentLocation(), arrow->GetComponentRotation());
				}
				coolCurentTime = 0;
			}
		}
	*/
	//	if (fireTime >15)
	//	{
	//		fireTime = 0;
	//	}

	//}
	/*
	if (currentTime < teleportTime)
	{
		SetActorLocation(stroll_Right);

	}
	
	
	if (currentTime > teleportTime && currentTime < teleportTime1 )
	{
		SetActorLocation(GetActorLocation() + GetActorRightVector().RotateAngleAxis(0, FVector(0, 1, 0)).GetSafeNormal() * moveSpeed);
	}
	
	
	if (currentTime > teleportTime1)
	{
		SetActorLocation(GetActorLocation() + GetActorUpVector().RotateAngleAxis(-90, FVector(1, 0, 0)).GetSafeNormal() * moveSpeed);

	}
	if (currentTime > 11)
	{
		currentTime = 0;
	}
	*/
	
	
	/*
	FVector stroll_Left = FVector(30, -180, 240);
	if(currentTime > teleportTime)
	{
		SetActorLocation(stroll_Right);
	}
	if (currentTime>teleportTime1)
	{
		SetActorLocation(stroll_Left);

	}
	if(currentTime>30)
	{
		currentTime = 0;
	}
	*/
	/*
	float index = GetActorLocation().Y;

	if (index <= -270)
	{
		goRight = true;
	}
	if (index >= -270 && index <= 930 && goRight == true || index < -270)
	{
		//UE_LOG(LogTemp, Warning, TEXT("right"));
		FVector direction = GetActorRightVector()*-1;
		SetActorLocation(GetActorLocation() + direction * 200 * DeltaTime);

	}

	if (index >= 930)
	{
		goRight = false;
	}

	if (index >= -270 && index <= 930 && goRight == false || index > 930)
	{
		//UE_LOG(LogTemp, Warning, TEXT("left"));

		FVector direction1 = GetActorRightVector();
		SetActorLocation(GetActorLocation() + direction1 * 200 * DeltaTime);
	}
	//UE_LOG(LogTemp, Warning, TEXT("%d"), goRight);
*/
}

void ADustStrollSpawner::Fire()
{
	if (monGPlayer->isGameStart == true)
	{

		int32 drawNumber = FMath::RandRange(1, 100);

		if (drawNumber < pointThree && pointFive < drawNumber)
		{

			GetWorld()->SpawnActor<ADust>(dustP3Spawn, arrow->GetComponentLocation(), arrow->GetComponentRotation());
	
		
		}
		if (drawNumber >= pointThree)
		{
			GetWorld()->SpawnActor<ADust>(dustSpawn, arrow->GetComponentLocation(), arrow->GetComponentRotation());
			//arrow->GetComponentRotation()
		}
		if (drawNumber <= pointFive)
		{
			GetWorld()->SpawnActor<ADust>(dustP5Spawn, arrow->GetComponentLocation(), arrow->GetComponentRotation());
		}
	}

}

