// Fill out your copyright notice in the Description page of Project Settings.


#include "Cleaner.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Components/SphereComponent.h>
#include <GameFramework/GameModeBase.h>
#include "MonGGameModeBase.h"
#include <Kismet/GameplayStatics.h>
#include "MonGPlayer.h"

// Sets default values
ACleaner::ACleaner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	cleanerComp = CreateDefaultSubobject<UBoxComponent>(TEXT("cleanerComp"));
	SetRootComponent(RootComponent);
	cleanerComp->SetCollisionProfileName(TEXT("CleanerPreset"));
	cleanerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("cleanerMesh"));
	cleanerMesh->SetupAttachment(cleanerComp);
	cleanerStick = CreateDefaultSubobject<UBoxComponent>(TEXT("cleanerStick"));
	cleanerStick->SetupAttachment(cleanerMesh);
	cleanerHead = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("cleanerHead"));
	cleanerHead->SetupAttachment(cleanerComp);
	cleanerHeadComp = CreateDefaultSubobject<USphereComponent>(TEXT("CleanerHeadComp"));
	cleanerHeadComp->SetupAttachment(cleanerHead);
	//cleanerStick->SetCollisionObjectType(ECC_GameTraceChannel6);

	cleanerStick->SetCollisionProfileName(TEXT("CleanerStickPreset"));
}

// Called when the game starts or when spawned
void ACleaner::BeginPlay()
{
	Super::BeginPlay();
	monGPlayer = Cast<AMonGPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), AMonGPlayer::StaticClass()));

	cleanerComp->OnComponentBeginOverlap.AddDynamic(this, &ACleaner::CleaningTime);
	dust = Cast<ADust>(UGameplayStatics::GetActorOfClass(GetWorld(), ADust::StaticClass()));

}

// Called every frame
void ACleaner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ACleaner::CleaningTime(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	dust = Cast<ADust>(OtherActor);

	if (monGPlayer->isClean == true)
	{
		dust->moveSpeed = 5;
		dust->dustComp->SetSimulatePhysics(false);
		dust->dustComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		dust->AttachToComponent(cleanerHead, FAttachmentTransformRules::KeepWorldTransform);
		//////////Á¡¼ö
		AGameModeBase* gm = UGameplayStatics::GetGameMode(this);
		AMonGGameModeBase* monGgm = Cast<AMonGGameModeBase>(gm);
		monGgm->AddScore(dust->point);
		dust->getPoint = true;

		FTimerHandle destroyTimer;
		FTimerDelegate timerDelegate;
		timerDelegate.BindLambda([this]()->void {
			if (dust != nullptr)
			{
				dust->Destroy();
			}
			});
		GetWorld()->GetTimerManager().SetTimer(destroyTimer, timerDelegate, 0.5f, false);
	}
}

