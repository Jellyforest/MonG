// Fill out your copyright notice in the Description page of Project Settings.


#include "WaterBullet.h"
#include <Components/StaticMeshComponent.h>
#include <Components/SphereComponent.h>
#include "DustStrollSpawner.h"
#include <Kismet/GameplayStatics.h>

#define PRINTTOScreen(msg) GEngine->AddOnScreenDebugMessage(0, 1, FColor::Blue, msg)

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
	
	bulletComp->OnComponentBeginOverlap.AddDynamic(this, &AWaterBullet::WaterShoot);
	//dustStrollSpawner = Cast<ADustStrollSpawner>(UGameplayStatics::GetActorOfClass(GetWorld(), ADustStrollSpawner::StaticClass()));

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

void AWaterBullet::WaterShoot(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	dustStrollSpawner = Cast<ADustStrollSpawner>(OtherActor);
	if (dustStrollSpawner != nullptr)
	{

		PRINTTOScreen(FString::Printf(TEXT("BulletOverlap")));
		if (dustStrollSpawner->HP > 0)
		{
			dustStrollSpawner->HP -= 30;
			this->Destroy();
		}
		if (dustStrollSpawner->HP == 0)
		{
			dustStrollSpawner->Destroy();
		}
	}

}

