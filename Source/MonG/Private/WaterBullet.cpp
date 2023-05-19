// Fill out your copyright notice in the Description page of Project Settings.


#include "WaterBullet.h"
#include <Components/StaticMeshComponent.h>
#include <Components/SphereComponent.h>


// Sets default values
AWaterBullet::AWaterBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bulletComp = CreateDefaultSubobject<USphereComponent>(TEXT("bulletComp"));
	SetRootComponent(RootComponent);
	bulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("bulletMesh"));
	bulletMesh->SetupAttachment(bulletComp);
	bulletComp->SetCollisionProfileName(TEXT("WaterBulletPreset"));
}

// Called when the game starts or when spawned
void AWaterBullet::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void AWaterBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorLocation(GetActorLocation() + GetActorForwardVector() * moveSpeed * DeltaTime);
	
	currentTime += DeltaTime;
	if (currentTime > destroyTime)
	{
		Destroy();
	}
}

