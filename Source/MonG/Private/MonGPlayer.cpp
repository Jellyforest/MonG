// Fill out your copyright notice in the Description page of Project Settings.
#include <UMG/Public/Blueprint/UserWidget.h>
#include "MonGPlayer.h"
#include <../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h>
#include "EnhancedInputSubsystems.h"
#include <Engine/LocalPlayer.h>
#include <Camera/CameraComponent.h>
#include <MotionControllerComponent.h>
#include "Components/CapsuleComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include "Dust.h"
#include "PlayWidget.h"
#include "Components/SphereComponent.h"
#include <Kismet/GameplayStatics.h>
#include "Components/TextBlock.h"
#include <UMG/Public/Components/WidgetComponent.h>
#include <Components/ArrowComponent.h>
#include "CleaningEffect.h"
#include "Haptics/HapticFeedbackEffect_Curve.h"
#include "MonGGameModeBase.h"
#include "Cleaner.h"


// Sets default values
AMonGPlayer::AMonGPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//카메라
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("camera"));
	camera->SetupAttachment(RootComponent);
	camera->bUsePawnControlRotation = false;

	//프리셋세팅
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("PlayerPreset"));
	
	//모션컨트롤러
	rightHand = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("rightHand"));
	rightHand->SetupAttachment(RootComponent);
	rightHand->SetTrackingMotionSource(FName("Right"));
	leftHand = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("leftHand"));
	leftHand->SetupAttachment(RootComponent);
	leftHand->SetTrackingMotionSource(FName("Left"));
	//모션컨트롤러 오른손 Mesh
	rightMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("rightMesh"));
	rightMesh->SetupAttachment(rightHand);
	ConstructorHelpers::FObjectFinder<USkeletalMesh>tempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/MannequinsXR/Meshes/SKM_QuinnXR_right.SKM_QuinnXR_right'"));
		if (tempMesh.Succeeded())
		{
			rightMesh->SetSkeletalMesh(tempMesh.Object);
			rightMesh->SetRelativeLocation(FVector(-2.9f, 3.5f, 4.5f));
			rightMesh->SetRelativeRotation(FRotator(25, 0, 90));
		}
	//모션컨트롤러 왼손 Mesh
	leftMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("leftMesh"));
	leftMesh->SetupAttachment(leftHand);
	ConstructorHelpers::FObjectFinder<USkeletalMesh>tempMesh2(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/MannequinsXR/Meshes/SKM_QuinnXR_left.SKM_QuinnXR_left'"));
	if (tempMesh2.Succeeded())
	{
		leftMesh->SetSkeletalMesh(tempMesh2.Object);
		leftMesh->SetRelativeLocation(FVector(-2.9f, -3.5f, 4.5f));
		leftMesh->SetRelativeRotation(FRotator(-25, -180, 90));
	}
	
	//청소기 세팅

	cleanerComp = CreateDefaultSubobject<UBoxComponent>(TEXT("cleanerComp"));
	cleanerComp->SetupAttachment(rightHand);
	cleanerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("cleanerMesh"));
	cleanerMesh->SetupAttachment(cleanerComp);
	cleanerHead = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("cleanerHead"));
	cleanerHead->SetupAttachment(rightHand);
	cleanerHeadComp = CreateDefaultSubobject<USphereComponent>(TEXT("CleanerHeadComp"));
	cleanerHeadComp->SetupAttachment(cleanerHead);

	
	/////청소기 프리셋
	//////cleanerComp->SetCollisionProfileName(TEXT("CleanerPreset"));
	rightHand->SetCollisionProfileName(TEXT("PlayerPreset"));
	leftHand->SetCollisionProfileName(TEXT("PlayerPreset"));
	//시간, 점수 위젯
	play_UI = CreateDefaultSubobject<UPlayWidget>(TEXT("play_UI"));
	widgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("widgetComp"));
	widgetComp->SetupAttachment(camera);
}

