// Fill out your copyright notice in the Description page of Project Settings.


#include "Marker.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>

// Sets default values
AMarker::AMarker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	markerComp = CreateDefaultSubobject<UBoxComponent>(TEXT("markerComp"));
	SetRootComponent(RootComponent);
	markerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("markerMesh"));
	markerMesh->SetupAttachment(markerComp);
	markerLead = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("markerLead"));
	markerLead->SetupAttachment(markerComp);
	markerComp->SetCollisionProfileName(TEXT("CleanerStickPreset"));


}

// Called when the game starts or when spawned
void AMarker::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMarker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

