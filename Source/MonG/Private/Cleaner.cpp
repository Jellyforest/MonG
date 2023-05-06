// Fill out your copyright notice in the Description page of Project Settings.


#include "Cleaner.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Components/SphereComponent.h>
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "CleaningEffect.h"
#include "Dust.h"
#include <Kismet/GameplayStatics.h>
#include "MonGGameModeBase.h"
#include "MonGPlayer.h"


// Sets default values
ACleaner::ACleaner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	cleanerComp = CreateDefaultSubobject<UBoxComponent>(TEXT("cleanerComp"));
	SetRootComponent(cleanerComp);
	cleanerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("cleanerMesh"));
	cleanerMesh->SetupAttachment(cleanerComp);
	cleanerHead = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("cleanerHead"));
	cleanerHead->SetupAttachment(cleanerComp);
	cleanerHeadComp = CreateDefaultSubobject<USphereComponent>(TEXT("CleanerHeadComp"));
	cleanerHeadComp->SetupAttachment(cleanerHead);
	playerOverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("playerOverlapComp"));
	playerOverlapComp->SetupAttachment(cleanerMesh);

	//청소기 프리셋
	cleanerComp->SetCollisionProfileName(TEXT("CleanerPreset"));
	playerOverlapComp->SetCollisionProfileName(TEXT("CleanerCompPreset"));
}

// Called when the game starts or when spawned
void ACleaner::BeginPlay()
{
	Super::BeginPlay();
	
	cleanerComp->OnComponentBeginOverlap.AddDynamic(this, &ACleaner::OnCleanerComp);

}

// Called every frame
void ACleaner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACleaner::CleanerClean()
{
	
	//청소효과
	AActor* cleanFX = GetWorld()->SpawnActor<ACleaningEffect>(cleaningEffect, cleanerHeadComp->GetComponentLocation(), cleanerHeadComp->GetComponentRotation());
	cleanFX->AttachToComponent(cleanerHeadComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("hand_lSocket"));
}

void ACleaner::OnCleanerComp(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	monGPlayer = Cast<AMonGPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), AMonGPlayer::StaticClass()));
	dust = Cast<ADust>(OtherActor);
	if (monGPlayer->isClean == true)
	{
		dust->moveSpeed = 5;
		dust->dustComp->SetSimulatePhysics(false);
		dust->dustComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		dust->AttachToComponent(cleanerHead, FAttachmentTransformRules::KeepWorldTransform);
		//////////점수
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

