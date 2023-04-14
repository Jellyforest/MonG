// Fill out your copyright notice in the Description page of Project Settings.


#include "DustStrollSpawner.h"

ADustStrollSpawner::ADustStrollSpawner()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ADustStrollSpawner::BeginPlay()
{
	Super::BeginPlay();

	leftDirection = FVector(30, -180, 240);
	leftDirection.Normalize();


}

void ADustStrollSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	currentTime += DeltaTime;

	if (currentTime > teleportTime && currentTime<teleportTime1)
	{
		SetActorLocation(GetActorLocation() + GetActorRightVector().RotateAngleAxis(0, FVector(0, 1, 0)).GetSafeNormal());
	}
	if (currentTime > teleportTime1)
	{
		SetActorLocation(GetActorLocation() + GetActorUpVector().RotateAngleAxis(-90, FVector(1, 0, 0)).GetSafeNormal());

	}
	if (currentTime > 14)
	{
		currentTime = 0;
	}

	/*
	FVector stroll_Right = FVector(30, 830, 240);
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

}
