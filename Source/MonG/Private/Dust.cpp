// Fill out your copyright notice in the Description page of Project Settings.


#include "Dust.h"
#include <Components/SphereComponent.h>
#include <Components/StaticMeshComponent.h>

// Sets default values
ADust::ADust()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	dustComp = CreateDefaultSubobject<USphereComponent>(TEXT("dustComp"));
	dustMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("dustMesh"));

}

// Called when the game starts or when spawned
void ADust::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADust::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

