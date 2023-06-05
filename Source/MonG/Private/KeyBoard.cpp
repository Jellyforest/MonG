// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyBoard.h"
#include <Components/StaticMeshComponent.h>
#include <Components/BoxComponent.h>

// Sets default values
AKeyBoard::AKeyBoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	keyboardMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("keyboardMesh"));
	SetRootComponent(RootComponent);
	aComp = CreateDefaultSubobject<UBoxComponent>(TEXT("aComp"));
	aComp->SetBoxExtent(FVector(0.2, 2.1, 2.9));
	aComp->SetRelativeScale3D(FVector(1, 1.2, 1.2));
	aComp->SetCollisionProfileName(TEXT("A"));
	bComp = CreateDefaultSubobject<UBoxComponent>(TEXT("bComp"));
	bComp->SetBoxExtent(FVector(0.2, 2.1, 2.9));
	bComp->SetRelativeScale3D(FVector(1, 1.2, 1.2));
	bComp->SetCollisionProfileName(TEXT("B"));
}

// Called when the game starts or when spawned
void AKeyBoard::BeginPlay()
{
	Super::BeginPlay();
	

}

// Called every frame
void AKeyBoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

