// Fill out your copyright notice in the Description page of Project Settings.


#include "Postit.h"

// Sets default values
APostit::APostit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APostit::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APostit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

