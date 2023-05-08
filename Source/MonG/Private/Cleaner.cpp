// Fill out your copyright notice in the Description page of Project Settings.


#include "Cleaner.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Components/SphereComponent.h>

// Sets default values
ACleaner::ACleaner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	cleanerComp = CreateDefaultSubobject<UBoxComponent>(TEXT("cleanerComp"));
	SetRootComponent(RootComponent);
	cleanerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("cleanerMesh"));
	cleanerMesh->SetupAttachment(cleanerComp);
	cleanerHead = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("cleanerHead"));
	cleanerHead->SetupAttachment(cleanerComp);
	cleanerHeadComp = CreateDefaultSubobject<USphereComponent>(TEXT("CleanerHeadComp"));
	cleanerHeadComp->SetupAttachment(cleanerHead);

}

// Called when the game starts or when spawned
void ACleaner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACleaner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