// Called when the game starts or when spawned
void AMonGPlayer::BeginPlay()
{
	Super::BeginPlay();

	playerController = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());
	play_UI = CreateWidget<UPlayWidget>(GetWorld(), playWidget);

	if (playerController)
	{
		auto localPlayer = playerController->GetLocalPlayer();
		auto subSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(localPlayer);
		if (subSystem)
		{
			subSystem->AddMappingContext(IMC_MonGInput, 0);
			subSystem->AddMappingContext(IMC_Hand, 0);
		}
	}

	rightHand->OnComponentBeginOverlap.AddDynamic(this, &AMonGPlayer::OnOverlap);
	leftHand->OnComponentBeginOverlap.AddDynamic(this, &AMonGPlayer::OnOverlap);
	//시간, ->OnComponentBeginOverlap.AddDynamic(this, &AMonGPlayer::OnOverlap);

	dust = Cast<ADust>(UGameplayStatics::GetActorOfClass(GetWorld(), ADust::StaticClass()));
	
	//먼지 방향바꾸기
	if (dust)
	{
		monGDirection = cleanerHead->GetComponentLocation()-dust->GetActorLocation();
		monGDirection.Normalize();
	}
	//시간 위젯
	play_UI->AddToViewport();
}

// Called every frame
void AMonGPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMonGPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* inputSystem = Cast <UEnhancedInputComponent>(PlayerInputComponent);
	if (inputSystem)
	{
		inputSystem->BindAction(IA_MonGMove, ETriggerEvent::Triggered, this, &AMonGPlayer::Move);
		inputSystem->BindAction(IA_MonGMouse, ETriggerEvent::Triggered, this, &AMonGPlayer::Look);
		inputSystem->BindAction(IA_Cleaning, ETriggerEvent::Started, this, &AMonGPlayer::Clean);
		inputSystem->BindAction(IA_Cleaning, ETriggerEvent::Completed, this, &AMonGPlayer::StopClean);
		inputSystem->BindAction(IA_MonGGrap, ETriggerEvent::Started, this, &AMonGPlayer::Hold);
		inputSystem->BindAction(IA_MonGGrap, ETriggerEvent::Completed, this, &AMonGPlayer::Hold);
	}

}

void AMonGPlayer::Move(const FInputActionValue& Values)
{
	FVector2D axis = Values.Get<FVector2D>();
	AddMovementInput(GetActorForwardVector(), axis.X);
	AddMovementInput(GetActorRightVector(), axis.Y);

}

void AMonGPlayer::Look(const FInputActionValue& Values)
{
	FVector2D axis = Values.Get<FVector2D>();
	AddControllerYawInput(axis.X);
	AddControllerPitchInput(axis.Y);

}

void AMonGPlayer::Clean()
{
	//마우스 클릭시 청소기 돌아가게
	isClean = true;

	/*
	//청소효과
	AActor* cleanFX = GetWorld()->SpawnActor<ACleaningEffect>(cleaningEffect, cleanerHeadComp->GetComponentLocation(), cleanerHeadComp->GetComponentRotation());
	cleanFX->AttachToComponent(cleanerHeadComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("hand_lSocket"));
	*/
	
	//청소기 진동
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		PC->PlayHapticEffect(HF_Clean, EControllerHand::Right);
	}
	
}

void AMonGPlayer::StopClean()
{
	//마우스 클릭안하면 청소기 안돌아가게
	isClean = false;
}

void AMonGPlayer::Hold()
{
	isHold = true;
}

void AMonGPlayer::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	cleaner = Cast<ACleaner>(OtherActor);
	UE_LOG(LogTemp, Warning, TEXT("OverlapHold"));

	if (isHold == true)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hold==true"));

		cleaner->cleanerMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		cleaner->AttachToComponent(rightHand, FAttachmentTransformRules::KeepWorldTransform);
		cleaner->AttachToComponent(leftHand, FAttachmentTransformRules::KeepWorldTransform);
	}

	/*
	dust=Cast<ADust>(OtherActor);
	if (isClean == true)
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
	*/
}
//확인
