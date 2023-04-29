// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Components/TimelineComponent.h>

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	doorComp = CreateDefaultSubobject<UBoxComponent>(TEXT("doorComp"));
	SetRootComponent(RootComponent);
	doorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("doorMesh"));
	doorMesh->SetupAttachment(doorComp);

	doorTimeLine = CreateDefaultSubobject<UTimelineComponent>(TEXT("doorTimeLine"));

}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoor::UpdateTimeLine(float output)
{
	// Ÿ�Ӷ��� Ŀ��(Timeline Curve)�� ����� �������� ���� �� ����� ��ġ ���� �� ����
	FRotator doorNewRotation = FRotator(0, output, 0);
	doorMesh->SetRelativeRotation(doorNewRotation);
}

