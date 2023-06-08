// Fill out your copyright notice in the Description page of Project Settings.


#include "Cleaner.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Components/SphereComponent.h>
#include <GameFramework/GameModeBase.h>
#include "MonGGameModeBase.h"
#include <Kismet/GameplayStatics.h>
#include "MonGPlayer.h"
#include "CleaningEffect.h"
#include <Components/ArrowComponent.h>
#include "WaterBullet.h"
#include "Sound/SoundCue.h"
#include <Components/AudioComponent.h>


#define PRINTTOScreen(msg) GEngine->AddOnScreenDebugMessage(0, 1, FColor::Blue, msg)

// Sets default values
ACleaner::ACleaner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	cleanerComp = CreateDefaultSubobject<UBoxComponent>(TEXT("cleanerComp"));
	SetRootComponent(RootComponent);
	cleanerComp->SetCollisionProfileName(TEXT("CleanerPreset"));
	//cleanerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("cleanerMesh"));
	//cleanerMesh->SetupAttachment(cleanerComp);
	cleanerStick = CreateDefaultSubobject<UBoxComponent>(TEXT("cleanerStick"));
	cleanerStick->SetupAttachment(cleanerComp);
	cleanerHead = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("cleanerHead"));
	cleanerHead->SetupAttachment(cleanerComp);
	cleanerHeadComp = CreateDefaultSubobject<USphereComponent>(TEXT("CleanerHeadComp"));
	cleanerHeadComp->SetupAttachment(cleanerHead);
	//cleanerStick->SetCollisionObjectType(ECC_GameTraceChannel6);

	cleanerStick->SetCollisionProfileName(TEXT("CleanerStickPreset"));
	arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("arrow"));
	arrow->SetupAttachment(cleanerHead);
	cleanerSoundComp = CreateDefaultSubobject<UAudioComponent>("bubbleSound");
	cleanerbubbleSoundComp = CreateDefaultSubobject<UAudioComponent>("cleanerbubbleSoundComp");
	cleanerSoundComp->SetupAttachment(RootComponent);
	cleanerbubbleSoundComp->SetupAttachment(RootComponent);
	//ConstructorHelpers::FObjectFinder<USoundWave>tempSound(TEXT("/Script/Engine.SoundWave'/Game/JY/Music/bubble.bubble'"));
	//if (tempSound.Succeeded())
//	{
		//bubleSound->SetSound(tempSound.Object);
	//}
}

// Called when the game starts or when spawned
void ACleaner::BeginPlay()
{
	Super::BeginPlay();
	monGPlayer = Cast<AMonGPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), AMonGPlayer::StaticClass()));

	cleanerComp->OnComponentBeginOverlap.AddDynamic(this, &ACleaner::CleaningTime);
	dust = Cast<ADust>(UGameplayStatics::GetActorOfClass(GetWorld(), ADust::StaticClass()));
	//먼지 방향바꾸기
	if (dust)
	{
		monGDirection = cleanerHead->GetComponentLocation() - dust->GetActorLocation();
		monGDirection.Normalize();
	}
}

// Called every frame
void ACleaner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ACleaner::CleaningTime(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	dust = Cast<ADust>(OtherActor);
	//PRINTTOScreen(FString::Printf(TEXT("cleanerOverlap")));

	if (monGPlayer->isLeftClean == true || monGPlayer->isRightClean == true)
	{
		dust->moveSpeed = 5;
		dust->dustComp->SetSimulatePhysics(false);
		dust->dustComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		dust->AttachToComponent(cleanerHead, FAttachmentTransformRules::KeepWorldTransform);
		//////////점수
		monGgm = Cast<AMonGGameModeBase>(UGameplayStatics::GetGameMode(this));
		monGgm->AddScore(dust->point);
		dust->getPoint = true;
		UGameplayStatics::PlaySound2D(this, cleanerSoundBase);	

		FTimerHandle destroyTimer;
		FTimerDelegate timerDelegate;
		timerDelegate.BindLambda([this]()->void {
			if (dust != nullptr)
			{
				dust->Destroy();
			}
			});
		GetWorld()->GetTimerManager().SetTimer(destroyTimer, timerDelegate, 0.2f, false);
		
	}
}


void ACleaner::Shoot()
{
	if (monGPlayer->isLeftClean == false && monGPlayer->isRightClean == false)
	{

		GetWorld()->SpawnActor<AWaterBullet>(waterBullet, arrow->GetComponentLocation(), arrow->GetComponentRotation());
		//UGameplayStatics::PlaySound2D(this, bubbleSoundBase);
		cleanerbubbleSoundComp->Play();

		isShoot = true;
	}
}

