// Fill out your copyright notice in the Description page of Project Settings.


#include "Dust.h"
#include <Components/SphereComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Kismet/GameplayStatics.h>

// Sets default values
ADust::ADust()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	dustComp = CreateDefaultSubobject<USphereComponent>(TEXT("dustComp"));
	SetRootComponent(dustComp);
	dustComp->SetCollisionProfileName(TEXT("DustPreset"));
	dustComp->SetSphereRadius(0.5f);

	dustMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("dustMesh"));
	dustMesh->SetupAttachment(dustComp);
	dustMesh->SetRelativeScale3D(FVector(0.3f));
	
	

}

// Called when the game starts or when spawned
void ADust::BeginPlay()
{
	Super::BeginPlay();
	
	//AMonGPlayer* monGPlayer = Cast<AMonGPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), AMonGPlayer::StaticClass()));
	//monGDirection = monGPlayer->GetActorLocation() - GetActorLocation();
	
	//monGDirection.Normalize();

	monGPlayer = Cast<AMonGPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), AMonGPlayer::StaticClass()));
}

// Called every frame
void ADust::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	currentTime += DeltaTime;

	//SetActorLocation(GetActorLocation() + monGDirection * moveSpeed * DeltaTime);

	//SetActorLocation(GetActorForwardVector());
	//if (monGPlayer->inClenner==false)
	//{
		//SetActorLocation(GetActorLocation() + GetActorForwardVector() * moveSpeed * DeltaTime);
		SetActorLocation(GetActorLocation() + GetActorForwardVector() * moveSpeed * DeltaTime);
	//	UE_LOG(LogTemp, Warning, TEXT("go"));

	//}
	//if (monGPlayer->inClenner == true)
	//{
	///	UE_LOG(LogTemp, Warning, TEXT("stop"));
	//	
	//}
	//È®ÀÎ
	if (currentTime > destroyTime)
	{
		Destroy();
	}
	
}



