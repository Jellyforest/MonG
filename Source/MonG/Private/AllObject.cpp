// Fill out your copyright notice in the Description page of Project Settings.


#include "AllObject.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>

// Sets default values
AAllObject::AAllObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	objectComp = CreateDefaultSubobject<UBoxComponent>(TEXT("objectComp"));
	SetRootComponent(RootComponent);
	objectMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("objectMesh"));
	objectMesh->SetupAttachment(objectComp);
	objectComp->SetCollisionProfileName(TEXT("CleanerStickPreset"));

}

// Called when the game starts or when spawned
void AAllObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAllObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

